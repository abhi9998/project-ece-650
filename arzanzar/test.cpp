#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <set>
#include <queue>
#include <algorithm>
// defined std::unique_ptr
#include <memory>
// // defines Var and Lit
// #include "minisat/core/SolverTypes.h"
// // defines Solver
//#include "minisat/core/Solver.h"
#include <pthread.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sstream>
#include <stdio.h>

#define SIZE 3

typedef struct vector_t {
  pthread_mutex_t lock;
  int values[SIZE];
} vector_t;

vector_t v1, v2, v3;

void initialize_vectors() {
  int i = 0;
  for (i = 0; i < SIZE; i++) {
    v1.values[i] = i;
    v2.values[i] = 2*i;
    v3.values[i] = 3*i;
  }
  pthread_mutex_init(&v1.lock, NULL);
  pthread_mutex_init(&v2.lock, NULL);
  pthread_mutex_init(&v3.lock, NULL);
}

void vector_add(vector_t *v_dst, vector_t *v_src) {
  pthread_mutex_lock(&v_dst->lock);
  pthread_mutex_lock(&v_src->lock);
  for (int i = 0; i < SIZE; i++) {
    v_dst->values[i] = v_dst->values[i] + v_src->values[i];
  }
  pthread_mutex_unlock(&v_dst->lock);
  pthread_mutex_unlock(&v_src->lock);
}

void *worker(void *arg) {
  vector_t **args = (vector_t **) arg;
  vector_t *v0 = args[0];
  vector_t *v1 = args[1];
  vector_add(v0, v1);
  return NULL;
}

int main(int argc, char *argv[]) {
  vector_t *args1[2], *args2[2], *args3[2];
  pthread_t pid1, pid2, pid3;

  initialize_vectors();

  args1[0] = &v1;
  args1[1] = &v2;

  args2[0] = &v2;
  args2[1] = &v3;

  args3[0] = &v3;
  args3[1] = &v1;

  pthread_create(&pid1, NULL, worker, (void *) &args1);
  pthread_create(&pid2, NULL, worker, (void *) &args2);
  pthread_create(&pid3, NULL, worker, (void *) &args3);

  pthread_join(pid1, NULL);
  pthread_join(pid2, NULL);
  pthread_join(pid3, NULL);

  for (unsigned i = 0; i < SIZE; i++) {
    std::cout << v1.values[i] << "\n";
  }

}