#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <inttypes.h>
#include <semaphore.h>
#include <sys/time.h>
#include <sys/timerfd.h>
#include <time.h>
#include <math.h>
#include <errno.h>
#include <sched.h>
#include <string.h>
#include <linux/input.h>

//######################################################
//
// Global variable & functions declarations area
//
//######################################################

#define main_runtime 5000        // Main program runtime in ms

const char *mDevice = "/dev/input/event2";  //Storing path of mouse event. Change this event number if your machine shows different number for mouse event
struct input_event ie;

const int t_periods[] = {25,40,75,60};  // Periodic thread periods

pthread_cond_t start, left_mouse, right_mouse;                       // Condition variable for start sync
pthread_mutex_t start_mut, left_mouse_mut, right_mouse_mut;          // Mutex used in conjunction with condition variables

int stp_flag = 1;

//===============================
// Thread description parameters
//===============================

#define P_SENDER_THREAD 4         // Number of periodic sender pthreads
#define A_SENDER_THREAD 2         // Number of aperiodic sender pthreads

//==============================
// Thread priority attributes
//==============================
#define P_SENDER_PRIO 40
#define A_SENDER_PRIO 60
#define MOUSE_PRIO 99

//==============================
// Thread context structs
//==============================
struct t_data
{
    int t_id;
    int t_num;
    int t_runs;
};

//######################################################
//
// Thread functions
//
//######################################################

// Thread function for periodic sender threads
//---------------------------------------------
void *psender_thread_func(void *argptr)
{
    // Thread function computations
    struct t_data *tptr;
    tptr = (struct t_data *)argptr;

    printf("Periodic thread invoked : %d with period %d us\n",tptr->t_num,t_periods[tptr->t_num]);

    // Each thread wait here till conditional variable broadcasts
    pthread_mutex_lock(&start_mut);
    int cret = pthread_cond_wait(&start,&start_mut);            // All threads waiting on start condition variable to start simultaneously
    if(cret!=0)
        printf("Periodic condition variable error %d\n",cret);
    pthread_mutex_unlock(&start_mut);
    
    struct timespec base,period;
    period.tv_sec = (t_periods[tptr->t_num])/1000;
    period.tv_nsec = (t_periods[tptr->t_num])*1000000ul;

    clock_gettime(CLOCK_MONOTONIC,&base);

    while(stp_flag)
    {
        // Arm for next timer deadline
        base.tv_sec += period.tv_sec;
        base.tv_nsec += period.tv_nsec;
        if(base.tv_nsec > 1000000000ul)
        {
            base.tv_sec++;
            base.tv_nsec = 0;
        }

        // Thread compute
        printf("Periodic sender thread running : %d\n",tptr->t_num);
        tptr->t_runs += 1;

        clock_nanosleep(CLOCK_MONOTONIC,TIMER_ABSTIME,&base,0);     // Takes time provided in time object as absolue time and thread goes to sleep
    }
    printf("Periodic thread %d was called %d times.\n", tptr->t_num, tptr->t_runs);   

    pthread_exit(NULL);
}



// Thread function for aperiodic sender threads
//----------------------------------------------
void *asender_thread_func(void *argptr)
{
    // Thread function computations
    struct t_data *tptr;
    tptr = (struct t_data *)argptr;

    printf("Aperiodic thread invoked : %d\n",tptr->t_num);

    while(stp_flag)
    {
        // Each thread wait here till respective async event conditional variable broadcasts
        if(tptr->t_num == 0)    // Left mouse click event compute
        {
            pthread_mutex_lock(&left_mouse_mut);
            int cret = pthread_cond_wait(&left_mouse,&left_mouse_mut);      // waiting on left click event
            if(cret!=0)
                printf("Periodic condition variable error %d\n",cret);
            pthread_mutex_unlock(&left_mouse_mut);
            if(stp_flag==0)
                break;
        }

        if(tptr->t_num == 1)    // Right mouse click event compute
        {
            pthread_mutex_lock(&right_mouse_mut);
            int cret = pthread_cond_wait(&right_mouse,&right_mouse_mut);      // waiting on right click event
            if(cret!=0)
                printf("Periodic condition variable error %d\n",cret);
            pthread_mutex_unlock(&right_mouse_mut);
            if(stp_flag==0)
                break;
        }

        printf("Aperiodic sender thread running : %d\n",tptr->t_num);
        tptr->t_runs += 1;
    }
    
    printf("Aperiodic thread %d was called %d times.\n", tptr->t_num, tptr->t_runs);   

    pthread_exit(NULL);
}




//##################
//
// Mouse thread
//
//##################

void* mouse_read(void* arg)  // Thread function to detect mouse click event and broadcast corresponding condition variables
{
    int fd, bytes;
    fd = open(mDevice,O_RDWR);     // Opens event file located in /dev/input/eventX

    if(fd == -1) //Because open returns -1 on occurence of error
    {
        printf("ERROR Opening %s\n", mDevice);
    }

    while(stp_flag == 0)
    {
        bytes = read(fd, &ie, sizeof(struct input_event)); 

        if(bytes > 0)
        {
            // broadcasting of condition variable based on left or right click
            if((ie.code == BTN_LEFT) && (ie.value == 0))
                pthread_cond_broadcast(&left_mouse);                     
            else if((ie.code == BTN_RIGHT) && (ie.value == 0))
                pthread_cond_broadcast(&right_mouse);
        }
     }

     return NULL;
}

//######################################################
//
// Main
//
//######################################################


int main(int argc, char const *argv[])
{
    //=========================================
    // Thread Initializations
    //=========================================
    int tret=-1;

    pthread_t P_tid[P_SENDER_THREAD];
    pthread_t A_tid[A_SENDER_THREAD];

    pthread_attr_t fifo_attr;
    pthread_attr_init(&fifo_attr);
    // pthread_attr_setinheritsched(&fifo_attr,PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&fifo_attr,SCHED_FIFO);

    struct sched_param param;


    //=========================================
    // Thread conditional variables
    //=========================================
    int cret = pthread_cond_init(&start,NULL);            // initialising condition variables
    if(cret!=0)
        printf("Start condn init error %d\n",cret);

    pthread_mutex_init(&start_mut,NULL);                 // Initialising condition variable mutexes(thread mutex are different)


    //=========================================
    // Set CPU affinity
    //=========================================
    // Bitset where each bit represents a CPU.
    cpu_set_t cpuset;
    // Initializes the CPU set to be the empty set.
    CPU_ZERO(&cpuset);
    // CPU_SET: This macro adds cpu to the CPU set.
    CPU_SET(0, &cpuset);


    //=========================================
    // Threads creation
    //=========================================

    //Creating Periodic Sender threads
    //----------------------------------
    param.sched_priority = P_SENDER_PRIO;
    pthread_attr_setschedparam(&fifo_attr, &param);

    struct t_data *dptr[P_SENDER_THREAD];

    for(int i=0; i<P_SENDER_THREAD; i++)
    {
        dptr[i] = (struct t_data *)malloc(sizeof(struct t_data));
        dptr[i]->t_id = P_tid[i];
        dptr[i]->t_num = i;
        dptr[i]->t_runs = 0;

        tret = pthread_create(&P_tid[i],&fifo_attr,psender_thread_func,(void *)dptr[i]);
        pthread_setaffinity_np(P_tid[i], sizeof(cpu_set_t), &cpuset);
        if(tret)
        {
            printf("ERROR. Return code from pthread_create() is %d\n", tret);
            exit(-1);
        }
    }


    //Creating Aperiodic Sender threads
    //----------------------------------
    param.sched_priority = A_SENDER_PRIO;
    pthread_attr_setschedparam(&fifo_attr, &param);

    struct t_data *adptr[A_SENDER_THREAD];

    for(int i=0; i<A_SENDER_THREAD; i++)
    {
        adptr[i] = (struct t_data *)malloc(sizeof(struct t_data));
        adptr[i]->t_id = A_tid[i];
        adptr[i]->t_num = i;
        adptr[i]->t_runs = 0;

        tret = pthread_create(&P_tid[i],&fifo_attr,asender_thread_func,(void *)adptr[i]);
        pthread_setaffinity_np(P_tid[i], sizeof(cpu_set_t), &cpuset);
        if(tret)
        {
            printf("ERROR. Return code from pthread_create() is %d\n", tret);
            exit(-1);
        }
    }


    //=========================================
    // Mouse read thread creation
    //=========================================
    pthread_t mouse_det;            // thread id of mouse click detection thread
    pthread_attr_t mouse_attr;  

    cret = pthread_cond_init(&left_mouse,NULL);
    if(cret!=0)
        printf("Left condn init error %d\n",cret);

    cret = pthread_cond_init(&right_mouse,NULL);
    if(cret!=0)
        printf("Right condn init error %d\n",cret);

    pthread_mutex_init(&right_mouse_mut,NULL);
    pthread_mutex_init(&left_mouse_mut,NULL);


    pthread_attr_init(&mouse_attr);
    // pthread_attr_setinheritsched(&mouse_attr,PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&mouse_attr, SCHED_FIFO);               // setting scheduling priority
    param.sched_priority = MOUSE_PRIO;                                  // Setting highest priority for mouse detection thread
    pthread_attr_setschedparam(&mouse_attr,&param); 

    tret=pthread_create(&mouse_det,&mouse_attr,mouse_read,NULL);
    if(tret)
    {
        printf("Error..Retruned with code %d\n", tret );
        exit(-1);
    }
    pthread_setaffinity_np(mouse_det,sizeof(cpu_set_t),&cpuset);


    // Conditional variable & setting main runtime
    //=============================================
    usleep(1000);                                      // allowing all threads to be created and waitinng on condition variable before broadcasting
    pthread_cond_broadcast(&start);                    // all threads start running


    struct timespec mainstop;                          // timespec variable for calculating time for terminating main program
    clock_gettime(CLOCK_MONOTONIC,&mainstop);          // gets current time

    mainstop.tv_sec += main_runtime/1000;                 // adds time to sleep
    mainstop.tv_nsec += main_runtime*1000000ul;
    if(mainstop.tv_nsec > 1000000000ul)
    {
        mainstop.tv_nsec = 0;
        mainstop.tv_sec++;
    }

    clock_nanosleep(CLOCK_MONOTONIC,TIMER_ABSTIME,&mainstop,0);  // sleeps for total program period

    //=========================================
    // Threads termination
    //=========================================
    if(stp_flag){
        stp_flag = 0;
    }
    usleep(1000000);

    // Release waiting aperiodic threads
    pthread_cond_broadcast(&left_mouse);
    usleep(1000000);
    pthread_cond_broadcast(&right_mouse);
    usleep(1000000);

    pthread_cond_destroy(&start);
    usleep(1000000);
    pthread_cond_destroy(&left_mouse);
    usleep(1000000);
    pthread_cond_destroy(&right_mouse);
    usleep(1000000);

    for(int i=0; i<P_SENDER_THREAD; i++){
        pthread_join(P_tid[i],NULL);
        free(dptr[i]);
    }
        
    for(int i=0; i<A_SENDER_THREAD; i++){
        pthread_join(A_tid[i],NULL);
        usleep(2000000);
        free(adptr[i]);
    }
        

    printf("Terminated successfully.\n");

    return 0;
}

//######################################################
//
// End of Main
//
//######################################################