#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "http-server.h"
#include "server.h"
#include "utils/error.h"

int main()
{
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;

    // Open the socket for connections
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket < 0)
    {
        error("Error opening socket");
    };

    // Define the server_addr struct fields
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to a port
    if (bind(server_socket, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        error("Error binding socket");
    };

    // Listen on the socket
    if (listen(server_socket, 5) > 0)
    {
        error("Error listening to socket");
    };

    printf("Server running on Port:%d\n", PORT);

    // Start accepting connection from client, and respond if connection is successful
    client_len = sizeof(client_addr);
    while (1)
    {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket < 0)
        {
            error("Error connecting to socket");
        };

        serve(client_socket);
    };

    close(server_socket);
}
