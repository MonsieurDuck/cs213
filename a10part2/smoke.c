#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include "uthread.h"
#include "uthread_mutex_cond.h"

#define NUM_ITERATIONS 1000

#ifdef VERBOSE
#define VERBOSE_PRINT(S, ...) printf (S, ##__VA_ARGS__);
#else
#define VERBOSE_PRINT(S, ...) ;
#endif

/**
 * You might find these declarations helpful.
 *   Note that Resource enum had values 1, 2 and 4 so you can combine resources;
 *   e.g., having a MATCH and PAPER is the value MATCH | PAPER == 1 | 2 == 3
 */
enum Resource            {    MATCH = 1, PAPER = 2,   TOBACCO = 4};
char* resource_name [] = {"", "match",   "paper", "", "tobacco"};

int signal_count [5];  // # of times resource signalled
int smoke_count  [5];  // # of times smoker with resource smoked

struct Agent {
  uthread_mutex_t mutex;
  uthread_cond_t  match;
  uthread_cond_t  paper;
  uthread_cond_t  tobacco;
  uthread_cond_t  smoke;
//    uthread_cond_t  tocan;
//    uthread_cond_t   pacan;
//    uthread_cond_t  macan;
};

struct Agent* createAgent() {
  struct Agent* agent = malloc (sizeof (struct Agent));
  agent->mutex   = uthread_mutex_create();
  agent->paper   = uthread_cond_create (agent->mutex);
  agent->match   = uthread_cond_create (agent->mutex);
  agent->tobacco = uthread_cond_create (agent->mutex);
  agent->smoke   = uthread_cond_create (agent->mutex);
//    agent->tocan =uthread_cond_create (agent->mutex);
//    agent->pacan=uthread_cond_create (agent->mutex);
//    agent->macan=uthread_cond_create (agent->mutex);
//

  return agent;
}

struct SmokerPool {
  struct Agent* agent;
  int match;
  int tobacco;
  int paper;
    uthread_cond_t  tocan;
    uthread_cond_t   pacan;
    uthread_cond_t  macan;
};

struct Smoker {
  struct SmokerPool* pool;
  int type;
};

//
// TODO
// You will probably need to add some procedures and struct etc.

struct SmokerPool* createSmokerPool(struct Agent* agent) {
  struct SmokerPool* smoker = malloc (sizeof (struct SmokerPool));
  smoker->agent = agent;
  smoker->match = 0;
  smoker->tobacco = 0;
  smoker->paper = 0;
    smoker->tocan =uthread_cond_create (smoker->agent->mutex);
    smoker->pacan=uthread_cond_create (smoker->agent->mutex);
    smoker->macan=uthread_cond_create (smoker->agent->mutex);
    
  return smoker;
}

struct Smoker* createSmoker(struct SmokerPool* pool, int type) {
  struct Smoker* smoker = malloc (sizeof (struct Smoker));
  smoker->pool = pool;
  smoker->type = type;
  return smoker;
}


void* smoker (void* av) {
  struct Smoker* s = av;
  struct SmokerPool* p = s->pool;
  struct Agent* a = p->agent;
  uthread_mutex_lock(a->mutex);
 while (1){
   switch(s->type){
    case MATCH:
       uthread_cond_wait(p->macan);
       if (p->paper > 0 && p->tobacco > 0){
         p->tobacco--;
         p->paper--;
         smoke_count[s->type]++;
         uthread_cond_signal(a->smoke);
       }
//       else
//         p->match++;
       break;

     case PAPER:
       uthread_cond_wait(p->pacan);
       if (p->match > 0 && p->tobacco > 0){
         p->match--;
         p->tobacco--;
         smoke_count[s->type]++;
         uthread_cond_signal(a->smoke);
       }
//       else
//         p->paper++;
       break;

     case TOBACCO:
       uthread_cond_wait(p->tocan);
       if (p->paper > 0 && p->match > 0){
         p->match--;
         p->paper--;
         smoke_count[s->type]++;
         uthread_cond_signal(a->smoke);
       }
//       else
//         p->tobacco++;
       break;

     default:
       break; 
   }
//   if (p->paper > 0 && p->tobacco > 0){
//     uthread_cond_signal(a->match);
//   }
//   else if (p->paper > 0 && p->match > 0){
//     uthread_cond_signal(a->tobacco);
//   }
//   else if (p->tobacco > 0 && p->match > 0){
//     uthread_cond_signal(a->paper);
//   }

 }
 uthread_mutex_unlock(a->mutex);
}


void* getto(void* av){
    struct SmokerPool* p =av;
    struct Agent* a = p->agent;
     uthread_mutex_lock(a->mutex);
    while(1){
//    VERBOSE_PRINT("waiting for tobacco\n");
    uthread_cond_wait(a->tobacco);
//    VERBOSE_PRINT("got tobacco\n");
    p->tobacco++;
    if(p->paper){
        uthread_cond_signal(p->macan);
        
    }
    else if(p->match){
        uthread_cond_signal(p->pacan);
    }
    }
    uthread_mutex_unlock (a->mutex);
    return NULL;
}

void* getma(void* av){
    struct SmokerPool* p =av;
    struct Agent* a = p->agent;
     uthread_mutex_lock(a->mutex);
    while(1){
//    VERBOSE_PRINT("waiting for match\n");
    uthread_cond_wait(a->match);
//    VERBOSE_PRINT("got match\n");
    p->match++;
    if(p->tobacco){
        uthread_cond_signal(p->pacan);
    }
    else if(p->paper){
        uthread_cond_signal(p->tocan);
    }
    }
    uthread_mutex_unlock (a->mutex);
    return NULL;
}

void* getpa(void* av){
    struct SmokerPool* p =av;
    struct Agent* a = p->agent;
     uthread_mutex_lock(a->mutex);
    while(1){
//     VERBOSE_PRINT("waiting for paper\n");
    uthread_cond_wait(a->paper);
//     VERBOSE_PRINT("got paper\n");
    p->paper++;
    if(p->tobacco){
        uthread_cond_signal(p->macan);
    }
    else if(p->match){
        uthread_cond_signal(p->tocan);
    }
    }
    uthread_mutex_unlock (a->mutex);
    return NULL;
}
/**
 * This is the agent procedure.  It is complete and you shouldn't change it in
 * any material way.  You can re-write it if you like, but be sure that all it does
 * is choose 2 random reasources, signal their condition variables, and then wait
 * wait for a smoker to smoke.
 */
void* agent (void* av) {
    struct SmokerPool* p =av;
  struct Agent* a = p->agent;
    
  static const int choices[]         = {MATCH|PAPER, MATCH|TOBACCO, PAPER|TOBACCO};
  static const int matching_smoker[] = {TOBACCO,     PAPER,         MATCH};

  uthread_mutex_lock (a->mutex);
    for (int i = 0; i < NUM_ITERATIONS; i++) {
      int r = random() % 3;
      signal_count [matching_smoker [r]] ++;
      int c = choices [r];
      if (c & MATCH) {
        VERBOSE_PRINT ("match available\n");
        uthread_cond_signal (a->match);
        
         
      }
      if (c & PAPER) {
        VERBOSE_PRINT ("paper available\n");
        uthread_cond_signal (a->paper);
//          p->paper++;
      }
      if (c & TOBACCO) {
        VERBOSE_PRINT ("tobacco available\n");
        uthread_cond_signal (a->tobacco);
//          p->tobacco++;
      }
//     if((c & MATCH)&&(c & PAPER))
//     {
//         uthread_cond_signal (a->tocan);
//     }
//        if((c & MATCH)&&(c & TOBACCO)){
//           uthread_cond_signal (a->pacan);
//        }
//        if((c & PAPER)&&(c & TOBACCO)){
//             uthread_cond_signal (a->macan);
//        }
      VERBOSE_PRINT ("agent is waiting for smoker to smoke\n");
      uthread_cond_wait (a->smoke);
    }
  uthread_mutex_unlock (a->mutex);
  return NULL;
}

int main (int argc, char** argv) {
  uthread_init (7);
  struct Agent*  a = createAgent();
  struct SmokerPool* p = createSmokerPool(a);

  uthread_t gmatch = uthread_create(getma, p);
  uthread_t gpaper = uthread_create(getpa, p);
  uthread_t gtobacco = uthread_create(getto, p);
  
  uthread_t masmoker = uthread_create(smoker, createSmoker(p, MATCH));
    uthread_t pasmoker = uthread_create(smoker, createSmoker(p, PAPER));
    uthread_t tosmoker = uthread_create(smoker, createSmoker(p, TOBACCO));
    

  uthread_join (uthread_create (agent, p), 0);
  assert (signal_count [MATCH]   == smoke_count [MATCH]);
  assert (signal_count [PAPER]   == smoke_count [PAPER]);
  assert (signal_count [TOBACCO] == smoke_count [TOBACCO]);
  assert (smoke_count [MATCH] + smoke_count [PAPER] + smoke_count [TOBACCO] == NUM_ITERATIONS);
  printf ("Smoke counts: %d matches, %d paper, %d tobacco\n",
          smoke_count [MATCH], smoke_count [PAPER], smoke_count [TOBACCO]);
    printf ("Signal counts: %d matches, %d paper, %d tobacco\n",
          signal_count [MATCH], signal_count [PAPER], signal_count [TOBACCO]);
}
