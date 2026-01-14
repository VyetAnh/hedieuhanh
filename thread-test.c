#include <stdio.h>

#include "threads/thread.h"
#include "threads/synch.h"
#include "devices/timer.h"
/*void thread_func1(void *aux UNUSED);
void thread_func2(void *aux UNUSED);*/
void test_thread_test(void);


static struct semaphore sema;

static void thread_func1(void *aux UNUSED) {
  printf("Thread 1: Waiting on semaphore...\n");
  sema_down(&sema);
  printf("Thread 1: Acquired semaphore!\n");
}

static void thread_func2(void *aux UNUSED) {
  printf("Thread 2.1: Sleeping before up semaphore...\n");
  timer_msleep(10000);
  printf("Thread 2.2: Waking and Up semaphore\n");
  sema_up(&sema);
}

void test_thread_test(void) {
  printf("Test case 1:\n");
  printf("Ho ten: Vu Viet Anh\n");
  printf("MSSV: 20223865\n");
  printf("Ho ten: Dinh Quang Lam\n");
  printf("MSSV: 20223712\n");
  printf("Ho ten: Truong Duc Khiem\n");
  printf("MSSV: 2022021\n");
  printf("Ho ten: Cao Van Quan\n");
  printf("MSSV: 20214057\n");
  printf("\n");
  sema_init(&sema, 0);
  
  printf("Test case 2:\n");
  thread_create("thread1", PRI_DEFAULT, thread_func1, NULL);
  thread_create("thread2", PRI_DEFAULT, thread_func2, NULL);
}

