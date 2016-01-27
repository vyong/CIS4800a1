/*****


*****/

#include "Shape.h"
#define Boolean int
#define true 1
#define false 0

Shape * shape_create(void) {
    
    Shape * head = malloc(sizeof(Shape));
    head->next = NULL;
    
    return head;
}