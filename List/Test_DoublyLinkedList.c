//
//  main.c
//  LearnAlgo
//
//  Created by 감윤욱 on 2016. 1. 21..
//  Copyright © 2016년 감윤욱. All rights reserved.
//

#include <stdio.h>
#include "DoublyLinkedList.h"

int main(int argc, const char * argv[]) {
    int i = 0;
    int Count = 0;
    Node* List = NULL;
    Node* Current = NULL;
    Node* NewNode = NULL;
    
    /* 노드 5개 추가 */
    for (i=0; i<5; i++) {
        NewNode = DLL_CreateNode(i);
        DLL_AppendNode(&List, NewNode);
    }
    
    /* 리스트 출력 */
    Count = DLL_GetNodeCount(List);
    for (i = 0; i<Count; i++) {
        Current = DLL_GetNodeAt(List, i);
        printf("List[%d] : %d\n", i, Current->Data);
    }
    
    /* 리스트의 세번째 노드 뒤에 새 노드 삽입 */
    printf("\nInserting 3000 After [2]...\n\n");
    
    Current = DLL_GetNodeAt(List, 2);
    NewNode = DLL_CreateNode(3000);
    
    DLL_InsertAfter(Current, NewNode);
    
    /* 리스트 출력 */
    Count = DLL_GetNodeCount(List);
    for (i = 0; i<Count; i++) {
        Current = DLL_GetNodeAt(List, i);
        printf("List[%d] : %d\n", i, Current->Data);
    }
    
    /* 모든 노드를 메모리에서 제거 */
    printf("\nDestroying  List...\n");
    
    for (i = 0; i<Count; i++) {
        Current = DLL_GetNodeAt(List, 0);
        
        if (Current != NULL) {
            DLL_RemoveNode(&List, Current);
            DLL_DestroyNode(Current);
        }
    }
    
    return 0;
}

