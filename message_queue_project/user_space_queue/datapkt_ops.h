#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <inttypes.h>
#include <semaphore.h>
#include <sys/time.h>
#include <sys/timerfd.h>
#include <string.h>
#include <time.h>
#include <math.h>

// struct data_t
// {
//     int data;
// };


// struct qnode_t
// {
//     int pkt_id;
//     double q_start;
//     double q_stop;
//     struct data_t *dataptr;
// };


// struct mqueue_node_t
// {
//   struct datapkt_t *pkt;
//   struct mqueue_node_t *next;
// };


// struct mqueue_t
// {
//     int queue_id;
//     struct mqueue_node_t *qnode;
// };


// struct qtracker_t
// {
//     struct mqueue_node_t *root;
//     struct mqueue_node_t *head;
//     struct mqueue_node_t *tail;
// };




