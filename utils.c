#include "utils.h"


Array *createArray(){
    Array *array = NEW(Array);

    array->length = 0;
    array->values = NEW_ARRAY(int, DEFAULT_ARRAY_SIZE);
    array->capacity = DEFAULT_ARRAY_SIZE;

    return array;
}

void destroyArray(Array *array){
    free(array->values);
    free(array);
}

void encapsulateArray(Array *array){
    int *tmp = array->values;
    int i = 0;

    array->capacity *= 2;
    array->values = NEW_ARRAY(int, array->capacity);

    for(i = 0; i < array->length; i++){
        array->values[i] = tmp[i];
    }

    free(tmp);
}

void arrayAdd(Array *array, int val){
    if(array->length == array->capacity){
        encapsulateArray(array);
    }

    array->values[array->length++] = val;
}
