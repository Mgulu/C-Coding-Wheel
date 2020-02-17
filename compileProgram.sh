gcc -ansi -I./ -c codeMessage.c -o codeMessage.o
gcc -ansi -I./ -c wheel.c -o wheel.o
gcc codeMessage.o wheel.o -o codeMessage
