/* (c) 2022 Hasan Enes Şimşek
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Stack implementation with factory design pattern in C
 */

#include "stack.h"

// stack implementation with an array
struct StackArray {
    struct Stack base;
    int idx;
    int array[STACK_SIZE_MAX];
};

static int stack_array_empty (struct Stack *s);
static int stack_array_full (struct Stack *s);
static int stack_array_top (struct Stack *s);
static void stack_array_pop (struct Stack *s);
static void stack_array_push (struct Stack *s, int x);
static void stack_array_destroy (struct Stack *s);
struct Stack * stack_array_create ();