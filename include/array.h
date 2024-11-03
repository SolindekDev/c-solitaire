#ifndef __ARRAY_H
#define __ARRAY_H

typedef struct __array_t {
  unsigned long size_of_element;
  unsigned long length;

  void **ptr;
} array_t;

#define ARRAY_FOR(arr) for (int i = 0; i < arr->length; i++)
#define ARRAY_IS_LAST_ELEMENT(arr, i) (arr->length == (i + 1))

array_t *create_array(unsigned long size_of_element);
array_t *destroy_array(array_t *array);

void *get_element_from_array(array_t *array, unsigned long index);

int append_element_to_array(array_t *array, void *element);
int delete_element_from_array(array_t *array, unsigned long index);
int insert_element_in_array(array_t *array, unsigned long index,
                                 void *element);
int delete_last_element_from_array(array_t *array);
int resize_array(array_t *array, unsigned long n);

#endif /* __ARRAY_H */