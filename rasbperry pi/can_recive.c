#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>

int main() {
    int s;
    struct sockaddr_can addr;
    struct ifreq ifr;
    struct can_frame frame;

    // Create a socket
    if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
        perror("Socket creation error");
        return 1;
    }

    // Specify the CAN interface
    strcpy(ifr.ifr_name, "can0");
    ioctl(s, SIOCGIFINDEX, &ifr);

    // Bind the socket to the CAN interface
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    bind(s, (struct sockaddr *)&addr, sizeof(addr));

    FILE *file = fopen("output.txt", "w"); // Open a file in write mode (overwrite old values)

    while (1) {
//---------------------------------------start of receving----------------------------------
        read(s, &frame, sizeof(struct can_frame));
        printf("CAN ID: %03X\n", frame.can_id);
        printf("Data Length: %d\n", frame.can_dlc);
        printf("Data: ");
        for (int i = 0; i < frame.can_dlc; i++) {
            printf("%02X ", frame.data[i]); // to print the data in terminal
            fprintf(file, "%02X ", frame.data[i]); // to print the data into file
        }

        fflush(file); // Flush the file buffer
        fseek(file, 0, SEEK_SET);// Move the file pointer to the beginning of the file to overwrite old values
        printf("\n");
//---------------------------------------end of receving----------------------------------

//---------------------------------------start of transmiting----------------------------------




//---------------------------------------end of transmiting----------------------------------

    }

    fclose(file); // Close the file
    close(s);

    return 0;
}
