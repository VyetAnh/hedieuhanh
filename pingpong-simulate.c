#include <stdio.h>
#include "threads/thread.h"
#include "threads/synch.h"
#include "devices/timer.h"

// Prototype các hàm
void ping_thread(void *aux UNUSED);
void pong_thread(void *aux UNUSED);
void test_pingpong_simulate(void); 

static struct semaphore sema_ping;
static struct semaphore sema_pong;

void ping_thread(void *aux UNUSED) {
    for (int i = 0; i < 5; i++) {
        sema_down(&sema_ping);  // Đợi semaphore_ping
        printf("ping ");
        timer_msleep(1000);  // Giả lập thời gian trôi qua
        sema_up(&sema_pong);  // Up semaphore_pong để bật "pong"
    }
}

void pong_thread(void *aux UNUSED) {
    for (int i = 0; i < 5; i++) {
        sema_down(&sema_pong);  // Đợi semaphore_pong
        printf("pong ");
        timer_msleep(1000);  // Giả lập thời gian trôi qua
        sema_up(&sema_ping);  // Up semaphore_ping để bật "ping"
    }
}

void test_pingpong_simulate(void) {
    printf ("Test: Ping-Pong synchronization\n");
    // Khởi tạo semaphore, sema_ping bắt đầu với giá trị 1, sema_pong với 0
    sema_init(&sema_ping, 1);
    sema_init(&sema_pong, 0);

    // Tạo các thread "ping" và "pong"
    thread_create("ping", PRI_DEFAULT, ping_thread, NULL);  // Tạo thread "ping"
    thread_create("pong", PRI_DEFAULT, pong_thread, NULL);  // Tạo thread "pong"
}

