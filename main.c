#include <stdio.h>
#include <string.h>
#include "store.h"
#include "gregstrings.h"

int main() {
  printf("Welcome to Gregis!\n");

  struct KVStore *kv_store = createKVStore(5, 10, 30);  
  
  addEntry(kv_store, "foo", "bar");
  
  struct Entry *fetched = getEntry(kv_store, "foo");

  printf("Value of fetched entry is %s.\n", fetched->value);

  struct Entry *non_existent = getEntry(kv_store, "bar");

  if (non_existent == NULL) {
    printf("No value exists for the key bar, correctly.\n");
  } else {
    printf("Found an entry for key \"bar\" with value %s.\n", non_existent->value);
  }

  addEntry(kv_store, "foo", "Gregory Jean-Baptiste");

  fetched = getEntry(kv_store, "foo");

  printf("Value of fetched entry is %s.\n", fetched->value);

  return 0;
}

