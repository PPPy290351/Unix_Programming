#!/usr/bin/env python

from capstone import *
from pwn import *
import binascii as b

NUMBER = 10 # brute force the quiz number

r = remote('127.0.0.1', port)

a = ''
md = Cs(CS_ARCH_X86, CS_MODE_64)

for g in range(0, NUMBER):
    a = ''
    c = ''
    CODE = ''
    z = r.recvuntil('>>> ')
    ui = r.recvuntil('\n')
    #print(ui)
    CODE = b.a2b_hex(ui.strip()) 
    ### odd-length error : .strip() -> maybe something extra in it, whitespace ...
    for i in md.disasm(CODE, 0x1000):
        a += i.mnemonic + ' ' + i.op_str + '\n'
    c = b.hexlify(a.encode('utf-8'))
    ### must byte-like as input , no str : .encode('utf-8') -> maybe non-ascii in it?
    #print(c)
    r.sendline(c)

r.interactive()

'''
Sample from capstone
for i in md.disasm(CODE, 0x1000):
    #print("0x%x:\t%s\t%s" %(i.address, i.mnemonic, i.op_str))
'''
