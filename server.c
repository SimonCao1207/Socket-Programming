#include "ftp_test.h"

void currentDir(){
    char path[200];
    getcwd(path, 200);
    printf("Current working directory: %s\n", path);
}
// NOTE: Please make sure that you fully understand the description before starting the coding. It will save your time!

int main(int argc, char *argv[]){

  /*####################################################################################*/
  /*###################### DO NOT MODIFY THE CODE BELOW THIS LINE ######################*/
  int serv_sock; // server socket
  int clnt_sock; // client socket
  if(argc != 3 || strcmp(argv[1], "-p")){
    printf("invalid command line\n");
    printf("./server -p <port>\n");
    exit(1);
  }
  /*###################### DO NOT MODIFY THE CODE ABOVE THIS LINE ######################*/
  /*####################################################################################*/
  
  // Initialize a server socket.
  // To ensure the server socket connect with client socket, 
  // you should initialize the server socket with the proper settings.
  // Note that you should use "INADDR_ANY" option when you setup the server address.
  /* Your Code */
  int port = 8080, new_sockfd;
  struct sockaddr_in serveraddr;
  struct sockaddr_in clntaddr;
  
  serv_sock = socket(AF_INET, SOCK_STREAM, 0);
  if(serv_sock == -1){
    printf("socket error\n");
    exit(1);
  }
  else {
    printf("socket success\n");
  }
  bzero((char *) &serveraddr, sizeof(serveraddr));
  bzero((char *) &clntaddr, sizeof(clntaddr));
  
  // SETTING SERVER ADDRESS
  serveraddr.sin_family = AF_INET; // Address family
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); // IP address in byte order
  serveraddr.sin_port = htons(port); // PORT is 8080
  
  /*-----------------------------------------------------------------------------------------*/

  // Bind the server socket .
  /* Your Code */
  if(bind(serv_sock, (SA *)&serveraddr, sizeof(serveraddr)) < 0){
    printf("bind error\n");
    exit(1);
  }
  else {
    printf("bind success\n");
  }
  
  /*-----------------------------------------------------------------------------------------*/
  
  // Set the server socket to listening mode.
  /* Your Code */

  printf("Server start: listen on port %s\n", argv[2]);
  if(listen(serv_sock, 1024) < 0){
    printf("listen error\n");
    exit(1);
  } else {
    printf("listen success\n");
  }
  /*-----------------------------------------------------------------------------------------*/
  
  // Accept client sockets if they request to accept.
  /* Your Code */
  
  socklen_t addrlen = sizeof(clntaddr);
  new_sockfd = accept(serv_sock, (SA *)&clntaddr, &addrlen);
  
  if(new_sockfd == -1){
    printf("accept error\n");
    exit(1);
  } else {
    printf("accept success\n");
  }
  /*-----------------------------------------------------------------------------------------*/
  
  // By now, we have initialized the server socket and made the socket accept the client sockets.
  // We will then implement the auxiliary loop to let the server socket dealing with the requests from the clients.
  // Funtions that you should implement are as follows: "Upload", "Download", and "Terminate".
  
  
  
  
  while(True){
    char signal[1];
    recv(new_sockfd, signal, 1, 0);
    printf("Signal %s\n", signal);
    // upload
    if(!strcmp(signal, "d")){
      /* Your Code */
        printf("...SERVER SENDING....\n");
        int bytesRecv;
        char filename[1000];
        recv(new_sockfd, filename, sizeof(filename), 0);
        printf("Recieved file name is %s\n", filename);
        changedir("server_files");
        FILE *fp = fopen(filename, "r");
        fseek(fp, 0, SEEK_END);
        long filesize = ftell(fp);
        rewind(fp);
        unsigned char data[filesize]={0};
        printf("File size = %d\n", filesize);
        fread(data,1,filesize,fp);
        if ((send(new_sockfd, data, sizeof(data), 0)) < 0){
            printf("Error server sending file\n");
        }
        // ls();
        break;
    }

    // download
    else if(!strcmp(signal, "u")){
      /* Your Code */
        printf("...RECEIVING....\n");
        char buffer[10000];
        int bytesRecv;
        int cnt = 0;
        char filename[1000];
        recv(new_sockfd, filename, sizeof(filename), 0);
        // printf("Receive file name is %s\n", filename);
        changedir("server_files");
        FILE *fp = fopen(filename, "w");
        if ((bytesRecv = recv(new_sockfd, buffer, sizeof(buffer), 0)) > 0){
            fwrite(buffer, 1,bytesRecv,fp);
            printf("Done Downloading in Server\n");
        }
        // ls();
      }
      
    // Terminate
    else if(0){
      /* Your Code */
      printf("to be continued");
    }
  }
}
