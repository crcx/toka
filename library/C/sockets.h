int cadd(int a,int b);
int pBind(int port);
int pConnect(const char *host, int port);
int pAccept(int sockfd);
int pRead(int sockfd, void *buffer, int length);
int pWrite(int sockfd, const char *data, int length);
int pClose( int sockfd );
