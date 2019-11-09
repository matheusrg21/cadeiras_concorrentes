#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdbool.h>

#define NUM_PEOPLE        20
#define NUM_GOOD_CHAIR     5
#define NUM_REGULAR_CHAIR  3
#define NUM_BAD_CHAIR      9

void* person(void *param) {
  sleep(5);
  printf("Hello World\n");
}

int main() {
  pthread_t people[NUM_PEOPLE];

  for (int i = 0; i < NUM_PEOPLE; i++) {
    pthread_create(&people[i], NULL, person, NULL);
  }

  for (int i = 0; i < NUM_PEOPLE; i++) {
    pthread_join(people[i], NULL);
  }

  return 0;
}
