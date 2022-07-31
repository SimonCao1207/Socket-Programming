#include "ftp_test.h"


// NOTE: Please make sure that you fully understand the description before starting the coding. It will save your time!

// Initialize a client socket.
// To ensure the client socket connect with the target server,
// you should pay attention to set the parameters "ip address" and "port" correctly.
// Remind that we assumed "./client -h 127.0.0.1 -p 8080".
int init(int argc, char *argv[]){

  /*####################################################################################*/
  /*###################### DO NOT MODIFY THE CODE BELOW THIS LINE ######################*/
  int sock;
  if(argc != 5 || strcmp(argv[1], "-h") || strcmp(argv[3], "-p")){
    printf("unvalid command line\n");
    printf("./client -h <address> -p <port>\n");
    exit(1);
  }
  /*###################### DO NOT MODIFY THE CODE ABOVE THIS LINE ######################*/
  /*####################################################################################*/

  // client socket initialization
  /* Your Code */
  int port = 8080;
  const char * ip = "127.0.0.1";
  struct sockaddr_in serveraddr;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if(sock == -1){
    printf("socket error\n");
    exit(1);
  }
  bzero((char *) &serveraddr, sizeof(serveraddr));
  
  // SETTING
  serveraddr.sin_family = AF_INET; // Address family
  serveraddr.sin_addr.s_addr = inet_addr(ip); // IP address 127.0.0.1
  serveraddr.sin_port = htons(port); // PORT is 8080
  
  // connection test
  /* Your Code */
  // printf("%u\n", inet_addr(ip));
  if((connect(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr))) < 0){
    printf("connect error\n");
    return False;
  } 
  else {
    printf("connect success\n");
  }
  return sock; // return initialized socket
}

// Implement "ls" function.
// NOTE: This is optional and will not be used in grading. 
// For those who get stuck in error, this function may help you get a current directory or something related to this assignment.
void ls(){
  /* Your Code */
  DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (strcmp(dir->d_name, ".") && strcmp(dir->d_name, ".."))
                printf("%s  ", dir->d_name);
        }
        printf("\n");
        closedir(d);
    }
}

// Implement "changedir" function.
// Change the current directory to target directory.
void changedir(const char* name){ 
  /* Your Code */
  if(chdir(name) < 0){
      printf("changedir error\n");
      exit(1);
  }
}

// Implement "Upload" function.
// Input : socket & file_name you want to upload to server
// Return : if the socket success to upload the accesible file, return "True". Otherwise, return "False".
int upload(int sock, const char* file_name){
  /* Your Code */
    FILE * fp = fopen(file_name, "rb");
    if (fp  == NULL){
      printf("reading file error\n");
      exit(1);
      return False;
    }
    fseek(fp, 0, SEEK_END);
    long filesize = ftell(fp);
    rewind(fp);
    unsigned char data[filesize]={0};
    const char* signal = "u";
    char filename[strlen(file_name)];
    strcpy(filename, file_name);
    
    int nread = fread(data,1,filesize,fp);
    
    printf("Sending file name %s\n", filename);
    
    if (send(sock, signal, strlen(signal), 0) == -1) {
      perror("Error in sending signal\n");
      exit(1);
    }
    
    if (send(sock, filename, sizeof(filename), 0) == -1) {
      perror("Error in sending file name\n");
      exit(1);
    }
    printf ("Sending data: %ld bytes.\n",filesize);
    
    if (send(sock, data, sizeof(data), 0) == -1) {
      perror("Error in sending file");
      exit(1);
    }
    fclose(fp);
    return True;
}
// Implement "Download" function.
// Input : socket & file_name you want to download from server
// Return : if the socket success to download the accessible file, return "True". Otherwise, return "False".
int download(int sock, const char* file_name){
  /* Your Code */
    FILE * fp = fopen(file_name, "w");
    if (fp  == NULL){
      printf("reading file error\n");
      exit(1);
      return False;
    }
    
    unsigned char buffer[100000];
    const char* signal = "d";
    int bytesRecv;
    
    if (send(sock, signal, strlen(signal), 0) == -1) {
      perror("Error in sending signal\n");
      exit(1);
    }
    
    if (send(sock, file_name, 1000, 0) == -1) {
      perror("Error in sending file name\n");
      exit(1);
    }
    
    if ((bytesRecv = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
        fwrite(buffer, 1, bytesRecv,fp);
        printf ("Receieve data: %d bytes.\n",bytesRecv);
        printf("Done Downloading in Client\n");
    } else {
        return False;
    }
    fclose(fp);
    return True;
}

// Implement "Terminate" function.
// Terminate function should send the terminate signal to server.
void terminate(int sock){
  /* Your Code */
    const char* signal = "t";

    if (send(sock, signal, strlen(signal), 0) == -1) {
      perror("Error in sending signal\n");
      exit(1);
    }
}
