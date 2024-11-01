#include <random.h>

#include <core.h>

/* random number from 0 to 1 */
double random_number() 
{
  return (double)rand() / (double)RAND_MAX;
}

void init_random_numbers()
{
  srand(time(NULL));
}