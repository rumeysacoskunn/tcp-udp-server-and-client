#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    int simpleSocket = 0;
    uint16_t simplePort = 0;
    int returnStatus = 0;
    char buffer[999] = "";
    struct sockaddr_in simpleServer;

    if (3 != argc) {
        fprintf(stderr, "Usage: %s <server> <port>\n", argv[0]);
        exit(1);
    }

    simpleSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (simpleSocket == -1) {
        fprintf(stderr, "Could not create a socket!\n");
        exit(1);
    } else {
        fprintf(stderr, "Socket created!\n");
    }

    simplePort = atoi(argv[2]);

    bzero(&simpleServer, sizeof(simpleServer));
    simpleServer.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &simpleServer.sin_addr);
    simpleServer.sin_port = htons(simplePort);

    // Send an empty message to the server
    returnStatus = sendto(simpleSocket, "", 0, 0, (struct sockaddr *)&simpleServer, sizeof(simpleServer));

    if (returnStatus == -1) {
        fprintf(stderr, "Error in sendto!\n");
        close(simpleSocket);
        exit(1);
    }

    // Receive the message from the server
    returnStatus = recvfrom(simpleSocket, buffer, sizeof(buffer), 0, NULL, NULL);

    if (returnStatus == -1) {
        fprintf(stderr, "Error in recvfrom!\n");
        close(simpleSocket);
        exit(1);
    }

    printf("%d: %s", returnStatus, buffer);

    close(simpleSocket);
    return 0;
}
