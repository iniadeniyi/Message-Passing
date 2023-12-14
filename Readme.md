Name: Inioluwa Adeniyi
Student ID: 1629052
CMPUT 379, Fall 2022
Assignment 3: Client-Server / Monitoring
Included files: # Readme.md # server.cpp # server.hpp # client.cpp # client.hpp # client_logger.cpp # client_logger.hpp # server_logger.cpp # server_logger.hpp # utility.cpp # utility.hpp # Makefile # tands.cpp # server.man # client.man

Wiring Instructions: None

Running Instructions:

    1. Navigate to the directory containing the files

    2. Type "make" into the terminal to create an instance of the client and server executables
        # you can type "make server" to create just the server executable or "make client" to create just the client
        executable

    3. To run the executable:
        1. type "./server <port>" into one terminal to run the server. the port number should be a number between 5000 and 64000.
        the server logs its activities into a log file called server.log
        2. type "./client <port> <ip_addr> into another terminal to connect client to the server. the port is the port the server is listening from and the ip_addr is the address of the machine hosting the server.
        Clients are known by the name machinename.pid where machinename is the name of the machine the client is running on and pid is the process id of the client. this is also used to name a log file of the client where all its actvitites are entered.
        <machinename>.<pid>.log



    4. type "make man" into the terminal to create both the client and server man pages

    5. type in "make clean" to remove the object files and executables. the man page pdfs and log files are left for the user if they want to check.

Notes and Assumptions:

    This assignment was fairly straight forward. I used the server and client set up provided in class with some minor modifications.
    I used these resources to understand and implement the connection of the server to multiple clients using the
    select() system call, which allows the server to get the status for all open connections (i.e., file descriptors).
    . https://www.youtube.com/watch?v=Y6pFtgRdUts
    . https://www.softprayog.in/programming/socket-programming-using-the-select-system-call
    . https://www.youtube.com/watch?v=dquxuXeZXgo

    I also used this youtube video to understand how to create man pages.
    . https://www.youtube.com/watch?v=r2JrbyezhM4

        Note:
        1. You can create more instances of the client to connect to the server but you may need to use a different machine

        2.  the  server will timeout after 30 seconds of inactivity.

        3. The backlog of the server is 10. That is the server can have only 10 open connections at a time
# Message-Passing
