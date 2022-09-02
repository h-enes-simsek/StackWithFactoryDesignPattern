/* (c) 2022 Hasan Enes Şimşek
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Stack implementation with factory design pattern in C
 */

#include <stddef.h> // for NULL
#include "stack_factory.h"

struct Stack * stack_create(Stack_imp_type t)
{
    if(t == STACK_IMPLEMENTATION_ARRAY)
        return stack_array_create();
    else if(t == STACK_IMPLEMENTATION_LIST)
        return NULL; // not yet implemented
    else 
        return NULL;
}