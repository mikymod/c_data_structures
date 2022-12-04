#include <stdio.h>

#include "../set/set.h"
#include "dictionary.h"

int main()
{
    struct dictionary *dict = dictionary_new(2);

    dictionary_insert(dict, "tool", 4, "fucking data");
    dictionary_insert(dict, "the_smiths", 10, "fucking data");
    dictionary_insert(dict, "radiohead", 9, "fucking data");
    dictionary_insert(dict, "the_cure", 8, "fucking data");
    dictionary_insert(dict, "rem", 3, "fucking data");
    dictionary_insert(dict, "slipknot", 8, "fucking data");
    dictionary_insert(dict, "pinkfloyd", 9, "fucking data");
    dictionary_insert(dict, "idles", 5, "fucking data");
    dictionary_insert(dict, "shame", 5, "fucking data");
    dictionary_insert(dict, "fountain_dc", 11, "fucking data");
    dictionary_insert(dict, "porcupine_tree", 14, "fucking data");
    dictionary_insert(dict, "nick_cave", 9, "fucking data");

    // struct dictionary_node *searched = NULL;
    // searched = dictionary_search(dict, "tool", 4);
    // printf("searched: [key: %s, data: %s]\n", searched->key, (const char *)searched->data);

    // dictionary_remove(dict, "the_cure", 8);
    // dictionary_remove(dict, "the_smiths", 10);
    // dictionary_display(dict);

    return 0;
}
