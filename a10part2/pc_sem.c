#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "uthread.h"
#include "uthread_sem.h"

#define MAX_ITEMS      10
#define NUM_ITERATIONS 200
#define NUM_PRODUCERS  2
#define NUM_CONSUMERS  2
#define NUM_PROCESSORS 4

// histogram [i] == # of times list stored i items
int histogram [MAX_ITEMS+1]; 

// number of items currently produced but not yet consumed
// invariant that you must maintain: 0 >= items >= MAX_ITEMS
int items = 0;

int producer_wait_count;
int consumer_wait_count;

struct ProducerSem{
  uthread_sem_t lock;
  uthread_sem_t notEmpty;
  uthread_sem_t notFull;
  int items;
};

struct ProducerSem* createProducerSem(){
  struct ProducerSem *producerSem = malloc(sizeof(struct ProducerSem));
  producerSem->lock = uthread_sem_create(1);
  producerSem->notEmpty = uthread_sem_create(0);
  producerSem->notFull = uthread_sem_create(MAX_ITEMS);
  producerSem->items = 0;
  return producerSem;
}
// if necessary wait until items < MAX_ITEMS and then increment items
// assertion checks the invariant that 0 >= items >= MAX_ITEMS
void* producer (void* v) {
  struct ProducerSem* p = v;
  for (int i=0; i<NUM_ITERATIONS; i++) {
    producer_wait_count++;
    
    uthread_sem_wait(p->notFull);
    uthread_sem_wait(p->lock);
    p->items++;
    histogram[p->items] += 1;
    assert(p->items > 0 &&p->items <= MAX_ITEMS);
    uthread_sem_signal(p->notEmpty);
    uthread_sem_signal(p->lock);
  }
  return NULL;
}

// if necessary wait until items > 0 and then decrement items
// assertion checks the invariant that 0 >= items >= MAX_ITEMS
void* consumer (void* v) {
  struct ProducerSem *p = v;
  for (int i=0; i<NUM_ITERATIONS; i++) {
    consumer_wait_count++;

    uthread_sem_wait(p->notEmpty);
    uthread_sem_wait(p->lock);
    assert(p->items > 0 && items < MAX_ITEMS);
    p->items--;
    histogram[p->items] += 1;
    uthread_sem_signal(p->notFull);
    uthread_sem_signal(p->lock);
  }
  return NULL;
}

int main (int argc, char** argv) {

  // init the thread system
  uthread_init (NUM_PROCESSORS);

  // start the threads
  uthread_t threads [NUM_PRODUCERS + NUM_CONSUMERS];
  struct ProducerSem *p = createProducerSem();

  for (int i = 0; i < NUM_PRODUCERS; i++)
    threads [i] = uthread_create (&producer, p);
  for (int i = NUM_PRODUCERS; i < NUM_PRODUCERS + NUM_CONSUMERS; i++)  
    threads [i] = uthread_create (&consumer, p);
  // wait for threads to complete
  for (int i=0; i < NUM_CONSUMERS + NUM_PRODUCERS; i++){
    void *res;
    uthread_join(threads[i], &res);
  }



  // sum up
  printf ("producer_wait_count=%d, consumer_wait_count=%d\n", producer_wait_count, consumer_wait_count);

  printf ("items value histogram:\n");
  int sum=0;
  for (int i = 0; i <= MAX_ITEMS; i++) {
    printf ("  items=%d, %d times\n", i, histogram [i]);
    sum += histogram [i];
  }
  // checks invariant that ever change to items was recorded in histogram exactly one
  assert (sum == (NUM_PRODUCERS + NUM_CONSUMERS) * NUM_ITERATIONS);
}
