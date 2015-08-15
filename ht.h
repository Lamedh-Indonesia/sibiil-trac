#ifndef HT_H
#define HT_H


struct htEntry {
        char *key;
        char *value;
        struct htEntry *next;
};

struct hashtable {
        int size;
        struct htEntry **table;
};

struct hashtable *htCreate(int size);                            /* Create a new hashtable. */
struct htEntry *htNewpair(char *key, char *value);               /* Create a key-value pair. */
int htHash(struct hashtable *hashtable, char *key);              /* Hash a string for a particular hash table. */
void htSet(struct hashtable *hashtable, char *key, char *value); /* Insert a key-value pair into a hash table. */
char *htGet(struct hashtable *hashtable, char *key);             /* Retrieve a key-value pair from a hash table. */

#endif /* HT_H */
