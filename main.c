/*
 * Uiletie
 * License: LGPL v2.1
 * Author: Ken Galle ken.galle@rainshowers.org
 */

/* 
 * File:   main.c
 * Author: Ken Galle <ken@rainshowers.org>
 * Borrowing heavily from nanomsg and parson example code.
 * 
 * Created on May 9, 2016, 7:48 PM
 */
/*
 * Test using:
# pwd: /home/ken/nethome/nanomsg/Pipeline/dist/Debug/GNU-Linux
bash-4.3$ ./pipeline node1 ipc:///tmp/pipeline.ipc "[ { \"name\" : \"QUIT\" } ]"
node: node1
NODE1: SENDING "QUIT"

*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <nanomsg/nn.h>
#include <nanomsg/pipeline.h>
#include "parson.h"
/*
 * 
 */
int main(int argc, char** argv) {
    fprintf(stderr, "starting server: %s\n", argv[1]);
    return uliletie_serve(argv[1]);
}

/*
 * to start with, just parse out the command.
 */
const char *uliletie_parse(char *buf) {
    JSON_Value *root_value;
    JSON_Array *commands;
    JSON_Object *command;
    int i;
    
    /* parsing json and validating output */
    root_value = json_parse_string(buf);
    if (json_value_get_type(root_value) != JSONArray) {
/*        system(cleanup_command); */
        return;  /* return what - this need to be a value */
    }

    /* getting array from root value and printing commit info */
    commands = json_value_get_array(root_value);
    printf("%-10.10s %-10.10s %s\n", "Date", "SHA", "Author");
    for (i = 0; i < json_array_get_count(commands); i++) {
        command = json_array_get_object(commands, i);
        const char *command_string = json_object_dotget_string(command, "name");
        return command_string;
    }
}

int uliletie_serve(char *url) {
    int sock = nn_socket(AF_SP, NN_PULL);
    assert(sock >= 0);
    assert(nn_bind(sock, url) >= 0);
    while (1) {
        char *buf = NULL;
        int bytes = nn_recv(sock, &buf, NN_MSG, 0);
        assert(bytes >= 0);
        printf("Uiletie serve received: %s\n", buf);
        // parse the input
        const char *command = uliletie_parse(buf);
        if (strcmp("QUIT", command) == 0) {
            nn_freemsg(buf);
            break;
        }
    }
    return 0;
}
