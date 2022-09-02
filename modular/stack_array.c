/* (c) 2022 Hasan Enes Şimşek
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Stack implementation with factory design pattern in C
 */

#include <string.h>
#include <stdlib.h>
#include "stack_array.h"

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
