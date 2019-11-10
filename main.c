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

// Good Chairs -----------------------------------------------------------------
pthread_mutex_t good_chairs_mutex = PTHREAD_MUTEX_INITIALIZER;
int good_chairs = 0;

bool try_get_good_chair() {
  bool result = false;
  pthread_mutex_lock(&good_chairs_mutex);

  if (good_chairs < NUM_GOOD_CHAIR) {
    good_chairs++;
    result = true;
  }

  pthread_mutex_unlock(&good_chairs_mutex);
  return result;
}

// Regular Chairs --------------------------------------------------------------
pthread_mutex_t regular_chairs_mutex = PTHREAD_MUTEX_INITIALIZER;
int regular_chairs = 0;

bool try_get_regular_chair() {
  bool result = false;
  pthread_mutex_lock(&regular_chairs_mutex);

  if (regular_chairs < NUM_REGULAR_CHAIR) {
    regular_chairs++;
    result = true;
  }

  pthread_mutex_unlock(&regular_chairs_mutex);
  return result;
}

// Bad Chairs ------------------------------------------------------------------
pthread_mutex_t bad_chairs_mutex = PTHREAD_MUTEX_INITIALIZER;
int bad_chairs = 0;

bool try_get_bad_chair() {
  bool result = false;
  pthread_mutex_lock(&bad_chairs_mutex);

  if (bad_chairs < NUM_BAD_CHAIR) {
    bad_chairs++;
    result = true;
  }

  pthread_mutex_unlock(&bad_chairs_mutex);
  return result;
}

// People ----------------------------------------------------------------------
void on_good_chair(size_t thread_id) {
  printf("%02d Found a good chair!!\n", thread_id);
}

void on_regular_chair(size_t thread_id) {
  printf("%02d Found a regular chair!\n", thread_id);
}

void on_bad_chair(size_t thread_id) {
  printf("%02d Found a bad chair :(\n", thread_id);
}

void without_chair(size_t thread_id) {
  printf("%02d Didn't get a chair\n", thread_id);
}

void* person (void *param) {
  size_t thread_id = (size_t) param;
  // Add a short delay for getting a chair
  sleep(rand() % 5);

  if (try_get_good_chair()) {
    on_good_chair(thread_id);
  } else {
    if (try_get_regular_chair()) {
      on_regular_chair(thread_id);
    } else {
      if (try_get_bad_chair()) {
        on_bad_chair(thread_id);
      } else {
        without_chair(thread_id);
      }
    }
  }
}

int main() {
  pthread_t people[NUM_PEOPLE];

  for (size_t i = 0; i < NUM_PEOPLE; i++) {
    pthread_create(&people[i], NULL, person, (void *)i);
  }

  for (int i = 0; i < NUM_PEOPLE; i++) {
    pthread_join(people[i], NULL);
  }

  return 0;
}
