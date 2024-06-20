#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <sys/ioctl.h>
#include <stdint.h>

#define CAN_INTERFACE "can0"

int initCANSocket() {
    int sockfd;
    struct sockaddr_can addr;
    struct ifreq ifr;

    // Create a socket
    if ((sockfd = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
        perror("Error creating socket");
        return -1;
    }

    // Set the CAN interface name
    strcpy(ifr.ifr_name, CAN_INTERFACE);
    ioctl(sockfd, SIOCGIFINDEX, &ifr);

    // Bind the socket to the CAN interface
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Error binding socket");
        close(sockfd);
        return -1;
    }

    return sockfd;
}

int sendCANData(int sockfd, canid_t can_id, uint8_t *data, size_t data_len) {
    struct can_frame frame;

    // Set the CAN frame parameters
    frame.can_id = can_id;
    frame.can_dlc = data_len;
    memcpy(frame.data, data, data_len);

    // Send the CAN frame
    if (write(sockfd, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
        perror("Error sending CAN frame");
        return -1;
    }

    return 0;
}

int main() {
    int sockfd;
    struct can_frame recv_frame;

    // Initialize CAN socket
    sockfd = initCANSocket();
    if (sockfd < 0) {
        fprintf(stderr, "Error initializing CAN socket\n");
        return 1;
    }

    // Send CAN frame
    FILE *file = fopen(filename, "rb");
    unsigned char buffer[8];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        // use 8 byte data
        canid_t can_id = 0x000;        
        size_t data_len = sizeof(buffer);
        if (sendCANData(sockfd, can_id, buffer, data_len) == 0) {
            // Wait until receiving one byte in the CAN bus
            ssize_t bytes_received;
            do {
                bytes_received = read(sockfd, &recv_frame, sizeof(struct can_frame));
            } while (bytes_received != sizeof(struct can_frame) || recv_frame.can_dlc != 1);
        }
    }

    // Close the socket and file
    fclose(file);
    close(sockfd);

    return 0;
}
