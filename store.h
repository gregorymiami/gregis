/* Include Guards? */
#ifndef GREGIS_STORE_H_
#define GREGIS_STORE_H_

typedef struct Entry {
  char *key;
  char *value;
} Entry;


typedef struct KVStore {
 struct Entry *entries;
 int store_size;
 int max_key_length;
 int max_value_length;
} KVStore;

struct Entry makeEntry(char *, int, char *, int);

struct KVStore *createKVStore(int, int, int);

int addEntry(struct KVStore *, char *, char *);

struct Entry *getEntry(struct KVStore *, char *);

#endif

