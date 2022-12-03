#include <stdlib.h>
#include <stdio.h>

#include "../hash.h"
#include "../linked_list/linked_list.h"
#include "set.h"

struct set_table *set_table_new(const size_t hashmap_size)
{
    struct set_table *table = malloc(sizeof(struct set_table));
    if (!table)
    {
        return NULL;
    }

    table->hashmap_size = hashmap_size;
    table->nodes = calloc(table->hashmap_size, sizeof(struct set_node *));
    if (!table->nodes)
    {
        free(table);
        return NULL;
    }
    return table;
}

struct set_node *set_table_insert(struct set_table *table, const char *key, const size_t key_len)
{
    // Checks for duplicates
    if (set_table_search(table, key, key_len))
    {
        return NULL;
    }

    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;
    struct set_node *new_item = malloc(sizeof(struct set_node));
    if (!new_item)
    {
        return NULL;
    }

    new_item->key = key;
    new_item->key_len = key_len;
    return (struct set_node *)list_append(PPCAST(&table->nodes[index]), PCAST(new_item));
}

struct set_node *set_table_search(struct set_table *table, const char *key, const size_t key_len)
{
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;

    struct set_node *current = table->nodes[index];
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

struct set_node *set_table_remove(struct set_table *table, const char *key, const size_t key_len)
{
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;

    struct set_node *current = table->nodes[index];
    if (!current)
    {
        return NULL;
    }

    return (struct set_node *)list_remove(PPCAST(&table->nodes[index]), PCAST(current));
}
