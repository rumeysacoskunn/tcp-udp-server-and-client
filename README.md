The programs provide a basic demonstration of server-client communication
using TCP and UDP 

The TCP server listens on a specified port and sends a random fortune message to any connecting client. 
The fortunes are defined in the server code. Command is: ./tcp_server <port>

The TCP client connects to the server, receives a fortune message, and prints it to the console.
Command is: ./tcp_client <server> <port>

The UDP server binds to a port and responds to any incoming message with a random fortune. 
Fortunes are defined in the server code.

The UDP client sends an empty message to the server, receives the fortune response, and prints it to the console.
Commands are the same as tcp server and client
