#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define DEFAULT_PORT 8080
#define DEFAULT_HOST "127.0.0.1"

void get_config(char **host, int *port)
{
  *host = getenv("HTTP_HOST");
  if (*host == NULL)
  {
    *host = DEFAULT_HOST;
  }

  char *port_str = getenv("HTTP_PORT");
  if (port_str == NULL)
  {
    *port = DEFAULT_PORT;
  }
  else
  {
    *port = atoi(port_str);
    if (*port == 0)
    {
      fprintf(stderr, "Cannot use HTTP_PORT=%d need non-zero value\n", *port);
    }
  }
}

size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata)
{
  size_t total_size = size * nmemb;
  fwrite(ptr, size, nmemb, stdout);
  return total_size;
}

void send_http_request(const char *host, int port, const char *endpoint) {
    int sockfd;
    struct sockaddr_in server_addr;
    char request[1024];
    char response[4096];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
    {
        perror("Socket creation failed");
        return;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(host);

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) 
    {
        perror("Connection failed");
        close(sockfd);
        return;
    }

    snprintf(request, sizeof(request),
             "GET /%s HTTP/1.1\r\n"
             "Host: %s:%d\r\n"
             "Connection: close\r\n\r\n", endpoint, host, port);

    if (send(sockfd, request, strlen(request), 0) < 0) 
    {
        perror("Send failed");
        close(sockfd);
        return;
    }

    ssize_t len = recv(sockfd, response, sizeof(response) - 1, 0);
    if (len < 0) 
    {
        perror("Receive failed");
    }

    else 
    {
        response[len] = '\0';
        printf("Response:\n%s\n", response);
    }

    close(sockfd);
}

int main(int argc, char *argv[])
{
  char endpoint[256];
  char *host;
  int port;

  get_config(&host, &port);

  while(1)
  {
    fprintf(stdout, "%s:%d/", host, port);
    fgets(endpoint, sizeof(endpoint), stdin);
    endpoint[strcspn(endpoint, "\n")] = '\0';
    send_http_request(host, port, endpoint);
  }

  return EXIT_SUCCESS;
}
