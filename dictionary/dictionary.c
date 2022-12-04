#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../set/set.h"
#include "../linked_list/linked_list.h"
#include "dictionary.h"

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

void _dictionary_resize(struct dictionary *dict)
{
    dict->collisions_count = 0;

    struct dictionary_node **tmp = calloc(dict->hashmap_size, sizeof(struct dictionary_node *));
    if (!tmp)
    {
        return;
    }

    memcpy(tmp, dict->nodes, dict->hashmap_size * sizeof(struct dictionary_node *));

    size_t prev_hashmap_size = dict->hashmap_size;
    dict->hashmap_size *= 2;
    dict->nodes = realloc(dict->nodes, dict->hashmap_size * sizeof(struct dictionary_node *));
    memset(dict->nodes, 0, dict->hashmap_size * sizeof(struct dictionary_node *));

    for (int i = 0; i < prev_hashmap_size; i++)
    {
        struct dictionary_node *current = tmp[i];
        struct dictionary_node *next = NULL;
        while (current)
        {
            size_t hash = djb33x_hash(current->key, current->key_len);
            size_t index = hash % dict->hashmap_size;

            next = current->next;

            list_append(PPCAST(&dict->nodes[index]), PCAST(current));

            current = next;
        }
    }

    free(tmp);
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

    // Check collisions
    if (dict->nodes[index])
    {
        dict->collisions_count++;
    }

    // return (struct dictionary_node *)list_append(PPCAST(&dict->nodes[index]), PCAST(new_item));
    list_append(PPCAST(&dict->nodes[index]), PCAST(new_item));

    if (dict->collisions_count > 0)
    {
        _dictionary_resize(dict);
    }

    dictionary_display(dict);

    return NULL;
}

struct dictionary_node *dictionary_remove(struct dictionary *dict, const char *key, const size_t key_len)
{
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % dict->hashmap_size;

    struct dictionary_node *current = dict->nodes[index];
    if (!current)
    {
        return NULL;
    }

    return (struct dictionary_node *)list_remove(PPCAST(&dict->nodes[index]), PCAST(current));
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

    while (current)
    {
        if (current->key == key)
        {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

void dictionary_display(struct dictionary *dict)
{
    struct dictionary_node **set_nodes = dict->nodes;
    printf("hashmap_size: %lld\n", dict->hashmap_size);
    for (int i = 0; i < dict->hashmap_size; i++)
    {
        struct dictionary_node *head = set_nodes[i];
        while (head)
        {
            printf("[%d: %s]\n", i, head->key);
            head = head->next;
        }
    }
    printf("----------\n");
}