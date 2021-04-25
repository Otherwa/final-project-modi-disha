/* Message Queue application for AESD final project. This file implements Message queue receive code 
 * Author: Disha Modi */
// Ref: https://www.softprayog.in/programming/interprocess-communication-using-posix-message-queues-in-linux

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define SERVER_QUEUE_NAME   "/sp-example-server"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10

int main (int argc, char **argv)
{
    char client_queue_name [64];
    mqd_t qd_server;   // queue descriptors

    // create the client queue for receiving messages from server
    sprintf (client_queue_name, "/sp-example-client-%d", getpid ());

    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    if ((qd_server = mq_open (SERVER_QUEUE_NAME, O_WRONLY)) == -1) {
        perror ("Client: mq_open (server)");
        exit (1);
    }

    char in_buffer [MSG_BUFFER_SIZE];

    printf ("Ask for a token (Press <ENTER>): ");

    char temp_buf [10];

    while (fgets (temp_buf, 2, stdin)) {

        // send message to server
        if (mq_send (qd_server, client_queue_name, strlen (client_queue_name) + 1, 0) == -1) {
            perror ("Client: Not able to send message to server");
            continue;
        }

        // display token received from server
        printf ("Client: Send message to server: %s\n\n", client_queue_name);

        printf ("Ask for a token (Press ): ");
    }

    printf ("Client: bye\n");

    exit (0);
}

