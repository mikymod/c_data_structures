#include <stdio.h>

#include "../set/set.h"
#include "dictionary.h"

int main()
{
    struct dictionary *dict = dictionary_new(2);

    dictionary_insert(dict, "tool", 4, "some data");
    dictionary_insert(dict, "the_smiths", 10, "some data");
    dictionary_insert(dict, "radiohead", 9, "some data");
    dictionary_insert(dict, "low", 3, "some data");
    dictionary_insert(dict, "antony", 6, "some data");
    dictionary_insert(dict, "flaming_lips", 12, "some data");
    dictionary_insert(dict, "the_notwist", 11, "some data");
    dictionary_insert(dict, "idles", 5, "some data");
    dictionary_insert(dict, "shame", 5, "some data");
    dictionary_insert(dict, "fontaines_dc", 12, "some data");
    dictionary_insert(dict, "porcupine_tree", 14, "some data");
    dictionary_insert(dict, "nick_cave", 9, "some data");

    int key = 12;
    dictionary_insert(dict, &key, sizeof(int), "fucking data");

    struct dictionary_node *searched = NULL;
    searched = dictionary_search(dict, (void *)"tool", 4);
    printf("searched: [key: %s, data: %s]\n", searched->key, (const char *)searched->data);

    dictionary_remove(dict, "the_cure", 8);
    dictionary_remove(dict, "the_smiths", 10);
    dictionary_display(dict);

    return 0;
}
