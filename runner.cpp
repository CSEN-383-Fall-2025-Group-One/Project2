#include <stdlib.h>

int main(){
  int seed = time(NULL);
  srand(seed);

  int arrival_time = rand() % 100;
  int service_time = (rand() % 10) + 1;
  int priority = (rand() % 4) + 1;
}
