//
// Created by Mehdi Khenissi on 06/02/2022.
//
#include "comman.h"
#define PORT 3000
#define  MAXLINE 4096


int main(int argc, char ** argv) {
    int new_socket, main_soket, n;
    struct sockaddr_in socket_res;
    int addrlen = sizeof(socket_res);

    uint8_t  buff[MAXLINE+1];
    uint8_t  recvline[MAXLINE+1];

    main_soket =  try(socket(AF_INET, SOCK_STREAM, 0));

    bzero(&socket_res, sizeof(socket_res));
    socket_res.sin_family = AF_INET;
    socket_res.sin_addr.s_addr = htonl(INADDR_ANY);
    socket_res.sin_port = htons(PORT);

    try(bind(main_soket, (struct sockaddr *) &socket_res, sizeof(socket_res)));
    try(listen(main_soket, 10));

    for(;;) {
        struct sockaddr_in addr;
        socklen_t  addr_len;

        printf("waiting for connection on port %d\n", PORT);
        fflush(stdout);
        new_socket = try(accept(main_soket, (struct sockaddr *) &socket_res, (socklen_t*) &addrlen));

        memset(recvline,0,MAXLINE);

        while((n = try(read(new_socket, recvline, MAXLINE-1))) > 0) {
            fprintf(stdout, "\n%s", recvline);
          //  if(recvline[MAXLINE-1] =='\n') {
                break;
          //  }
        }


        memset(recvline,0,MAXLINE);

        if(n < 0) {
            printf("error");
        }


        snprintf((char*) buff, sizeof(buff), "HTTP/1.1 200 OK\r\n\r\n<h1>Hello this my first mini web server </h1> <br> <p> its working this is cool <p> ");

        try(write(new_socket, (char *)buff, strlen((char *) buff)));
        close(new_socket);
    }

}
