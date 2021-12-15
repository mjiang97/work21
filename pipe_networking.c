#include "pipe_networking.h"

/*=========================
  server_handshake
  args: int * to_client
  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.
  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
    int from_client = 0;
    printf("creating wkp...\n");
    mkfifo(WKP, 0644);

    printf("opening from_client...\n");
    from_client = open(WKP, O_RDONLY);

    printf("reading from_client...\n");
    char f[HANDSHAKE_BUFFER_SIZE];
    read(from_client, f, sizeof(f));
    remove(WKP); 

    printf("opening secret pipe...\n");
    *to_client = open(f, O_WRONLY);

    printf("writing to client...\n");
    write(*to_client, ACK, sizeof(ACK));

    printf("receiving from client...\n");
    read(from_client, f, sizeof(f));

    printf("received.\n");
    remove(ACK);
    printf("removed pipes.\n");

    return from_client;
}

/*=========================
  client_handshake
  args: int * to_server
  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.
  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
    int from_server = 0;
    printf("creating secret pipe...\n");
    mkfifo(ACK, 0644);

    printf("opening wkp...\n");
    *to_server = open(WKP, O_WRONLY);

    printf("writing to server...\n");
    write(*to_server, ACK, sizeof(ACK));

    printf("receiving server message...\n");
    from_server = open(ACK, O_RDONLY);

    char f[HANDSHAKE_BUFFER_SIZE];
    printf("reading server message...\n");
    read(from_server, f, sizeof(f));
    remove(ACK);

    printf("sending response...\n", f);
    write(*to_server, f, sizeof(f));

    return from_server;
}