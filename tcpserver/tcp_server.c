#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

int main(void) {
  
  char server_data[256] = "This is the server data";
  
  // Create the server socket
  int server_socket;
  server_socket = socket(AF_INET, SOCK_STREAM, 0);

  // Define the server address
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(9002);
  server_address.sin_addr.s_addr = INADDR_ANY;

  // Bind the socket to our specified IP and port
  bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

  //Listen for traffic
  listen(server_socket, 1);

  //  Initalize variables for the client information

  struct sockaddr_storage client_address;
  socklen_t client_len = sizeof(client_address);

  // Get the client socket
  int client_socket;
  client_socket = accept(server_socket, (struct sockaddr*) &client_address, &client_len);

  //  Log the client IP
  char address_buffer[100];
  getnameinfo((struct sockaddr*) &client_address, client_len, address_buffer, sizeof(address_buffer), 0, 0, NI_NUMERICHOST);
  printf("Connection from %s\n", address_buffer);

  // Send the server data
  send(client_socket, server_data, sizeof(server_data), 0);

  // Close the socket
  close(server_socket);

  return 0;
}
