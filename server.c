#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "http-server.h"
#include "utils/error.h"

const char *get_mime_type(const char *path)
{
    const char *ext = strrchr(path, '.');
    if (ext == NULL)
        return "text/plain";
    if (strcmp(ext, ".html") == 0)
        return "text/html";
    if (strcmp(ext, ".css") == 0)
        return "text/css";
    if (strcmp(ext, ".js") == 0)
        return "application/javascript";
    if (strcmp(ext, ".png") == 0)
        return "image/png";
    if (strcmp(ext, ".jpg") == 0)
        return "image/jpeg";
    if (strcmp(ext, ".gif") == 0)
        return "image/gif";
    return "text/plain";
}

void serve(int client_socket)
{

    // Receive from client
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read = read(client_socket, buffer, BUFFER_SIZE - 1);

    if (bytes_read < 0)
    {
        error("Error reading from socket");
    }

    buffer[bytes_read] = '\0';
    printf("Received request:\n%s\n", buffer);

    // Store method, path and version from request
    char method[16], path[256], version[16];
    sscanf(buffer, "%s %s %s", method, path, version);

    // serving index.html if root is requested
    char full_path[512] = "./";
    if (strcmp(path, "/") == 0)
    {
        strcpy(full_path, "./index.html");
    }
    else
    {
        strcat(full_path, path + 1);
    }

    // Read index.html file
    FILE *html_root = fopen(full_path, "r");
    if (html_root == NULL)
    {
        const char *response =
            "HTTP/1.1 404 Not Found\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: 45\r\n"
            "\r\n"
            "<html><body>404: File Not Found</body></html>";
        write(client_socket, response, strlen(response));
    }
    else
    {
        // determine file size
        fseek(html_root, 0, SEEK_END);
        long html_root_size = ftell(html_root);

        // Allocate heap memory to store content of index.html, if fails exit and close socket/html file
        fseek(html_root, 0, SEEK_SET);
        char *html_root_buffer = malloc(html_root_size);
        if (html_root_buffer == NULL)
        {
            perror("Error allocating memory");
            fclose(html_root);
            close(client_socket);
            return;
        }

        // Read index.html and store content in its buffer
        fread(html_root_buffer, 1, html_root_size, html_root);
        fclose(html_root);

        // Retrieve the mime type of request
        const char *mime_type = get_mime_type(full_path);

        // Send the header of response
        char header[BUFFER_SIZE];
        sprintf(header, "HTTP/1.1 200 OK\r\nContent-Type: %s\r\nContent-Length: %ld\r\n\r\n", mime_type, html_root_size);
        write(client_socket, header, strlen(header));

        // Send index.html file content
        write(client_socket, html_root_buffer, html_root_size);
        free(html_root_buffer);
    };

    close(client_socket);
}
