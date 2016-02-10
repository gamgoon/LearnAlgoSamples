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
#include "Graph.h"

typedef Vertex* ElementTypex;

typedef struct tagNode
{
    ElementTypex Data;
    struct tagNode* NextNode;
} Node;

Node* SLL_CreateNode(ElementTypex NewData);
void SLL_DestroyNode(Node* Node);
void SLL_AppendNode(Node** Head, Node* NewNode);
void SLL_InsertAfter(Node* Current, Node* NewNode);
void SLL_InsertNewHead(Node** Head, Node* NewNode);
void SLL_RemoveNode(Node** Head, Node* Remove);
Node* SLL_GetNodeAt(Node* Head, int Location);
int SLL_GetNodeCount(Node* Head);

#endif /* LinkedList_h */
