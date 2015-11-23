/* This is based on the btgatt-client.c code from the BlueZ project
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/l2cap.h>

#define ATT_CID 4

int main(int argc, char **argv)
{
    struct sockaddr_l2 srcaddr, dstaddr;
    int sockfd, status;
    unsigned short cid = 4;
    unsigned short psm = 0;
    char src[18] = "5C:F3:70:6A:B4:C0";
    char dst[18] = "20:C3:8F:F6:60:9E";
	
    sockfd = socket(AF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP);
    
    memset(&srcaddr, 0, sizeof(srcaddr));
    str2ba( src, &srcaddr.l2_bdaddr );
    srcaddr.l2_family = AF_BLUETOOTH;
    srcaddr.l2_cid = htobs(ATT_CID);
    srcaddr.l2_bdaddr_type = BDADDR_LE_PUBLIC;
    
    status = bind(sockfd, (struct sockaddr *)&srcaddr, sizeof(srcaddr));
    if ( status < 0 ) {
        perror("uh oh");
        close(sockfd);
        return -1;
    }
    
    memset(&dstaddr, 0, sizeof(dstaddr));
    str2ba( dst, &dstaddr.l2_bdaddr );
    dstaddr.l2_family = AF_BLUETOOTH;
    dstaddr.l2_cid = htobs(ATT_CID);
    dstaddr.l2_bdaddr_type = BDADDR_LE_PUBLIC;

    // connect to server
    printf("Connecting to device\n");
    status = connect(sockfd, (struct sockaddr *)&dstaddr, sizeof(dstaddr));
    if ( status < 0 ) {
        perror("uh oh");
        close(sockfd);
        return -1;
    }
    // send a message
    if( status == 0 ) {
        printf("Successfully connected\n");
        unsigned int i;
        // Write request = 0x12
        // Handle value = 0x0012 (reversed below due to endianness)
        char str[10] = "\x12\x12\x00hello!\n";
        for (i = 0; i < 5; i++) {
            status = write(sockfd, str, 10);
            sleep(1);
        }
    }
    
    printf("Done, closing socket\n");
    close(sockfd);
    return 0;
}
