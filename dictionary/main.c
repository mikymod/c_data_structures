#include <stdio.h>

#include "../set/set.h"
#include "dictionary.h"

void dictionary_display(struct dictionary *dict)
{
    struct dictionary_node **set_nodes = dict->nodes;
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

int main()
{
    struct dictionary *dict = dictionary_new(100);
    dictionary_display(dict);

    dictionary_insert(dict, "tool", 4, "fucking data");
    dictionary_insert(dict, "the_smiths", 10, "fucking data");
    dictionary_insert(dict, "radiohead", 9, "fucking data");
    dictionary_insert(dict, "the_cure", 8, "fucking data");
    dictionary_insert(dict, "rem", 3, "fucking data");
    dictionary_display(dict);

    struct dictionary_node *searched = NULL;
    searched = dictionary_search(dict, "tool", 4);
    printf("searched: [key: %s, data: %s]\n", searched->key, searched->data);

    dictionary_remove(dict, "the_cure", 8);
    dictionary_remove(dict, "the_smiths", 10);
    dictionary_display(dict);

    return 0;
}
