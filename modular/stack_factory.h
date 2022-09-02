/* (c) 2022 Hasan Enes Şimşek
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Stack implementation with factory design pattern in C
 */

#ifndef STACK_FACTORY_H
#define STACK_FACTORY_H

// a stack can be implemented with an array or a linked list
typedef enum 
{
    STACK_IMPLEMENTATION_ARRAY,
    STACK_IMPLEMENTATION_LIST
} Stack_imp_type;


// it decides which type of stack will be created
struct Stack * stack_create(Stack_imp_type);

#endif