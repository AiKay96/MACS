#include "hashset.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void HashSetNew(hashset *h, int elemSize, int numBuckets,
		HashSetHashFunction hashfn, HashSetCompareFunction comparefn, HashSetFreeFunction freefn){
			assert(elemSize > 0 && numBuckets > 0 && hashfn != NULL && comparefn != NULL);
			h->elemSize = elemSize;
			h->allocatedSize = numBuckets;
			h->logicalSize = 0;
			h->hashfn = hashfn;
			h->comparefn = comparefn;
			h->freefn = freefn;
			h->arr = malloc(h->allocatedSize * sizeof(vector));
			assert(h->arr != NULL);
			for(int i = 0; i < h->allocatedSize; i++)
				VectorNew(&h->arr[i], h->elemSize, h->freefn, 0);
		}

void HashSetDispose(hashset *h){
	for(int i = 0; i < h->allocatedSize; i++)
		VectorDispose(&h->arr[i]);
	free(h->arr);
}

int HashSetCount(const hashset *h){
	return h->logicalSize;
}

void HashSetMap(hashset *h, HashSetMapFunction mapfn, void *auxData){
	assert(mapfn != NULL);
	for(int i = 0; i < h->allocatedSize; i++)
		VectorMap(&h->arr[i], mapfn, auxData);
}

void HashSetEnter(hashset *h, const void *elemAddr){
	assert(elemAddr != NULL);
	int index = h->hashfn(elemAddr, h->allocatedSize);
	assert(index >= 0 && index < h->allocatedSize);
	int contains = VectorSearch(&h->arr[index], elemAddr, h->comparefn, 0, false);
	if(contains == -1){
		VectorAppend(&h->arr[index], elemAddr);
		h->logicalSize++;
	}else
		VectorReplace(&h->arr[index], elemAddr, contains);
}

void *HashSetLookup(const hashset *h, const void *elemAddr){
	assert(elemAddr != NULL);
	int index = h->hashfn(elemAddr, h->allocatedSize);
	assert(index >= 0 && index < h->allocatedSize);
	int contains = VectorSearch(&h->arr[index], elemAddr, h->comparefn, 0, false);
	if(contains == -1)
		return NULL;
	else
		return VectorNth(&h->arr[index], contains);
}
