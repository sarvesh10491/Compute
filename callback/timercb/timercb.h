typedef void (*callback_t)(void);

typedef struct timercb
{
    int sleeptime;
    callback_t cbhandler;
}timercb_t;

void register_callback(timercb_t *timerCtx);