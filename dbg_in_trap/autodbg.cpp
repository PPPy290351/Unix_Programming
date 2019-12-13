#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <sys/user.h>

using namespace std;

void errquit(const char *msg) {
	perror(msg);
	exit(-1);
}

void dump_code(long addr, long code) {
	fprintf(stderr, "## %lx: code = %02x %02x %02x %02x %02x %02x %02x %02x\n",
		addr,
		((unsigned char *) (&code))[0],
		((unsigned char *) (&code))[1],
		((unsigned char *) (&code))[2],
		((unsigned char *) (&code))[3],
		((unsigned char *) (&code))[4],
		((unsigned char *) (&code))[5],
		((unsigned char *) (&code))[6],
		((unsigned char *) (&code))[7]);
}

int main(int argc, char *argv[]) {
	pid_t child;
	if((child = fork()) < 0) errquit("fork");
	if(child == 0) {
		if(ptrace(PTRACE_TRACEME, 0, 0, 0) < 0) errquit("ptrace");
		execlp("./no_more_traps", "./no_more_traps", NULL);
		errquit("execvp");
	} else {
		int status;
		unsigned long  code;
		if(waitpid(child, &status, 0) < 0) errquit("waitpid");
		assert(WIFSTOPPED(status));
		ptrace(PTRACE_SETOPTIONS, child, 0, PTRACE_O_EXITKILL);

		/* continue the execution */
		ptrace(PTRACE_CONT, child, 0, 0);

		char readp[2];
		FILE* fp;
		fp = fopen("no_more_traps.txt", "r");
    	if(fp == NULL) return -1;

    	fseek( fp, 0, SEEK_SET );
		while(fread(readp, 2, 1, fp)) {
			struct user_regs_struct regs;
			if(waitpid(child, &status, 0) < 0) errquit("waitpid error");
			if(!WSTOPSIG(status) && !WSTOPSIG(status) & 0x5) continue;
			if(ptrace(PTRACE_GETREGS, child, 0, &regs) != 0)
				errquit("ptrace(GETREGS)");
			code = ptrace(PTRACE_PEEKTEXT, child, regs.rip-1, 0);
			// dump_code(regs.rip, code);
			unsigned char index = strtol(readp, NULL, 16);
			if(ptrace(PTRACE_POKETEXT, child, regs.rip-1, (code & 0xffffffffffffff00) | index) != 0) errquit("poketext error");
			// code = ptrace(PTRACE_PEEKTEXT, child, regs.rip-1, 0);
			// dump_code(regs.rip, code);
			/* restore break point */
			regs.rip = regs.rip-1;
			/* set registers */
			if(ptrace(PTRACE_SETREGS, child, 0, &regs) != 0) errquit("ptrace(SETREGS)");
			ptrace(PTRACE_CONT, child, 0, 0);
		}
	}
	return 0;
}