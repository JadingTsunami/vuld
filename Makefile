CC=gcc
CFLAGS=-I.

dehpick: dehpick.o fileutil.o
	$(CC) -o dehpick dehpick.o fileutil.o

vuld: vuld.o fileutil.o gameutil.o
	$(CC) -o vuld vuld.o fileutil.o gameutil.o

clean:
	rm -f *.o *.O dehpick vuld vuld.exe
