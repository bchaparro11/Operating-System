//
//gcc -Wall *.c -o data_string_hash_table
//valgrind ./data_string_hash_table
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table_with_strings.h"



/*create */
hash_table_t *hash_table_create(int size)
{
    int i;
    hash_table_t *new_table=NULL;    
    if (size<1)
    {
      return NULL;
    }
    /*space for the table */
    if ((new_table = calloc(1,sizeof(hash_table_t))) == NULL) 
    {
        return NULL;
    }        
    if ((new_table->table = calloc(1,sizeof(list_t*) * size)) == NULL) 
    {      
        free(new_table);
        return NULL;
    }
    /* Inicialization of the internal table */  
    for(i=0; i<size; i++) 
    {
      new_table->table[i] = NULL;
    }
    new_table->size = size;
    return new_table;
}

/*hash function to select the position of the array */ 
unsigned int hash(hash_table_t *hashtable, char *key_string)
 {
    if(hashtable==NULL)
    { 
      return 0;
    }
    if(key_string==NULL)
    { 
      return 0;
    }           
   unsigned int hashval=0;    
        
    for(; *key_string != '\0'; key_string++) 
    {
      hashval = *key_string + (hashval << 5) - hashval;    
    }
    return hashval % hashtable->size;
 }

 
/*Internal lookup_  */ 
list_t *hash_table_lookup_data_string_(hash_table_t *hashtable, char *key_string)
{
    if(hashtable==NULL)
    { 
      return NULL;
    }
    if(key_string==NULL)
    { 
      return NULL;
    }      
      
    list_t *list;
    unsigned int hashval = hash(hashtable, key_string);
    for(list = hashtable->table[hashval]; list != NULL; list = list->next) 
    {
        if (strcmp(key_string, list->key_string) == 0) 
	{
	  return list;
	}
    }
    return NULL;
}

/*remove  */ 
int hash_table_remove_data_string(hash_table_t *hashtable, char *key_string)
{
    if(hashtable==NULL)
    { 
      return -1;
    }
    if(key_string==NULL)
    { 
      return -2;
    }      
    
    list_t *list;
    list_t *prev;
    unsigned int hashval = hash(hashtable, key_string);
    
    for(list = hashtable->table[hashval], prev=NULL; list != NULL; prev=list, list = list->next) 
    {
        if (strcmp(key_string, list->data_string) == 0) 
	{
	  if(prev==NULL){
	    hashtable->table[hashval]=list->next;	    
	  }else{
	    prev->next=list->next;	  
	  } 
	 free(list->data_string);
	 free(list->key_string);
	 free(list);
	 hashtable->elements--;
	 return 0;
	}
    }
    return -1;
}


/* lookup */
char* hash_table_lookup_data_string(hash_table_t *hashtable, char *key_string)
{      
  list_t* ptr=hash_table_lookup_data_string_(hashtable,key_string);
  
  if(ptr==NULL)
  {
    return NULL;
    
  }
  else
  {  
    return ptr->data_string;  
  }
}

/* Adding element */ 
int hash_table_add_data_string(hash_table_t *hashtable, char *key_string, char *data_string)
{
    if(hashtable==NULL)
    { 
      return -1;
    }
    if(key_string==NULL)
    { 
      return -2;
    }      
    if(data_string==NULL)
    { 
      return -3;
    }   
    list_t *new_list=NULL;
    list_t *current_list=NULL;
    unsigned int hashval = hash(hashtable, key_string);
    if ((new_list = malloc(sizeof(list_t))) == NULL) 
    {     
      return -1;
    }
    current_list = hash_table_lookup_data_string_(hashtable, key_string);
    if (current_list != NULL)
    {
      return -2;
    }
    /* Insert into list by the head */
    new_list->key_string = strdup(key_string);
    new_list->data_string = strdup(data_string);
    new_list->next = hashtable->table[hashval];
    hashtable->table[hashval] = new_list;
    hashtable->elements++;
    return 0;
}

/* Removing */ 
int hash_table_free(hash_table_t ** ptr_hashtable)
{   /*Safety issues*/
    if(ptr_hashtable == NULL)
    {
      return -1;
      
    }
    hash_table_t* hashtable=NULL;
    hashtable= (*ptr_hashtable);
    if (hashtable == NULL) 
    { 
      return -2;
    }
    int i=0;
    list_t *list;
    list_t *temp;    
    for(i=0; i<hashtable->size; i++) 
    {
        list = hashtable->table[i];
        while(list!=NULL) {
            temp = list;
            list = list->next;
            free(temp->data_string);
	    free(temp->key_string);
            free(temp);
	    hashtable->elements--;
        }
    }
    /* Free the table itself */
    free(hashtable->table);
    free(hashtable);
    (*ptr_hashtable)=NULL;
    return 0;
}

/* Printing out the table */ 
int hash_table_print(hash_table_t* hashtable)
{
   if(hashtable==NULL)
    { 
      return -1;
    }
    
    int aux_printing=0;
    int i=0;
    list_t *list=NULL;

    if (hashtable == NULL) 
      { 
	return 0;
      }
    
    for(i=0; i<hashtable->size; i++)  
      {
        list = hashtable->table[i];
        while(list!=NULL) 
	{
            printf("\n[%d][%d](key,value):\t \%20s : \%20s",i, (aux_printing++),
		   list->key_string,list->data_string);	   
            list = list->next;
        }
      }    
  return 0 ;    
}

/*resize*/
int hash_table_resize(hash_table_t* hashtable, int size)
{
  if(hashtable==NULL)
  {
    return -1;
  }
  if(size<0)
  {
    return -2;
  }  
  //Creating and isolated 
  hash_table_t* ht2=hash_table_create(size);
  int i=0;
  list_t *list;
  list_t *temp;    
  for(i=0; i<hashtable->size; i++) 
    {
        list = hashtable->table[i];
        while(list!=NULL) 
	{
            temp = list;
            list = list->next;
	    hash_table_add_data_string(ht2,temp->key_string,temp->data_string);
            free(temp->data_string);
	    free(temp->key_string);
	    free(temp);		    
	}
    }
  free(hashtable->table);  
  (*hashtable)=(*ht2);
  free(ht2);
  return 0;
}


int main()
{
  printf("\n ***Checking the code \n");
  printf("\n ***Creating hash table with 1 queue \n");
  hash_table_t* h1 =hash_table_create(1);
  printf("\n ***Adding 4 elements \n");
  hash_table_add_data_string(h1,"uno","1");
  hash_table_add_data_string(h1,"one","1");
  hash_table_add_data_string(h1,"two","2");
  hash_table_add_data_string(h1,"two","22"); //It should fail
  hash_table_add_data_string(h1,"three","3");
  hash_table_add_data_string(h1,"four", "4");
  
  hash_table_remove_data_string(h1,"uno");
  char* element_two=NULL;
  element_two=hash_table_lookup_data_string(h1,"two");
  if (element_two!=NULL)
  {
    printf ("\n *** Element \"two\" is: %s", element_two);
  }
  
  
  printf("\n***Dumping the queue \n");
  hash_table_print(h1);
  printf("\n***Resizing the table to 4 queues \n");    
  hash_table_resize(h1,4);
  printf("\n***Dumping the queue \n");
  hash_table_print(h1);  
  printf("\n***Releasing the hashtable \n");
  hash_table_free(&h1);
  return 0; 
}

 
