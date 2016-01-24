//
//  ArrayStack.c
//  
//
//  Created by gamgoon on 2016. 1. 23..
//
//

#include "ArrayStack.h"

void AS_CreateStack(ArrayStack** Stack, int Capacity)
{
    (*Stack) = (ArrayStack*)malloc(sizeof(ArrayStack));
    (*Stack)->Nodes = (Node*)malloc(sizeof(Node) * Capacity); // 배열의 길이
    (*Stack)->Capacity = Capacity;
    (*Stack)->Top = 0;
}

void AS_DestroyStack(ArrayStack* Stack)
{
    free(Stack->Nodes);
    free(Stack);
}
void AS_Push(ArrayStack* Stack, ElementType Data)
{
    int position = Stack->Top;
    Stack->Nodes[position].Data = Data;
    Stack->Top++;
}

ElementType AS_Pop(ArrayStack* Stack)
{
    int position = --(Stack->Top);
    return Stack->Nodes[position].Data;
}

ElementType AS_Top(ArrayStack* Stack)
{
    int position = Stack->Top - 1;
    return Stack->Nodes[position].Data;
}

int AS_GetSize(ArrayStack* Stack)
{
    return Stack->Top;
}


int AS_IsEmpty(ArrayStack* Stack)
{
    return (Stack->Top == 0);
}
