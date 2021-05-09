#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define BUF_SIZE 1024
#define PORT_NUM "6666"

void errorExit(char *format, const char *text) {
    printf(format, errno, text);
    perror("");
    exit(EXIT_FAILURE);
}

int establish_connection(const char* hostname) {
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    hints.ai_family = AF_UNSPEC;                /* Allows IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV;

    if (getaddrinfo(hostname, PORT_NUM, &hints, &result) != 0)
        errorExit("error %d while getting address of %s", hostname);

    /* Walk through returned list until we find an address structure
       that can be used to successfully connect a socket */

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd == -1)
            continue;                           /* On error, try next address */

        if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
            break;                              /* Success */

        /* Connect failed: close this socket and try next address */

        close(sfd);
    }

    if (rp == NULL){
        printf("Could not connect socket to any address\n");
    }

    freeaddrinfo(result);
    return sfd;
}

int open_file(const char* filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        errorExit("error %d while opening file %s", filename);
    }
    return fd;
}

int
main(int argc, char *argv[])
{
    ssize_t num_read;
    ssize_t tot_sent = 0;
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    char buf[BUF_SIZE];

    if (argc < 3 || strcmp(argv[1], "--help") == 0)  {      
        printf("%s server-host file \n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sfd = establish_connection(argv[1]);
    int fd = open_file(argv[2]);

    //sleep(300);
    while ((num_read = read(fd, buf, BUF_SIZE)) > 0) {
        if (write(sfd, buf, num_read) !=  num_read)
            errorExit("error %d while writing to socket %s\n", "");

        tot_sent += num_read;
        printf("Total sent: %zd\n", tot_sent); 
    }

    if (num_read == -1) errorExit("error %d while reading file %s\n", argv[2]);
    if (close(fd) == -1) perror("close input");


    printf("Total sent: %zd\n", tot_sent);   /* Includes '\n' */
    //sleep(5);

    exit(EXIT_SUCCESS);                         /* Closes 'cfd' */
}