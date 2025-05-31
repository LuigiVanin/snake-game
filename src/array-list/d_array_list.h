#ifndef D_ARRAY_LIST_H
#define D_ARRAY_LIST_H

#include <stddef.h>

#define _newArrayListOverload1(T, capacity) NewArrayList_(sizeof(T), capacity)

#define _newArrayListOverload2(T) NewArrayList_(sizeof(T), 8)

#define _GET_NEW_ARRAY_MACRO(_1, _2, NAME, ...) NAME

/**
 * @brief Macro to create a new ArrayList template with optional default
 * capacity.
 *
 * This macro supports two overloads:
 * - NewArrayListTemplate(Type): Creates a new ArrayList for the specified Type
 * with a default capacity of 8.
 * - NewArrayListTemplate(Type, Capacity): Creates a new ArrayList for the
 * specified Type with the given initial Capacity.
 *
 * @param Type The type of elements to be stored in the ArrayList.
 * @param Capacity (Optional) The initial capacity of the ArrayList. If not
 * provided, defaults to 8.
 */
#define NewArrayList(...)                                                      \
  _GET_NEW_ARRAY_MACRO(                                                        \
    __VA_ARGS__, _newArrayListOverload1, _newArrayListOverload2)               \
  (__VA_ARGS__)

/**
 * @brief Pushes an item onto a generic array list.
 *
 * This macro appends a new item to the end of the specified array list,
 * automatically resizing the underlying storage if necessary.
 *
 * @param THIS Pointer to the array list.
 * @param VALUE The item to be added to the list.
 *
 * @note The list must have been initialized using NewArrayListT.
 */
#define PushItem(THIS, VALUE)                                                  \
  do {                                                                         \
    typeof(VALUE) __temp_value = (VALUE);                                      \
    PushItem_(THIS, &__temp_value);                                            \
  } while (0)

/**
 * @brief Inserts an item at the specified index in a generic array list.
 *
 * This macro inserts a new item into the given array list at the specified
 * index, shifting subsequent elements to the right. The underlying storage is
 * automatically resized if necessary.
 *
 * @param THIS Pointer to the array list.
 * @param INDEX The position at which to insert the new item.
 * @param VALUE The item to be inserted into the list.
 *
 * @note The list must have been initialized using NewArrayList.
 * @note If INDEX is greater than the current length, the behavior is undefined.
 */
#define InsertAt(THIS, INDEX, VALUE)                                           \
  do {                                                                         \
    typeof(VALUE) __temp_value_index = (VALUE);                                \
    InsertItemAt_(THIS, INDEX, &__temp_value_index);                           \
  } while (0)

/**
 * @brief Creates a new ArrayList instance.
 *
 * This macro initializes a new ArrayList with the specified element type.
 * It allocates memory for the list structure and sets up the initial capacity.
 *
 * @param type The data type of elements to be stored in the ArrayList.
 * @return A pointer to the newly created ArrayList.
 *
 * @note The returned ArrayList must be freed using the appropriate destroy
 * function to avoid memory leaks.
 */
#define GetAt(T, THIS, INDEX) (*(T *)GetAt_(THIS, INDEX));

/**
 * @brief Removes and returns the last item from the specified list.
 *
 * This macro calls the internal function PopItem_ to perform the
 * operation.
 *
 * @param THIS The list from which to pop the last item.
 */
#define PopItem(THIS) PopItem_(THIS)

/**
 * @brief Removes the specific item from the specified list.
 *
 * This macro calls the internal function RemoveItemAt_ to perform the
 * operation.
 *
 * @param THIS The list from which to pop the last item.
 * @param INDEX Index of the desire item to be removed.
 */
#define RemoveAt(THIS, INDEX) RemoveItemAt_(THIS, INDEX)

#define GetArray(T, THIS) ((T *)GetArray_(THIS));

typedef struct {
  size_t capacity;
  size_t length;
  void  *data;
  size_t element_size;
} ArrayList;

ArrayList NewArrayList_(size_t element_size, size_t capacity);

void PushItem_(ArrayList *this, const void *value);

void InsertItemAt_(ArrayList *this, size_t index, const void *value);

void _ResizeList(ArrayList *this);

void *GetAt_(ArrayList this, size_t index);

void PopItem_(ArrayList *this);

void RemoveItemAt_(ArrayList *this, size_t index);

void *GetArray_(ArrayList *this);

void DeleteList(ArrayList *this);
#endif