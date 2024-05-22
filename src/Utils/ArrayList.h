#pragma once
#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#define ARRAYLIST_INIT_CAPACITY 4

#define ARRAYLIST_INIT(list) ArrayList list; ArrayList_init(&list)
#define ARRAYLIST_ADD(list, item) ArrayList_add(&list, (void *) item)
#define ARRAYLIST_SET(list, id, item) ArrayList_set(&list, id, (void *) item)
#define ARRAYLIST_GET(list, type, id) (type) ArrayList_get(&list, id)
#define ARRAYLIST_DELETE(list, id) ArrayList_delete(&list, id)
#define ARRAYLIST_TOTAL(list) ArrayList_total(&list)
#define ARRAYLIST_FREE(list) ArrayList_free(&list)

typedef struct ArrayList {
    void **items;
    int capacity;
    int total;
} ArrayList;

void ArrayList_init(ArrayList *list)
{
    list->capacity = ARRAYLIST_INIT_CAPACITY;
    list->total = 0;
    list->items = (void**)malloc(sizeof(void *) * list->capacity);
}

int ArrayList_total(ArrayList *list)
{
    return list->total;
}

static void ArrayList_resize(ArrayList *list, int capacity)
{
    #ifdef DEBUG_ON
    printf("ArrayList_resize: %d to %d\n", list->capacity, capacity);
    #endif

    void **items = (void**)realloc(list->items, sizeof(void *) * capacity);
    if (items) {
        list->items = items;
        list->capacity = capacity;
    }
}

void ArrayList_add(ArrayList *list, void *item)
{
    if (list->capacity == list->total)
        ArrayList_resize(list, list->capacity * 2);
    list->items[list->total++] = item;
}

void ArrayList_set(ArrayList *list, int index, void *item)
{
    if (index >= 0 && index < list->total)
        list->items[index] = item;
}

void *ArrayList_get(ArrayList *list, int index)
{
    if (index >= 0 && index < list->total)
        return list->items[index];
    return NULL;
}

void ArrayList_delete(ArrayList *list, int index)
{
    if (index < 0 || index >= list->total)
        return;

    list->items[index] = NULL;

    for (int i = index; i < list->total - 1; i++) {
        list->items[i] = list->items[i + 1];
        list->items[i + 1] = NULL;
    }

    list->total--;

    if (list->total > 0 && list->total == list->capacity / 4)
        ArrayList_resize(list, list->capacity / 2);
}

void ArrayList_deleteItem(ArrayList *list, void *item)
{
    if (list == NULL || item == NULL)
        return;

    for (int i = 0; i < list->total; i++) {
        if (list->items[i] == item) {
            // Found the item, delete it by shifting elements
            for (int j = i; j < list->total - 1; j++) {
                list->items[j] = list->items[j + 1];
            }
            list->items[list->total - 1] = NULL; // Clear the last element
            list->total--;

            if (list->total > 0 && list->total == list->capacity / 4)
                ArrayList_resize(list, list->capacity / 2);

            break; // Stop searching
        }
    }
}

void ArrayList_free(ArrayList *list)
{
    if(list != NULL && list->items != NULL){
        free(list->items);
    }
}

void ArrayList_reverse(ArrayList *list)
{

    int left = 0;
    int right = list->total - 1;

    while (left < right)
    {
        // Swap items at left and right indices
        void *temp = list->items[left];
        list->items[left] = list->items[right];
        list->items[right] = temp;

        // Move to the next pair of elements
        left++;
        right--;
    }
}

#endif
