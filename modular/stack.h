/* (c) 2022 Hasan Enes Şimşek
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Stack implementation with factory design pattern in C
 */

#define STACK_SIZE_MAX 5

// generic stack operations, every implementation of a stack should use these functions
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

int stack_top (struct Stack *s);
void stack_pop (struct Stack *s);
void stack_push (struct Stack *s, int x);
int stack_empty (struct Stack *s);
int stack_full (struct Stack *s);
void stack_destroy (struct Stack *s);