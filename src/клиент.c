#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

#define PORT 8888
#define SERVER_IP "127.0.0.1"

int main() {
    WSADATA wsa;
    SOCKET clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[1024];
    int bytesReceived;
    SetConsoleOutputCP(CP_UTF8);

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup прерван\n");
        return 1;
    }

    // Create a socket
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Сокет прерван\n");
        return 1;
    }

    // Prepare the server address structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddr.sin_port = htons(PORT);

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        printf("Соединение прерван\n");
        return 1;
    }

    printf("Подключение к серверу\n");

    // Receive data from the server
    bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);

    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        printf("Сохранение мира:\n%s\n", buffer);
    } else {
        printf("Не найден файл save_word.txt\n");
    }

    // Close the socket and cleanup Winsock
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
