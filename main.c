#include "ftp_test.h"

int main (int argc, char *argv[])
{  
    /* Your Code */
    // Test your implementation here.
    //
    // Example:
    for (int i = 0;i < argc;i++)
    printf("%s ", argv[i]);
    printf("\n");
    
    int sock = init(argc, argv);
    if (sock) {
        printf("dit me\n");
    }
    else {
        printf("vai lon\n");
    }
    
    
    changedir("client_files");
    ls();
    
    // if (upload(sock, "../ironman.jpg") == True)
    // printf("send success\n");
    
//     changedir("../server_files");
//     ls();
    
//     changedir("../client_files");
//     ls();
    
    // if (download(sock, "../Thanos.jpg") == True)
    // printf("recv success\n");
    
    // ls();
    // changedir("../server_files");
    // ls();
}