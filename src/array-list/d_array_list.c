#include "d_array_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ArrayList NewArrayList_(size_t element_size, size_t capacity) {
  if (element_size <= 0) {
    fprintf(stderr, "Error: `element_size` must be greater than 0.");
    element_size = 1; // default association to a char.
  }

  if (capacity <= 0) {
    fprintf(stderr, "Error: `capacity` must be greater than 0.");
    capacity = 8;
  }

  ArrayList arr_list = {
    .capacity     = capacity,
    .element_size = element_size,
    .length       = 0,
    .data         = (void *)malloc(element_size * capacity),
  };

  return arr_list;
}

void PushItem_(ArrayList *this, const void *value) {
  if (this->capacity <= 0) this->capacity = 1;

  if (this->length >= this->capacity) _ResizeList(this);

  /**
   * NOTE: Why use char* instead of void* for address manipulation?
   *       Some compilers dont know how to properly handle void* pointer
   * arithimatic manipulation due to void not being a proper type not having
   * defined size depending on the compiler. To standartize the behaviour, is
   * recommended to cast the void pointer to a char* that has a well defined bit
   * length
   * */
  char *dest = (char *)this->data + (this->length * this->element_size);

  memcpy(dest, value, this->element_size);

  this->length++;
}

void InsertItemAt_(ArrayList *this, size_t index, const void *value) {
  if (index >= this->length) {
    fprintf(stderr, "Error: array list not initialized properly");
    return;
  }

  if (this->length >= this->capacity) _ResizeList(this);

  char *dest = (char *)this->data + (index * this->element_size);

  memmove(dest + this->element_size, //
          dest,                      //
          (this->length - index) * this->element_size);
  // memcpy(list_replace, dest, (this->length - index) * this->element_size);
  memcpy(dest, value, this->element_size);

  this->length++;
}

void _ResizeList(ArrayList *this) {
  if (this->length >= this->capacity) {
    void *target =
      realloc(this->data, this->element_size * (this->capacity * 2));

    if (target != NULL) {
      this->data = target;
      this->capacity *= 2;
    } else
      fprintf(stderr, "Error: realloc failed during resize.\n");
  }
}

void *GetAt_(ArrayList this, size_t index) {
  if (index >= this.length) {
    fprintf(stderr,
            "Error: Index %zu out of bounds for ArrayList with length %d.\n",
            index,
            (int)this.length);
    // Decide on error handling: return NULL, exit, assert, etc.
    return NULL;
  }

  return (char *)this.data + (index * this.element_size);
}

void PopItem_(ArrayList *this) {
  if (this == NULL) {
    fprintf(stderr, "Error: array list not initialized properly");
    return;
  }

  if (this->length <= 0) {
    fprintf(stderr, "Error: array list is empty");
    return;
  }
  this->length--;
}

void RemoveItemAt_(ArrayList *this, size_t index) {
  if (this == NULL) {
    fprintf(stderr, "Error: array list not initialized properly");
    return;
  }

  if (index < 0 || index >= this->length) {
    fprintf(stderr,
            "Error: Index %zu out of bounds for ArrayList with length %d.\n",
            index,
            (int)this->length);
  }

  char *dest = (char *)this->data + (index * this->element_size);

  memmove(                                      //
    dest,                                       //
    dest + this->element_size,                  //
    (this->length - index) * this->element_size //
  );
  this->length--;
}

void *GetArray_(ArrayList *this) {
  return this->data;
}

void DeleteList(ArrayList *this) {
  if (this->data != NULL) {
    free(this->data);
    this->data     = NULL;
    this->length   = 0;
    this->capacity = 8;
  }
}
