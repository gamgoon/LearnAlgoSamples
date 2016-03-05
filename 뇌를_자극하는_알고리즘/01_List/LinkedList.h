//
//  LinkedList.h
//  LearnAlgo
//
//  Created by gamgoon on 2016. 1. 21..
//  Copyright © 2016년 gamgoon. All rights reserved.
//

#ifndef LinkedList_h
#define LinkedList_h

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct tagNode
{
    ElementType Data;
    struct tagNode* NextNode;
} Node;

Node* SLL_CreateNode(ElementType NewData);
void SLL_DestroyNode(Node* Node);
void SLL_AppendNode(Node** Head, Node* NewNode);
void SLL_InsertAfter(Node* Current, Node* NewNode);
void SLL_InsertNewHead(Node** Head, Node* NewNode);
void SLL_RemoveNode(Node** Head, Node* Remove);
Node* SLL_GetNodeAt(Node* Head, int Location);
int SLL_GetNodeCount(Node* Head);

/* Quiz */
// void SLL_InsertBefore(Node* Current, Node* NewNode);
void SLL_DestroyAllNodes(Node* List);

#endif /* LinkedList_h */
