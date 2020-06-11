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
#include "datapkt_ops.h"

// struct data_t
// {
//     int data;
// };

struct mqueue_node_t **qset = NULL;
struct qtracker_t *qtrack = NULL;

struct qnode_t
{
    int pkt_id;
    double q_start;
    double q_stop;
    double q_time;
    void *dataptr;
};


struct mqueue_node_t
{
    struct qnode_t *pkt;
    struct mqueue_node_t *next;
};


struct mqueue_t
{
    int queue_id;
    struct mqueue_node_t *qnode;
};


struct qtracker_t
{
    struct mqueue_node_t *root;
    struct mqueue_node_t *curr;
    int head;
    int tail;
};

//##########################
// Queue creation functions
//##########################

int q_create(int MQ_NUM, int QUEUE_LEN)
{
    qset = (struct mqueue_node_t **)malloc(MQ_NUM * sizeof(struct mqueue_node_t **));
    for(int i=0; i<MQ_NUM; i++)
    {
        *(qset+i) = (struct mqueue_node_t *)malloc(QUEUE_LEN * sizeof(struct mqueue_node_t *));
    }

    qtrack = malloc(MQ_NUM * sizeof(struct qtracker_t *));

    for(int i=0; i<MQ_NUM; i++){
        (qtrack+i)->root = *(qset+i);
        (qtrack+i)->curr = (qtrack+i)->root;
        (qtrack+i)->head = 0;
        (qtrack+i)->tail = 0;
    }
    
    printf("Message queues created.\n");

    return 0;
}


void q_enqueue(int qnum, void * dp)
{
    (qtrack+qnum)->curr->qnode

}