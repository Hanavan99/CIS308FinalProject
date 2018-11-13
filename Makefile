CC = gcc
src = $(wildcard *.c)
obj = $(src:.c=.o)

client:
	$(CC) -o client $(obj) 

server:
	$(CC) -o server $(obj) 

clean:
	rm -f $(obj) client server
