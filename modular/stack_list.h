/* (c) 2022 Hasan Enes Şimşek
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Stack implementation with factory design pattern in C
 */
 
#ifndef STACK_LIST_H
#define STACK_LIST_H

#include "stack.h"

// stack implementation with a linked list
struct StackNode {
    int val;
    struct StackNode *prev;
};

struct StackList {
    struct Stack base;
    struct StackNode *last;
};

static int stack_list_empty (struct Stack *s);
static int stack_list_full (struct Stack *s);
static int stack_list_top (struct Stack *s);
static void stack_list_pop (struct Stack *s);
static void stack_list_push (struct Stack *s, int x);
static void stack_list_destroy (struct Stack *s);
struct Stack * stack_list_create ();

#endif