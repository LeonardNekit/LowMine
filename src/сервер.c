#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>

#define PORT 8888
#define FILENAME "save_word.txt"

int main() {
    WSADATA wsa;
    SOCKET serverSocket;
    SOCKET clientSocket;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    int addrLen = sizeof(struct sockaddr_in);
    SetConsoleOutputCP(CP_UTF8);

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup прерван\n");
        return 1;
    }

    // Create a socket
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Сокет прерван\n");
        return 1;
    }

    // Prepare the server address structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind the socket
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Bind прерван\n");
        return 1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 1) == SOCKET_ERROR) {
        printf("Listen прерван\n");
        return 1;
    }

    printf("Сервер запущен. Ждите подключение игрока...\n");

    // Accept a connection
    if ((clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrLen)) == INVALID_SOCKET) {
        printf("Принятие был прерван\n");
        return 1;
    }

    printf("Игрок подключился\n");

    // Open the file for reading
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Нет файла(или же переименован в другое название)\n");
        return 1;
    }

    // Read the contents of the file
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *fileContent = (char *)malloc(fileSize + 1);
    fread(fileContent, fileSize, 1, file);
    fclose(file);
    fileContent[fileSize] = '\0';

    // Send the file content to the client
    send(clientSocket, fileContent, fileSize, 0);

    free(fileContent);

    // Close sockets and cleanup Winsock
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
