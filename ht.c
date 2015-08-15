#define _XOPEN_SOURCE 500

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "ht.h"

struct hashtable *htCreate(int size)
{
        struct hashtable *hashtable = NULL;
        int i;
        if ( size < 1 ) return NULL;

        if ((hashtable = malloc(sizeof(struct hashtable))) == NULL)
                return NULL;

        /* Allocate pointers to the head nodes. */
        if ((hashtable->table = malloc(sizeof(struct htEntry *) * size )) == NULL )
                return NULL;
        for( i = 0; i < size; i++ )
                hashtable->table[i] = NULL;

        hashtable->size = size;
        return hashtable;
}

int htHash(struct hashtable *hashtable, char *key )
{
        unsigned long int hashval;
        unsigned int i = 0;

        /* Convert our string to an integer index */
        while ( hashval < ULONG_MAX && i < strlen(key) ) {
                hashval = hashval << 8;
                hashval += key[i];
                i++;
        }
        return hashval % hashtable->size;
}

struct htEntry *htNewpair(char *key, char *value)
{
        struct htEntry *newpair;

        if ((newpair = malloc(sizeof(struct htEntry))) == NULL)
                return NULL;
        if ((newpair->key = strdup(key)) == NULL)
                return NULL;
        if ((newpair->value = strdup(value)) == NULL)
                return NULL;
        newpair->next = NULL;

        return newpair;
}

/* Insert a key-value pair into a hash table. */
void htSet(struct hashtable *hashtable, char *key, char *value)
{
        int bin = 0;
        struct htEntry *newpair = NULL;
        struct htEntry *next = NULL;
        struct htEntry *last = NULL;

        bin = htHash(hashtable, key);

        next = hashtable->table[bin];

        while ( next != NULL && next->key != NULL && strcmp( key, next->key ) > 0 ) {
                last = next;
                next = next->next;
        }

        /* There's already a pair.  Let's replace that string. */
        if ( next != NULL && next->key != NULL && strcmp(key, next->key) == 0 ) {
                free( next->value );
                next->value = strdup(value);
                /* Nope, could't find it.  Time to grow a pair. */
        } else {
                newpair = htNewpair(key, value);
                /* We're at the start of the linked list in this bin. */
                if ( next == hashtable->table[bin] ) {
                        newpair->next = next;
                        hashtable->table[bin] = newpair;
                        /* We're at the end of the linked list in this bin. */
                } else if ( next == NULL ) {
                        last->next = newpair;
                        /* We're in the middle of the list. */
                } else  {
                        newpair->next = next;
                        last->next = newpair;
                }
        }
}

char *htGet(struct hashtable *hashtable, char *key)
{
        int bin = 0;
        struct htEntry *pair;

        bin = htHash(hashtable, key);

        /* Step through the bin, looking for our value. */
        pair = hashtable->table[ bin ];
        while ( pair != NULL && pair->key != NULL && strcmp( key, pair->key ) > 0 )
                pair = pair->next;

        /* Did we actually find anything? */
        if ( pair == NULL || pair->key == NULL || strcmp( key, pair->key ) != 0 )
                return NULL;
        else return pair->value;
}
