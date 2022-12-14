/* (c) 2022 Hasan Enes Şimşek
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Stack implementation with dynamic method dispatching in C

 * Note: I was inspired (stole actually) mostly from the answer in the link
 * https://stackoverflow.com/questions/17621544/dynamic-method-dispatching-in-c
 * stackoverflow user: @jxh
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE_MAX 5

struct Stack {
    const struct StackInterface * const vtable;
};

struct StackInterface {
    int (*top)(struct Stack *);
    void (*pop)(struct Stack *);
    void (*push)(struct Stack *, int);
    int (*empty)(struct Stack *);
    int (*full)(struct Stack *);
    void (*destroy)(struct Stack *);
};

int stack_top (struct Stack *s) { return s->vtable->top(s); }
void stack_pop (struct Stack *s) { s->vtable->pop(s); }
void stack_push (struct Stack *s, int x) { s->vtable->push(s, x); }
int stack_empty (struct Stack *s) { return s->vtable->empty(s); }
int stack_full (struct Stack *s) { return s->vtable->full(s); }
void stack_destroy (struct Stack *s) { s->vtable->destroy(s); }

// Stack with array -----

struct StackArray {
    struct Stack base;
    int idx;
    int array[STACK_SIZE_MAX];
};

static int stack_array_empty (struct Stack *s) { 
    struct StackArray *sa = (void *)s;
    if(sa != NULL)
        return sa->idx == 0;
    return -1;
}
static int stack_array_full (struct Stack *s) { 
    struct StackArray *sa = (void *)s;
    if(sa != NULL)
        return sa->idx == STACK_SIZE_MAX;
    return -1;
}

static int stack_array_top (struct Stack *s) { 
    struct StackArray *sa = (void *)s;
    if(stack_array_empty(s))
        return -1;
    else 
        return sa->array[sa->idx-1];
}
static void stack_array_pop (struct Stack *s) { 
    struct StackArray *sa = (void *)s;
    if(!stack_array_empty(s) && stack_array_empty(s) != -1)
        sa->idx--;
        
}
static void stack_array_push (struct Stack *s, int x) { 
    struct StackArray *sa = (void *)s;
    if(!stack_array_full(s) && stack_array_full(s) != -1)
    {
        sa->array[sa->idx] = x;
        sa->idx++;
    }
}

static void stack_array_destroy (struct Stack *s) {
    struct StackArray *sa = (void *)s;
    if(sa != NULL) {
        free(sa);
    }
}

struct Stack * stack_array_create () {
    static const struct StackInterface vtable = {
        stack_array_top, stack_array_pop, stack_array_push,
        stack_array_empty, stack_array_full, stack_array_destroy
    };
    static struct Stack base = { &vtable };
    struct StackArray *sa = malloc(sizeof(*sa));
    memcpy(&sa->base, &base, sizeof(base));
    sa->idx = 0;
    return &sa->base;
}

// Stack with linked list

struct StackNode {
    int val;
    struct StackNode *prev;
};

struct StackList {
    struct Stack base;
    struct StackNode *last;
};

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


int main()
{
    printf("Stack with array implementation\n");
    struct Stack *s1 = stack_array_create();

    stack_push(s1, 1);
    stack_push(s1, 2);
    printf("expected:2, output:%d\n",stack_top(s1));
    stack_pop(s1);
    printf("expected:1, output:%d\n",stack_top(s1));
    stack_pop(s1);
    stack_pop(s1);
    stack_pop(s1);
    printf("expected:-1, output:%d\n",stack_top(s1));
    stack_push(s1, 5);
    printf("expected:5, output:%d\n",stack_top(s1));
    stack_push(s1, 5);
    stack_push(s1, 5);
    stack_push(s1, 5);
    stack_push(s1, 5);
    stack_push(s1, 7);
    printf("expected:5, output:%d\n",stack_top(s1));
    stack_array_destroy(s1);
    
    printf("\n\nStack with linked list implementation\n");
    struct Stack *s2 = stack_list_create();

    stack_push(s2, 1);
    stack_push(s2, 2);
    printf("expected:2, output:%d\n",stack_top(s2));
    stack_pop(s2);
    printf("expected:1, output:%d\n",stack_top(s2));
    stack_pop(s2);
    stack_pop(s2);
    stack_pop(s2);
    printf("expected:-1, output:%d\n",stack_top(s2));
    stack_push(s2, 5);
    printf("expected:5, output:%d\n",stack_top(s2));
    stack_push(s2, 5);
    stack_push(s2, 5);
    stack_push(s2, 5);
    stack_push(s2, 5);
    stack_push(s2, 7);
    printf("expected:7, output:%d\n",stack_top(s2));
    stack_destroy(s2);
    
    getchar();
}
