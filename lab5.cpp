#include "DigitalOut.h"
#include "mbed.h"
#include "ThisThread.h"

typedef struct {
    int led;
} message_t;
MemoryPool<message_t, 16> mpool;
Queue<message_t, 16> queue;
Thread thread;
DigitalOut testled(PC_7);
#define PRINT_FLAG 3

void send_thread(void)
{
    uint32_t i = 0;
    while (true) {
        testled = !testled;
        i++; /* так как настоящие данные брать неоткуда здесь они генерируются*/
        message_t *message = mpool.alloc();
        message->led = testled;
        queue.put(message);
        ThisThread::sleep_for(1000);
    }
}
int main()
{
    thread.start(callback(send_thread));
    while (true) {
        osEvent evt = queue.get();
        if (evt.status == osEventMessage) {
            message_t *message = (message_t *)evt.value.p;
            printf("led is: %u\n\r", message->led);
            mpool.free(message);
        }
    }
}
