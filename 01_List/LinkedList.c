//
//  LinkedList.c
//  LearnAlgo
//
//  Created by gamgoon on 2016. 1. 21..
//  Copyright © 2016년 gamgoon. All rights reserved.
//

#include "LinkedList.h"

/********************************************************
 * 주요 연산
 * 노드 생성/소멸
 * 노드 추가
 * 노드 탐색
 * 노드 삭제
 * 노드 삽입
 *
 * 메모리 영역
 * - static memory (정적 메모리)
 * - automatic memeory (자동 메모리)
 * - free store (자유 저장소)
 * 자유 저장소에 메모리를 할당하려면 malloc() 함수가 필요.
 * void* malloc(size_t size)
 * void* 는 만능 포인터. 즉 어떤 형이라도 가리킬 수 있다.
 * size_t 는 typedef 문으로 unsigned int 의 별칭으로 선언되어 있다.
 * 예제:
 *      Node* NewNode = (Node*)malloc(sizeof(Node));
    
    단점 :
        - 다음 노드를 가리키려는 포인터 때문에 각 노드마다 4byte의 메모리가 추가로 필요.
        - 특정 위치에 있는 노드를 얻는데 드는 비용이 크며 속도도 느림.
          노드의 개수가 n이라면 최악의 경우 n회의 노드 ㅏㅁ색 루프를 실행해야 특정 위치에 있는 노드를 찾을 수 있다.
          반면 배열은 상수 시간에 노드를 얻을 수 있다.
    장점 :
        - 새로운 노드의 추가/삽입/삭제가 쉽고 빠르다. 배열은 요소를 삽입하거나 제거하기가 어렵다.
        - 현재 노드의 다음 노드를 얻어오는 연산에 대해서는 비용이 발생하지 않음. (장정이라고 하기 어렵지만, 단점은 아니기에...)
 
    따라서 : 레코드의 추가/삽입/삭제가 잦고 조회는 드문 곳. 예) 데이터베이스에서 조회해온 레코드를 순차적으로 다루는 데에는 제격.
 ********************************************************/

/* 노드 생성 */
Node* SLL_CreateNode(ElementType NewData)
{
    Node* NewNode = (Node*)malloc(sizeof(Node));
    
    NewNode->Data = NewData;
    NewNode->NextNode = NULL;
    
    return NewNode;
}

/* 노드 소멸 */
/* 노드 소멸은 자유 저장소 세계의 해결사인 free()함수에게 노드가 있는 주소를 일러주면 끝. */
void SLL_DestroyNode(Node* Node)
{
    free(Node);
}

/* 노드 추가 */
/* 사용법
 * Node* List = NULL;
 * Node* NewNode = NULL;
 * NewNode = SLL_CreateNode(117); // 자유 저장소에 노드 생성
 * SLL_AppendNode(&List, NewNode); // 생성한 노드를 List에 추가
 * NewNode = SLL_CreateNode(119);
 * SLL_AppendNode(&List, NewNode);
 *
 * Node** 는 매개변수로 포인터 자신의 주소를 넘길 수 있게 된다.
 */
void SLL_AppendNode(Node** Head, Node* NewNode)
{
    /* 헤드 노드가 NULL이라면 새로운 노드가 Head */
    if ((*Head) == NULL) {
        *Head = NewNode;
    } else {
        /* 테일을 찾아 NewNode를 연결한다. */
        Node* Tail = (*Head);
        while (Tail->NextNode != NULL) {
            Tail = Tail->NextNode;
        }
        
        Tail->NextNode = NewNode;
    }

}

/* 노드 탐색 : 비효율적 구현. 링크드 리스트의 특징(단점) */
/* 사용법
 Node* List = NULL;
 Node* MyNode = NULL;
 
 SLL_AppendNode(&List, SLL_CreateNode(117));
 SLL_AppendNode(&List, SLL_CreateNode(119));
 
 MyNode = SLL_GetNodeAt(List, 1); // 두번째 노드의 주소를 MyNode에 저장
 printf("%d\n", MyNode->Data); // 119 출력
 */
 
Node* SLL_GetNodeAt(Node* Head, int Location)
{
    Node* Current = Head;
    
    while (Current != NULL && (--Location >= 0)) {
        Current = Current->NextNode;
    }
    
    return Current;
}

/* 노드 삭제 */
/* 사용법
 Node* List = NULL;
 Node* MyNode = NULL;
 
 SLL_AppendNode(&List, SLL_CreateNode(117));
 SLL_AppendNode(&List, SLL_CreateNode(119));
 SLL_AppendNode(&List, SLL_CreateNode(212));
 
 MyNode = SLL_GetNodeAt(List, 1); // 두번째 노드의 주소를 MyNode에 저장
 printf("%d\n", MyNode->Data); // 119 출력
 
 SLL_RemoveNode(&List, MyNode);
 SLL_DestroyNode(MyNode); // 메모리 완전히 소멸
 */
void SLL_RemoveNode(Node** Head, Node* Remove)
{
    if (*Head == Remove) {
        *Head = Remove->NextNode;
    }else{
        Node* Current = *Head;
        while (Current != NULL && Current->NextNode != Remove) {
            Current = Current->NextNode;
        }
        
        if (Current != NULL) {
            Current->NextNode = Remove->NextNode;
        }
    }
}

/* 노드 삽입 */
void SLL_InsertAfter(Node* Current, Node* NewNode){
    NewNode->NextNode = Current->NextNode;
    Current->NextNode = NewNode;
}

/* 노드 개수 세기 */
int SLL_GetNodeCount(Node* Head){
    int Count = 0;
    Node* Current = Head;
    
    while (Current != NULL) {
        Current = Current->NextNode;
        Count++;
    }
    
    return Count;
}


void SLL_InsertNewHead(Node** Head, Node* NewNode){
    if (Head == NULL) {
        (*Head) = NewNode;
    } else {
        NewNode->NextNode = (*Head);
        (*Head) = NewNode;  // 왜???
    }
}