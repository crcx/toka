/******************************************
 *|F|
 *|F| FILE: sockets.c
 *|F|
 ******************************************/

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>

#define __USE_BSD 1
#include <string.h>
 
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <dirent.h>

#include <netdb.h>
#include <unistd.h>

#include "sockets.h"


/******************************************
 *|F| int pBind(int port)
 *|F| Bind a socket to a port, and return it.
 *|F|
 ******************************************/
int pBind(int port)
{
  int sockfd;
  struct sockaddr_in serv_addr;
  int on   = 1;
  
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
  {
    fprintf(stderr, "ERROR opening socket\n"); 
    return -1;
  }
  
  
  /* Enable address reuse */
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
  
  memset(&serv_addr, '\0', sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(port);
  
  /* bind */
  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
  {
    fprintf(stderr, "ERROR on binding\n");
    return -1;
  }
  
  /* queue five connections. */
  listen(sockfd, 5);
  
  /* Return socket */
  return sockfd;
}


/******************************************
 *|F| int pConnect(const char *host, int port)
 *|F| Connect a socket to a host/port, and return it.
 *|F|
 ******************************************/
int pConnect(const char *host, int port)
{
  struct sockaddr_in sa;
  struct hostent *hp;
  int ret,sockfd;
  
  /* Get the host. */ 
  hp = gethostbyname(host);
  bcopy((char *)hp->h_addr, (char *)&sa.sin_addr, hp->h_length);
  sa.sin_family = hp->h_addrtype;
  sa.sin_port = htons(port);
  sockfd = socket(hp->h_addrtype, SOCK_STREAM, 0);
  
  /* connect */
  ret = connect(sockfd, (struct sockaddr *)&sa, sizeof(sa));
  if (ret < 0)
  {
    fprintf(stderr, "Failed to connect\n");
    close(sockfd);
    return -1;
  }
  
  /* Return socket */
  return sockfd;
}



/******************************************
 *|F| int pAccept(int sockfd)
 *|F| Accept a new connection upon a socket.  Return the new client.
 *|F|
 ******************************************/
int pAccept(int sockfd)
{
  int newsockfd;
  socklen_t clilen;
  struct sockaddr_in  cli_addr;
  
  /* accept() */
  clilen = sizeof(cli_addr);
  newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
  
  /* Return error on failure */
  if (newsockfd < 0)
  {
    fprintf(stderr, "ERROR on accept\n");
    return -1;
  }
  
  /*
   * Return the new socket and the connecting IP address.
   */
  return newsockfd;
}



/******************************************
 *|F| int pRead(int sockfd, void *buffer, int length)
 *|F| Read from a socket, return length.
 *|F|
 ******************************************/
int pRead(int sockfd, void *buffer, int length)
{
  int n = 0;

  memset(buffer, '\0', length);

  n = read(sockfd, buffer, length);
  
  if (n == -1)
  {
    fprintf(stderr, "Problem reading from socket\n");
    return -1;
  }
  
  /* return length. */
  return n;
}



/******************************************
 *|F| int pWrite(int sockfd, const char *data, int length)
 *|F| Write data to a socket.
 *|F|
 *
 * - February 24, 2007
 *   Replaced the loop by a straight write()
 *   This needs further testing.
 ******************************************/
int pWrite(int sockfd, const char *data, int length)
{
  int sent = write(sockfd, data, length);
  if (sent <= 0)
  {
    fprintf( stderr, "Problem writing to socket\n" );
    return -1;
  }
  else
    return sent;
}



/******************************************
 *|F| int pClose(int sockfd)
 *|F| Close a socket.
 *|F|
 ******************************************/
int pClose(int sockfd)
{
  close(sockfd);
  return 0;
}
