/* (c) 2022 Hasan Enes Şimşek
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Stack implementation with factory design pattern in C
 */

#include "stack.h"

int stack_top (struct Stack *s) { return s->vtable->top(s); }
void stack_pop (struct Stack *s) { s->vtable->pop(s); }
void stack_push (struct Stack *s, int x) { s->vtable->push(s, x); }
int stack_empty (struct Stack *s) { return s->vtable->empty(s); }
int stack_full (struct Stack *s) { return s->vtable->full(s); }
void stack_destroy (struct Stack *s) { s->vtable->destroy(s); }