#ifndef CORE_H
#define CORE_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include <stdint.h>
#include <stdbool.h>

#define NO_NULL(x)                                                             \
  ({                                                                           \
    if (x == NULL) {                                                           \
      printf("critical error: " #x " is null.");                               \
      exit(1);                                                                 \
    }                                                                          \
  })

#endif /* CORE_H */