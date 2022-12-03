#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../set/set.h"
#include "dictionary.h"

#define PPCAST(x) (struct dictionary_node **)(x)
#define PCAST(x) (struct dictionart_node *)(x)

struct dictionary *dictionary_new(const size_t hashmap_size)
{
    struct dictionary *dict = malloc(sizeof(struct dictionary));
    if (!dict)
    {
        return NULL;
    }

    dict->hashmap_size = hashmap_size;
    dict->nodes = calloc(dict->hashmap_size, sizeof(struct dictionary_node *));
    if (!dict->nodes)
    {
        free(dict);
        return NULL;
    }

    dict->collisions_count = 0;

    return dict;
}

struct dictionary_node *dictionary_insert(struct dictionary *dict, const char *key, const size_t key_len, void *data)
{
    // Checks for duplicates
    if (dictionary_search(dict, key, key_len))
    {
        return NULL;
    }

    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % dict->hashmap_size;

    struct dictionary_node *new_item = malloc(sizeof(struct dictionary_node));
    if (!new_item)
    {
        return NULL;
    }

    new_item->key = key;
    new_item->key_len = key_len;
    new_item->data = data;
    return (struct dictionary_node *)list_append(PPCAST(&dict->nodes[index]), PCAST(new_item));
}

struct dictionary_node *dictionary_remove(struct dictionary *dict, const char *key, const size_t key_len)
{
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % dict->hashmap_size;

    struct set_node *current = dict->nodes[index];
    if (!current)
    {
        return NULL;
    }

    return (struct set_node *)list_remove(PPCAST(&dict->nodes[index]), PCAST(current));
}

struct dictionary_node *dictionary_search(struct dictionary *dict, const char *key, const size_t key_len)
{
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % dict->hashmap_size;

    struct dictionary_node *current = dict->nodes[index];
    if (!current)
    {
        return NULL;
    }

    while (current->key != key && current->next)
    {
        current = current->next;
    }

    return current;
}
