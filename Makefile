CC = g++
CFLAGS = -c -Wall

all: server client

man: server_man client_man

server: server.o server_logger.o utility.o tands.o
			$(CC) -O -o server server.o server_logger.o utility.o tands.o

client: client.o client_logger.o utility.o tands.o
			$(CC) -O -o client client.o client_logger.o utility.o tands.o

tands.o: tands.cpp
			$(CC) $(CFLAGS) tands.cpp

server.o: server.cpp	
			$(CC) $(CFLAGS) server.cpp

client.o: client.cpp
			$(CC) $(CFLAGS) client.cpp

server_logger.o: server_logger.cpp
			$(CC) $(CFLAGS) server_logger.cpp

client_logger.o: client_logger.cpp
			$(CC) $(CFLAGS) client_logger.cpp

utility.o: utility.cpp
			$(CC) $(CFLAGS) utility.cpp

server_man:
	groff -Tpdf -man server.man > server_man.pdf

client_man:
	groff -Tpdf -man client.man > client_man.pdf

clean:
			rm -f *o server client *pdf