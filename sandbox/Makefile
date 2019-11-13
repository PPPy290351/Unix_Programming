CC:= gcc
exe:= sandbox.so main
all:
	# gcc -rdynamic -Wall -o demo demo.c
	gcc -o sandbox.so -shared -fPIC sandbox.c -ldl
	gcc -rdynamic -Wall -o main main.c 

clean:
	rm $(exe)
