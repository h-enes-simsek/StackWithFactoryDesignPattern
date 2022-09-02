/* (c) 2022 Hasan Enes Şimşek
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Stack implementation with factory design pattern in C
 */
 
#include <string.h>
#include <stdlib.h>
#include "stack_list.h"

static int stack_list_empty (struct Stack *s) {
    struct StackList *sl = (void *)s;
    return !sl->last;
}
static int stack_list_full (struct Stack *s) {
    return 0; // linked list limitless
}
static int stack_list_top (struct Stack *s) {
    struct StackList *sl = (void *)s;
    if(sl->last)
        return (sl->last)->val;
    else
        return -1;
}
static void stack_list_pop (struct Stack *s) {
    struct StackList *sl = (void *)s;
    if(!stack_list_empty(s)) {
        struct StackNode* lastNode = sl->last;
        sl->last = lastNode->prev;
        free(lastNode);
    }
}
static void stack_list_push (struct Stack *s, int x) {
    struct StackList *sl = (void *)s;
    if(stack_list_empty(s)) {
        struct StackNode* newNode = malloc(sizeof(*newNode));
        newNode->prev = NULL;
        newNode->val = x;
        sl->last = newNode;
    } 
    else {
        struct StackNode* newNode = malloc(sizeof(*newNode));
        newNode->val = x;
        newNode->prev = sl->last;
        sl->last = newNode;
    }
}
static void stack_list_destroy (struct Stack *s) {
    struct StackList *sl = (void *)s;
    if(sl) {
        while(!stack_list_empty(s)) {
            stack_list_pop(s);
        }
        free(sl);
    }
}

struct Stack * stack_list_create () {
    static const struct StackInterface vtable = {
        stack_list_top, stack_list_pop, stack_list_push,
        stack_list_empty, stack_list_full, stack_list_destroy
    };
    static struct Stack base = { &vtable };
    struct StackList *sl = malloc(sizeof(*sl));
    memcpy(&sl->base, &base, sizeof(base));
    sl->last = NULL;
    return &sl->base;
}