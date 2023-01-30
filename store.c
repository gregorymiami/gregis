#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include "gregstrings.h"
#include "store.h"

struct Entry makeEntry(char * key, int key_length, char * value, int value_length) {
  struct Entry entry;
  entry.key = (char*)malloc(sizeof(char) * (key_length + 1));
  entry.value = (char*)malloc(sizeof(char) * (value_length + 1));
  greg_string_copy(key, entry.key);
  greg_string_copy(value, entry.value);
  return entry;
}

struct KVStore *createKVStore(int store_size, int max_key_length, int max_value_length) {
  struct KVStore *kv_store = (struct KVStore*)malloc(sizeof(struct KVStore));
  kv_store->max_key_length = max_key_length;
  kv_store->max_value_length = max_value_length;
  kv_store->store_size = store_size;
  
  kv_store->entries = (struct Entry*)malloc(sizeof(struct Entry) * kv_store->store_size);

  for (int i = 0; i < kv_store->store_size; i++) {
    kv_store->entries[0].key = NULL;
    kv_store->entries[0].value = NULL; 
  } 

  return kv_store; 
}

int addEntry(struct KVStore *kv_store, char * key, char * value) {
  if (key == NULL || value == NULL) {
    printf("key and value must not be null.");
    return 1;
  }   

  int key_length = greg_string_length(key);
  int value_length = greg_string_length(value);
  
  if (key_length == 0) {
    printf("key must be non-empty.");
    return 1;
  }

  if (key_length > kv_store->max_key_length || value_length > kv_store->max_value_length) {
    printf("Key length is %d, max key length allowed is %d.\n", key_length, kv_store->max_key_length);
    printf("Value length is %d, max value length allowed is %d.\n", value_length, kv_store->max_value_length);  
    printf("key-value length error.\n");
    return 1;
  }

  struct Entry *existing_entry = getEntry(kv_store, key);

  if (existing_entry != NULL) {
    printf("overwritting existing key.\n"); 
    char *value_copy = (char*)malloc(sizeof(char) * (value_length + 1));
    greg_string_copy(value, value_copy);
    existing_entry->value = value_copy;
    printf("key %s with value %s successfully added.\n", key, value_copy);
    return 0;
  }

  for (int i = 0; i < kv_store->store_size; i++) {
    if (kv_store->entries[i].key == NULL) {
      char *key_copy = (char*)malloc(sizeof(char) * (key_length + 1));
      greg_string_copy(key, key_copy);      
      kv_store->entries[i].key = key_copy; 
      char *value_copy = (char*)malloc(sizeof(char) * (value_length + 1));
      greg_string_copy(value, value_copy);
      kv_store->entries[i].value = value_copy;
      printf("key %s with value %s successfully added.\n", key_copy, value_copy);
      return 0;
    } 
  }
  
  printf("no more space in the key-value store.");
  return 2;
}


struct Entry *getEntry(struct KVStore *kv_store, char *key) {
  if (key == NULL) {
    printf("key cannot be null");
    return NULL;
  }

  if (kv_store == NULL) {
    printf("the key value store must not be null");
    return NULL;
  }

  for (int i = 0; i < kv_store->store_size; i++) {
    if (greg_string_compare(kv_store->entries[i].key, key) == 0) {
       return &kv_store->entries[i];
    }    
  }

  return NULL; 
}
