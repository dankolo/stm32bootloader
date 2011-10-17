#include "queue.h"
#include <stdio.h>
#include <assert.h>

#define QUEUE_ZIZE 1024
#define ARRAY_SIZE (QUEUE_ZIZE+1)

static QUEUE_TYPE queue[ARRAY_SIZE];
static size_t front=1;
static size_t rear=0;


void insert_one(QUEUE_TYPE value)
{
  assert(!is_full());
  rear=(rear+1)%ARRAY_SIZE;
  queue[rear]=value;
}


void delete_one(void)
{
  assert(!is_empty());
  front=(front+1)%ARRAY_SIZE;
}


QUEUE_TYPE first(void)
{
  assert(!is_empty());
  return queue[front];
}

uint8_t is_empty(void)
{
  return (rear+1)%ARRAY_SIZE==front;
}

uint8_t is_full(void)
{
  return (rear+2)%ARRAY_SIZE==front;
}