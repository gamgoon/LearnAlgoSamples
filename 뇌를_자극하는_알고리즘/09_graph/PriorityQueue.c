#include "PriorityQueue.h"

PriorityQueue* PQ_Create(int InitialSize)
{
	PriorityQueue* NewPQ = (PriorityQueue*) malloc(sizeof(PriorityQueue));
	NewPQ->Capacity = InitialSize;
	NewPQ->UsedSize = 0;
	NewPQ->Nodes = (PQNode*)malloc(sizeof(PQNode) * NewPQ->Capacity);

	printf("size : %lu\n", sizeof(PQNode));

	return NewPQ;
}

void PQ_Destroy(PriorityQueue* PQ)
{
	free(PQ->Nodes);
	free(PQ);
}

void PQ_Enqueue(PriorityQueue* PQ, PQNode NewNode)
{
	int CurrentPosition = PQ->UsedSize;
	int ParentPosition = PQ_GetParent(CurrentPosition);

	if (PQ->UsedSize == PQ->Capacity)
	{
		if (PQ->Capacity == 0)
		{
			PQ->Capacity = 1;
		}
		PQ->Capacity *= 2;
		PQ->Nodes = (PQNode*)realloc(PQ->Nodes, sizeof(PQNode) * PQ->Capacity);
	}

	PQ->Nodes[CurrentPosition] = NewNode;

	while (CurrentPosition > 0 
		&& PQ->Nodes[CurrentPosition].Priority < PQ->Nodes[ParentPosition].Priority)
	{
		PQ_SwapNodes(PQ, CurrentPosition, ParentPosition);

		CurrentPosition = ParentPosition;
		ParentPosition = PQ_GetParent(CurrentPosition);
	}

	PQ->UsedSize++;
}

void PQ_Dequeue(PriorityQueue* PQ, PQNode* Root)
{
	int ParentPosition = 0;
	int LeftPosition = 0;
	int RightPosition = 0;

	memcpy(Root, &PQ->Nodes[0], sizeof(PQNode)); // Root 에 최소값을 저장한다.
	memset(&PQ->Nodes[0], 0, sizeof(PQNode));

	PQ->UsedSize--;
	PQ_SwapNodes(PQ, 0, PQ->UsedSize); // 힙의 첫 번째 요소에 마지막 요소의 값을 복사한다.

	LeftPosition = PQ_GetLeftChild(0);
	RightPosition = LeftPosition + 1;

	// 힙순서 속성 만족할 떄까지 자식 노드와의 교환을 반복
	while (1)
	{
		int SelectedChild = 0;

		if (LeftPosition >= PQ->UsedSize)
		{
			break;
		}

		if (RightPosition >= PQ->UsedSize)
		{
			SelectedChild = LeftPosition;
		}
		else
		{
			// 자식노드중 작은 것 선택
			if (PQ->Nodes[LeftPosition].Priority > PQ->Nodes[RightPosition].Priority)	
			{
				SelectedChild = RightPosition;
			}
			else
			{
				SelectedChild = LeftPosition;
			}
		}

		// 선택된 작은값의 자식노드와 부모 노드를 비교. 부모노드가 크면 교환
		if (PQ->Nodes[SelectedChild].Priority < PQ->Nodes[ParentPosition].Priority)
		{
			PQ_SwapNodes(PQ, ParentPosition, SelectedChild);
			ParentPosition = SelectedChild;
		}
		else
		{
			break;
		}

		LeftPosition = PQ_GetLeftChild(ParentPosition);
		RightPosition = LeftPosition + 1;

	}
	// 메모리 절약? 현재 사용 공간이 Capacity 의 절반이하이면 배열사이즈 줄임.
	if (PQ->UsedSize < (PQ->Capacity / 2))
	{
		PQ->Capacity /= 2;
		PQ->Nodes = (PQNode*)realloc(PQ->Nodes, sizeof(PQNode) * PQ->Capacity);
	}
}

int PQ_GetParent(int Index)
{
	return (int)((Index - 1) / 2);
}
int PQ_GetLeftChild(int Index)
{
	return (2 * Index) + 1;
}
void PQ_SwapNodes(PriorityQueue* PQ, int Index1, int Index2)
{
	int CopySize = sizeof(PQNode);
	PQNode* Temp = (PQNode*)malloc(sizeof(CopySize));

	memcpy(Temp, &PQ->Nodes[Index1], CopySize);
	memcpy(&PQ->Nodes[Index1], &PQ->Nodes[Index2], CopySize);
	memcpy(&PQ->Nodes[Index2], Temp, CopySize);

	free(Temp);
}
//void PQ_PrintNodes(PriorityQueue* PQ);
int PQ_IsEmpty(PriorityQueue* PQ)
{
	return (PQ->UsedSize == 0);
}