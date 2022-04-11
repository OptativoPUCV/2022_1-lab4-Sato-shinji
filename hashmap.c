#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
    Pair *new = createPair(key, value);
    Pair **buckets = map->buckets;
    long index = hash(key, map->capacity);

    while(buckets[index])
    {
        if (!buckets[index]->key || !strcmp(buckets[index]->key, key)) return;
        index++;
        if (index >= map->capacity) index = 0;
    }


    map->buckets[index] = new;
    map->current = index;
    map->size++;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
    HashMap *new = (HashMap *) malloc(sizeof(HashMap));
    new->buckets = (Pair **) calloc(capacity, sizeof(Pair));
    new->size = 0;
    new->capacity = capacity;
    new->current = -1;

    return new;
}

void eraseMap(HashMap * map,  char * key) {
    Pair *par = searchMap(map, key);

    if(par)
    {
        par->key = NULL;
        map->size--;
    }
}

Pair * searchMap(HashMap * map,  char * key) {   
    Pair **buckets = map->buckets;
    long index = hash(key, map->capacity);

    while(buckets[index])
    {
        if (!strcmp(buckets[index]->key, key)) 
        {
            map->current = index;
            return buckets[index];
        }
        index++;
        if (index >= map->capacity) index = 0;
    }

    return NULL;
}

Pair * firstMap(HashMap * map) {
    long index = 0;
    while(!map->buckets[index])
    {
        index++;
        if (index >= map->capacity) return NULL;
    }
    map->current = index;
    return map->buckets[index];
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
