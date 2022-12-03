#ifndef DICTIONARY_H
#define DICTIONARY_H

struct dictionary_node
{
    struct dictionary_node *next;
    const char *key;
    size_t key_len;
    void *data;
};

struct dictionary
{
    struct dictionary_node **nodes;
    size_t hashmap_size;
    size_t collision_count;
};

struct dictionary *dictionary_new(const size_t hashmap_size);
struct dictionary_node *dictionary_insert(struct dictionary *dict, const char *key, const size_t key_len, void *data);
struct dictionary_node *dictionary_remove(struct dictionary *dict, const char *key, const size_t key_len);
struct dictionary_node *dictionary_search(struct dictionary *dict, const char *key, const size_t key_len);

#endif
