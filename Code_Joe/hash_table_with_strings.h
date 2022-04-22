#ifndef HASH_TABLE_WITH_STRINGS_H__ 
#define HASH_TABLE_WITH_STRINGS_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct list_data
{
    int *IDo;
    int *IDd;
    int *Hod;
    float *Avt;
    char *key_string;
    struct list_data *next;
};

typedef struct list_data list_t;

struct hash_table_data 
{
    int size;           /* the size of the table */
    list_t **table;     /* the table elements    */
    int elements;       /*the number of elements   */
};

typedef struct hash_table_data  hash_table_t;

/**
 *  It creates a new (string) hash table.
 **/
 
hash_table_t *hash_table_create(int size);

/**
 *  Hash function
 **/
unsigned int hash(hash_table_t *hashtable, char *key_string);

/**
 *  It removes an element from the table
 **/
int hash_table_remove_data_string(hash_table_t *hashtable, char *key_string);

/**
 * It returns an element of the table. NULL if it is not found
 */

char* hash_table_lookup_data_string(hash_table_t *hashtable, char *key_string);

/**
 *It adds a new tuple in the hash table ((unique)key_string, data_string)
 */ 
int hash_table_add_data_string(hash_table_t *hashtable, char *key_string, char *data_string);

/**
 * Removing the hash table
 */
int hash_table_free(hash_table_t ** ptr_hashtable);

/**
 * Printing out all information (debuging)
 */ 
int hash_table_print(hash_table_t* hashtable);

/**
 *Resizing the table
 */
int hash_table_resize(hash_table_t* hashtable, int size);

#endif
