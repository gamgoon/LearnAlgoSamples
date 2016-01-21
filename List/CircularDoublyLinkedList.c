//
//  CircularDoublyLinkedList.c
//  LearnAlgo
//
//  Created by 감윤욱 on 2016. 1. 21..
//  Copyright © 2016년 감윤욱. All rights reserved.
//

#include "CirCularDoublyLinkedList.h"

/* 노드 생성 */
Node* CDLL_CreateNode(ElementType NewData)
{
    Node* NewNode = (Node*)malloc(sizeof(Node));
    
    NewNode->Data = NewData;
    NewNode->PrevNode = NULL;
    NewNode->NextNode = NULL;
    
    return NewNode;
}

/* 노드 소멸 */
void CDLL_DestroyNode(Node* Node)
{
    free(Node);
}

/* 노드 추가 */
void CDLL_AppendNode(Node** Head, Node* NewNode)
{
    /* 헤드 노드가 NULL이라면 새로운 노드가 Head */
    if ((*Head) == NULL) {
        *Head = NewNode;
        (*Head)->NextNode = *Head;
        (*Head)->PrevNode = *Head;
    } else {
        /* 이전 리스트에서는 테일을 찾기위해 정주행 했지만, 환형은 테일을 찾는게 간단. */
        Node* Tail = (*Head)->PrevNode;

        Tail->NextNode->PrevNode = NewNode; // TODO:(*Head)->PrevNode = NewNode; 하면 안되는건가?
        Tail->NextNode = NewNode;

        NewNode->NextNode = (*Head);
        NewNode->PrevNode = Tail; 
    }

}

/* 노드 삽입 */
void CDLL_InsertAfter(Node* Current, Node* NewNode){
    NewNode->NextNode = Current->NextNode;
    NewNode->PrevNode = Current;

    if (Current->NextNode != NULL)
    {
        Current->NextNode->PrevNode = NewNode;
        Current->NextNode = NewNode;
    }
    

}

/* 노드 탐색 : 비효율적 구현. 링크드 리스트의 특징(단점) */
Node* CDLL_GetNodeAt(Node* Head, int Location)
{
    Node* Current = Head;
    
    while (Current != NULL && (--Location >= 0)) {
        Current = Current->NextNode;
    }
    
    return Current;
}

/* 노드 삭제 */
void CDLL_RemoveNode(Node** Head, Node* Remove)
{
    if (*Head == Remove) {
        
        (*Head)->PrevNode->NextNode = Remove->NextNode; // TODO: 이것도 (*Head)->Next 로 하면 안되나?
        (*Head)->NextNode->PrevNode = Remove->PrevNode; 


        *Head = Remove->NextNode;

        Remove->PrevNode = NULL;
        Remove->NextNode = NULL;

    }else{
        // TODO: 꼭 Temp 를 이용해야하나? 
        Node* Temp = Remove;
        
        Remove->PrevNode->NextNode = Temp->NextNode;    
        Remove->NextNode->PrevNode = Temp->PrevNode;
        
        Remove->PrevNode = NULL;
        Remove->NextNode = NULL;
    }
}

/* 노드 개수 세기 */
int CDLL_GetNodeCount(Node* Head){
    int Count = 0;
    Node* Current = Head;
    
    while (Current != NULL) {
        Current = Current->NextNode;
        Count++;

        if (Current == Head)
        {   
            break;
        }
    }
    
    return Count;
}


void PrintNode(Node* _Node) {
    if (_Node->PrevNode == NULL)
    {
        printf("Prev: NULL");
    }else{
        printf("Prev: %d", _Node->PrevNode->Data);
    }

    printf("Current: %d", _Node->Data);

    if (_Node->NextNode == NULL)
    {
        printf("Next: NULL\n");
    }else{
        printf("Next: %d\n", _Node->NextNode->Data);
    }
}