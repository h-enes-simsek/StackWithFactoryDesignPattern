/* (c) 2022 Hasan Enes Şimşek
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Stack implementation with factory design pattern in C

 * Note: I was inspired (stole actually) mostly from the answer in the link
 * https://stackoverflow.com/questions/17621544/dynamic-method-dispatching-in-c
 * stackoverflow user: @jxh
 *
 */

#include <stdio.h>
#include "stack_array.h"
#include "stack_list.h"
#include "stack_factory.h"

int main()
{
    printf("Stack with array implementation\n");
    struct Stack *s1 = stack_create(STACK_IMPLEMENTATION_ARRAY);

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
    stack_destroy(s1);
    
    
    printf("\n\nStack with linked list implementation\n");
    struct Stack *s2 = stack_create(STACK_IMPLEMENTATION_LIST);

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
