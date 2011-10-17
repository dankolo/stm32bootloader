#ifndef __QUEUE_H
#define __QUEUE_H


#include "stm32f10x.h"
#include <stdlib.h>

#define QUEUE_TYPE uint8_t

void insert_one(QUEUE_TYPE value);

void delete_one(void);

QUEUE_TYPE first(void);

uint8_t is_empty(void);

uint8_t is_full(void);

#endif
