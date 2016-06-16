/*
 * http://tim.dysinger.net/posts/2013-09-16-getting-started-with-nanomsg.html
 * 
gcc pipeline.c /usr/local/lib/libnanomsg.a -o pipeline
 * 
 # run this:./pipeline node0 ipc:///tmp/pipeline.ipc 
 # and this:node0=$!
 # at the same time
 # the node0 variable gets the process id of the pipeline run
 # if both of those succeed, then sleep 1 is run
 # The node0() function is a while(1) loop, so save off its
 # process-id ("node0=$!") so that is can later be killed off with
 # "kill $node0".  This is the receiving node, so it waits to 
 # receive stuff indefinitely.  Node1 sends stuff, so it sends it
 # and then exits.
./pipeline node0 ipc:///tmp/pipeline.ipc & node0=$! && sleep 1
 * 
./pipeline node1 ipc:///tmp/pipeline.ipc "Hello, World!"
 * 
./pipeline node1 ipc:///tmp/pipeline.ipc "Goodbye."
 * 
kill $node0
 * 
bash-4.3$ ls /tmp -l
srwxr-xr-x 1 ken ken  0 May  4 23:30 pipeline.ipc
 * 
 */

#include <assert.h>
/* #include <libc.h> */
#include <string.h>
#include <stdio.h>
#include <nanomsg/nn.h>
#include <nanomsg/pipeline.h>

#define NODE0 "node0"
#define NODE1 "node1"
/*
int node0(const char *url) {
    int sock = nn_socket(AF_SP, NN_PULL);
    assert(sock >= 0);
    assert(nn_bind(sock, url) >= 0);
    while (1) {
        char *buf = NULL;
        int bytes = nn_recv(sock, &buf, NN_MSG, 0);
        assert(bytes >= 0);
        printf("NODE0: RECEIVED \"%s\"\n", buf);
        nn_freemsg(buf);
    }
}

int node1(const char *url, const char *msg) {
    int sz_msg = strlen(msg) + 1; // '\0' too
    int sock = nn_socket(AF_SP, NN_PUSH);
    assert(sock >= 0);
    assert(nn_connect(sock, url) >= 0);
    printf("NODE1: SENDING \"%s\"\n", msg);
    int bytes = nn_send(sock, msg, sz_msg, 0);
    assert(bytes == sz_msg);
    return nn_shutdown(sock, 0);
}

int main(const int argc, const char **argv) {
    if (strncmp(NODE0, argv[1], strlen(NODE0)) == 0 && argc > 1) {
        fprintf(stderr, "node: %s\n", argv[1]);
        return node0(argv[2]);
    } else if (strncmp(NODE1, argv[1], strlen(NODE1)) == 0 && argc > 2) {
        fprintf(stderr, "node: %s\n", argv[1]);
        return node1(argv[2], argv[3]);
    } else {
        fprintf(stderr, "node: %s\n", argv[1]);
        fprintf(stderr, "Usage: pipeline %s|%s <URL> <ARG> ...'\n",
                NODE0, NODE1);
        return 1;
    }
}
*/