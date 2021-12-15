#include "pipe_networking.h"
#include <ctype.h>

char *toUpper(char line[]) {
    char * input = line;
    int i = 0;
    // process input str into all caps
    for (i = 0; i < strlen(line); i++) {
        line[i] = toupper(line[i]);
    }
    return line;
}

int main() {
    int to_client;
    int from_client;

  
    while(1) {
        from_client = server_handshake( &to_client );
        char message[BUFFER_SIZE];
        while(read(from_client, message, sizeof(message))) {
            printf("processing...\n");
            toUpper(message);
            write(to_client, message, sizeof(message));
        }
    }
}

// int main() {

//   int to_client;
//   int from_client;

//   while (1) {
//     from_client = server_handshake( &to_client );

    
//     char clientmsg[BUFFER_SIZE];

//     while (read(from_client, clientmsg, BUFFER_SIZE)) {
//       printf("Processing\n");
//       toUpper(clientmsg);
//       write(to_client, clientmsg, BUFFER_SIZE);
//     }
//   }
// }