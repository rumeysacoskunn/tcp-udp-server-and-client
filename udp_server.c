#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>

const char APRESSMESSAGE[10][999] = {
    "Your kindness will brighten someone's day.\n",
    "Good news is coming your way, stay positive!\n",
    "Opportunities for success are on the horizon.\n",
    "Your hard work will pay off in unexpected ways.\n",
    "A joyful surprise awaits you around the corner.\n",
    "Today is a perfect day to make a new friend.\n",
    "Your positive attitude will lead to great achievements.\n",
    "Believe in yourself, and anything is possible.\n",
    "The best is yet to come, keep moving forward.\n",
    "Love and happiness will surround you today.\n"
};

int random_number(int lower, int upper) {
    return rand() % (upper - lower + 1) + lower;
}

int main(int argc, char *argv[]) {
    int simpleSocket = 0;
    uint16_t simplePort = 0;
    int returnStatus = 0;
    char buffer[999] = "";
    struct sockaddr_in simpleServer, clientName;
    socklen_t clientNameLength = sizeof(clientName);

    if (2 != argc) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    simpleSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (simpleSocket == -1) {
        fprintf(stderr, "Could not create a socket!\n");
        exit(1);
    } else {
        fprintf(stderr, "Socket created!\n");
    }

    simplePort = atoi(argv[1]);

    bzero(&simpleServer, sizeof(simpleServer));
    simpleServer.sin_family = AF_INET;
    simpleServer.sin_addr.s_addr = htonl(INADDR_ANY);
    simpleServer.sin_port = htons(simplePort);

    returnStatus = bind(simpleSocket, (struct sockaddr *)&simpleServer, sizeof(simpleServer));

    if (returnStatus == 0) {
        fprintf(stderr, "Bind completed!\n");
    } else {
        fprintf(stderr, "Could not bind to address!\n");
        close(simpleSocket);
        exit(1);
    }

    while (1) {
        returnStatus = recvfrom(simpleSocket, buffer, sizeof(buffer), 0, (struct sockaddr *)&clientName, &clientNameLength);

        if (returnStatus == -1) {
            fprintf(stderr, "Error in recvfrom!\n");
            close(simpleSocket);
            exit(1);
        }

        srand(time(0));
        int randNum = random_number(0, 9);
        sendto(simpleSocket, APRESSMESSAGE[randNum], strlen(APRESSMESSAGE[randNum]), 0, (struct sockaddr *)&clientName, clientNameLength);
    }

    close(simpleSocket);
    return 0;
}
