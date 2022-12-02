#include <stdio.h>

#include "set.h"

void set_table_display(struct set_table *table)
{
    struct set_node **set_nodes = table->nodes;
    for (int i = 0; i < table->hashmap_size; i++)
    {
        struct set_node *head = set_nodes[i];
        while (head)
        {
            printf("[%d: %s]\n", i, head->key);
            head = head->next;
        }
    }
}

int main()
{
    struct set_table *table = set_table_new(20);
    set_table_insert(table, "hurt", 4);
    set_table_insert(table, "myxomatosis", 11);
    set_table_insert(table, "lateralus", 9);
    set_table_insert(table, "tupelo", 6);
    set_table_display(table);

    struct set_node *searched = NULL;
    searched = set_table_search(table, "lateralus", 9);
    printf("search: %s\n", searched ? searched->key : "not found");
    searched = set_table_search(table, "myxomatosis", 11);
    printf("search: %s\n", searched ? searched->key : "not found");
    searched = set_table_search(table, "big_mouth_strikes_again", 23);
    printf("search: %s\n", searched ? searched->key : "not found");
    searched = set_table_search(table, "opus", 4);
    printf("search: %s\n", searched ? searched->key : "not found");

    // set_table_remove(table, "hurt", 4);
    set_table_remove(table, "tupelo", 6);
    set_table_display(table);

    return 0;
}