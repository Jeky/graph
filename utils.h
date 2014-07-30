#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#define NEW(type) (type*)malloc(sizeof(type))
#define NEW_ARRAY(type, size) (type*)malloc(sizeof(type) * size)

#endif