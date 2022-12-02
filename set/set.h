#ifndef SET_H
#define SET_H

// forward decl
struct list_node;

struct set_node
{
    struct list_node *next;
    const char *key;
    size_t key_len;
};

struct set_table
{
    struct set_node **nodes;
    size_t hashmap_size;
};

struct set_table *set_table_new(const size_t hashmap_size);
struct set_node *set_table_insert(struct set_table *table, const char *key, const size_t key_len);
struct set_node *set_table_search(struct set_table *table, const char *key, const size_t key_len);
struct set_node *set_table_remove(struct set_table *table, const char *key, const size_t key_len);

#endif
