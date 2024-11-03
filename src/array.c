#include <array.h>
#include <core.h>

#ifndef ARRAY_VALIDATE_NUMBER
#define ARRAY_VALIDATE_NUMBER(num)                                             \
  ({                                                                           \
    if (num < 0) {                                                             \
      printf(                                                                  \
          "ARRAY_VALIDATE_NUMBER() went wrong while creating/modifing array"); \
      exit(1);                                                                 \
    }                                                                          \
  })
#endif /* ARRAY_VALIDATE_NUMBER */

array_t *create_array(unsigned long size_of_element) 
{
  ARRAY_VALIDATE_NUMBER(size_of_element);

  /* Initialize array fields with default
   * values */
  array_t *array = (array_t *)calloc(1, sizeof(array_t));

  array->size_of_element = size_of_element;
  array->length = 0;
  array->ptr = (void **)calloc(array->length + 1, sizeof(void *));

  return array;
}

array_t *destroy_array(array_t *array) 
{
  if (array == NULL)
    return NULL;

  free(array->ptr);
  free(array);

  return NULL;
}

void *get_element_from_array(array_t *array, unsigned long index) 
{
  if (array == NULL || index >= array->length || index < 0)
    return NULL;

  return array->ptr[index];
}

int append_element_to_array(array_t *array, void *element) 
{
  if (array == NULL || element == NULL)
    return -1;

  void **new_ptr =
      (void **)realloc(array->ptr, (array->length + 1) * sizeof(void *));
  NO_NULL(new_ptr);

  array->ptr = new_ptr;
  array->ptr[array->length] = element;
  array->length++;

  return 0;
}

int delete_element_from_array(array_t *array, unsigned long index) 
{
  if (array == NULL || index >= array->length)
    return -1;

  for (unsigned long i = index; i < array->length - 1; i++)
    array->ptr[i] = array->ptr[i + 1];

  array->length--;

  void **new_ptr = (void **)realloc(array->ptr, array->length * sizeof(void *));
  NO_NULL(new_ptr);

  if (new_ptr != NULL || array->length == 0)
    array->ptr = new_ptr;

  return 0;
}

int delete_last_element_from_array(array_t *array) 
{
  if (array == NULL || array->length == 0 || array->ptr == NULL)
    return -1;

  unsigned long new_length = array->length - 1;
  void **new_ptr = realloc(array->ptr, new_length * sizeof(void *));
  NO_NULL(new_ptr);

  if (array->size_of_element > 0) {
    void *last_element = array->ptr[array->length - 1];
    free(last_element);
  }

  array->ptr = new_ptr;
  array->length = new_length;

  return 0;
}

int resize_array(array_t *array, unsigned long n) 
{
  if (array == NULL)
    return -1;

  if (n == array->length)
    return 0;

  void **new_ptr = (void **)realloc(array->ptr, n * sizeof(void *));
  NO_NULL(new_ptr);
  array->ptr = new_ptr;

  if (n < array->length) {
    for (unsigned long i = n; i < array->length; i++)
      if (array->size_of_element > 0)
        free(array->ptr[i]);
  } else {
    for (unsigned long i = array->length; i < n; i++)
      array->ptr[i] = NULL;
  }

  array->length = n;
  return 0;
}

int insert_element_in_array(array_t *array, unsigned long index,
                            void *element) 
{                            
  if (array == NULL || element == NULL || index > array->length)
    return -1;

  void **new_ptr =
      (void **)realloc(array->ptr, (array->length + 1) * sizeof(void *));
  NO_NULL(new_ptr);

  array->ptr = new_ptr;

  for (unsigned long i = array->length; i > index; i--)
    array->ptr[i] = array->ptr[i - 1];

  array->ptr[index] = element;
  array->length++;

  return 0;
}