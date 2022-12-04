#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#define PPCAST(x) (struct dlist_node **)(x)
#define PCAST(x) (struct dlist_node *)(x)

struct dlist_node
{
    struct dlist_node *prev;
    struct dlist_node *next;
};

struct dlist_node *dlist_get_tail(struct dlist_node **head);

struct dlist_node *dlist_get_node(struct dlist_node **head, const unsigned int index);

struct dlist_node *dlist_append(struct dlist_node **head, struct dlist_node *item);

struct dlist_node *dlist_pop(struct dlist_node **head);

struct dlist_node *dlist_remove(struct dlist_node **head, struct dlist_node *item);

void dlist_insert_after(struct dlist_node *item, struct dlist_node *after);

void dlist_insert_before(struct dlist_node **head, struct dlist_node *item, struct dlist_node *before);

size_t dlist_size(struct dlist_node **head);

void dlist_shuffle(struct dlist_node **head);

#endif