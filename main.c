#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PESSOAS   20
#define CADEIRA_BOA    5
#define CADEIRA_MEDIA  3
#define CADEIRA_RUIM   9

void* pessoa(void *param) {
  sleep(5);
  printf("Hello World\n");
}

int main() {
  pthread_t threads[NUM_PESSOAS];

  for (int i = 0; i < NUM_PESSOAS; i++) {
    pthread_create(&threads[i], NULL, pessoa, NULL);
  }

  for (int i = 0; i < NUM_PESSOAS; i++) {
    pthread_join(threads[i], NULL);
  }

  return 0;
}
