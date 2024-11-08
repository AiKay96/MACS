#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <search.h>

void VectorNew(vector *v, int elemSize, VectorFreeFunction freeFn, int initialAllocation){
    assert(elemSize > 0 && initialAllocation >= 0);
    v->elemSize = elemSize;
    v->freeFn = freeFn;
    v->allocatedSize = initialAllocation;
    if(initialAllocation == 0)
        v->allocatedSize = 4;
    v->logicalSize = 0;
    v->arr = malloc(v->elemSize * v->allocatedSize);
    assert(v->arr != NULL);
}

void VectorDispose(vector *v){
    if(v->freeFn != NULL)
        for(int i = 0; i < v->logicalSize; i++)
            v->freeFn((char*)v->arr + i * v->elemSize);
    free(v->arr);
}

int VectorLength(const vector *v){
    return v->logicalSize;
}

void *VectorNth(const vector *v, int position){
    assert(position >= 0 && position < v->logicalSize);
    return (char*)v->arr + position * v->elemSize;
}

void VectorReplace(vector *v, const void *elemAddr, int position){
    assert(position >= 0 && position < v->logicalSize);
    void* NthElem = VectorNth(v, position);
    if(v->freeFn != NULL)
        v->freeFn(NthElem);
    memcpy(NthElem, elemAddr, v->elemSize);
}
void grow(vector *v){
    v->arr = realloc(v->arr, 2 * v->allocatedSize * v->elemSize);
    assert(v->arr != NULL);
    v->allocatedSize *= 2;
}

void VectorInsert(vector *v, const void *elemAddr, int position){
    assert(position >= 0 && position <= v->logicalSize);
    if(v->logicalSize == v->allocatedSize)
        grow(v);
    if(position == v->logicalSize)
        memcpy((char*)v->arr + v->logicalSize * v->elemSize, elemAddr, v->elemSize);
    else{
        void* NthElem = VectorNth(v, position);
        memmove((char*)NthElem + v->elemSize, NthElem, v->elemSize * (v->logicalSize - position));
        memcpy(NthElem, elemAddr, v->elemSize);
    }
    v->logicalSize++;
}

void VectorAppend(vector *v, const void *elemAddr){
    VectorInsert(v, elemAddr, v->logicalSize);
}

void VectorDelete(vector *v, int position){
    assert(position >= 0 && position < v->logicalSize);
    void* NthElem = VectorNth(v, position);
    if(v->freeFn != NULL)
        v->freeFn(NthElem);
    if(position != v->logicalSize - 1)
        memmove(NthElem, (char*)NthElem + v->elemSize, v->elemSize * (v->logicalSize - position - 1));
    v->logicalSize--;
}

void VectorSort(vector *v, VectorCompareFunction compare){
    assert(compare != NULL);
    qsort(v->arr, v->logicalSize, v->elemSize, compare);
}

void VectorMap(vector *v, VectorMapFunction mapFn, void *auxData){
    assert(mapFn != NULL);
    for(int i = 0; i < v->logicalSize; i++)
        mapFn((char*)v->arr + i * v->elemSize, auxData);
}

static const int kNotFound = -1;
int VectorSearch(const vector *v, const void *key, VectorCompareFunction searchFn, int startIndex, bool isSorted){
    assert(startIndex >= 0 && startIndex <= v->logicalSize && searchFn != NULL);
    void* NthElem;
    void* base = (char*)v->arr + startIndex*v->elemSize;
    size_t searchSize = v->logicalSize - startIndex;
    if(isSorted)
        NthElem = bsearch(key, base, searchSize, v->elemSize, searchFn);
    else
        NthElem = lfind(key, base, &searchSize, v->elemSize, searchFn);
    if(NthElem == NULL)
        return kNotFound;
    return ((char*)NthElem - (char*)v->arr) / v->elemSize;
} 
