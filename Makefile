CC = gcc
serversrc = $(wildcard core_*.c server_*.c)
clientsrc = $(wildcard core_*.c client_*.c)
serverobj = $(serversrc:.c=.o)
clientobj = $(clientsrc:.c=.o)

server:
	$(CC) -o server $(serversrc)

client:
	$(CC) -o client $(clientsrc)

clean:
	rm -f server client
