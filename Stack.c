#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;
typedef double f64;


typedef struct {

    i16 *collection;
    i16 capacity;
    u16 size;

}Node;



Node *createStack(i16 capacity);
void destroyStack(Node *stack);
bool isFull(Node const *stack);
bool isEmpty(Node const *stack);
bool pop(Node *stack, i16 *item);
bool push(Node *stack, i16 item);
bool peek(Node const *stack, i16 *item);

Node *createStack(i16 const capacity) {

    if (capacity <= 0) {return NULL;}

    Node *stack = malloc(sizeof(Node));
    if (stack == NULL) {return NULL;}

    stack->collection = malloc(sizeof(i16) * capacity);
    if (stack->collection == NULL) {
        free(stack);
        return NULL;
    }

    stack->capacity = capacity;
    stack->size = 0;

    return stack;
}

void destroyStack(Node *stack) {
    free(stack->collection);
    free(stack);
}

bool isFull(Node const *stack) {
   return stack -> capacity == stack -> size;
}

bool isEmpty(Node const *stack) {
    return stack -> size == 0;
}

bool push(Node *stack, i16 const item) {

    if (isFull(stack)) return false;

    stack -> collection[stack -> size] = item;
    stack -> size++;

    return true;
}

bool peek(Node const *stack, i16 *item) {
    if (isEmpty(stack)) return false;

    *item = stack->collection[stack -> size-1];

    return true;
}

bool pop(Node *stack, i16 *item) {
    if (isEmpty(stack)) return false;

    //Pointer item is used to print the removed item
    stack -> size--;
    *item = stack->collection[stack -> size];


    return true;
}


int main() {

    Node *stack = createStack(5);

    if (stack == NULL) {
        printf("Error in creating stack\n");
        return 1;
    }

    if (isEmpty(stack)) {
        printf("Stack is empty\n");
    }

    push(stack, 10);
    printf("Stack size %d \n",stack->size);
    push(stack, 9);
    push(stack, 4);
    push(stack, 7);
    push(stack, 8);
    printf("Stack size %d \n",stack->size);

    if (isFull(stack)) printf("Stack is full\n");

    bool const tryPush = push(stack, 5);
    if (tryPush == false) printf("Push failed \n");

    i16 peekValue = 0;
    peek(stack, &peekValue);

    printf("Peek value %d \n",peekValue);

    i16 popValue = 0;

    for (u8 i = 0; i < 5; i++) {
        pop(stack, &popValue);
        printf("Pop value %d \n",popValue);
    }

    bool const tryPop = pop(stack, &popValue);
    if (tryPop == false) printf("Pop failed \n");

    bool const tryPeak = peek(stack, &popValue);
    if (tryPeak == false) printf("Peak failed \n");

    destroyStack(stack);

    return 0;
}