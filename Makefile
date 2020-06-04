CC=gcc
CFLAGS=-I.

dehpick: dehpick.o fileutil.o
	$(CC) -o dehpick dehpick.o fileutil.o

vuld: vuld.o fileutil.o
	$(CC) -o vuld vuld.o fileutil.o

clean:
	rm -f *.o dehpick vuld
