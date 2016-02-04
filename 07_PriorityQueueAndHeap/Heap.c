#include "Heap.h"

Heap* HEAP_Create(int InitialSize)
{
	Heap* NewHeap = (Heap*) malloc(sizeof(Heap));
	NewHeap->Capacity = InitialSize;
	NewHeap->UsedSize = 0;
	NewHeap->Nodes = (HeapNode*)malloc(sizeof(HeapNode) * NewHeap->Capacity);

	printf("size : %lu\n", sizeof(HeapNode));

	return NewHeap;
}

void HEAP_Destroy(Heap* H)
{
	free(H->Nodes);
	free(H);
}

void HEAP_Insert(Heap* H, ElementType NewData)
{
	int CurrentPosition = H->UsedSize;
	int ParentPosition = HEAP_GetParent(CurrentPosition);

	if (H->UsedSize == H->Capacity)
	{
		H->Capacity *= 2;
		H->Nodes = (HeapNode*)realloc(H->Nodes, sizeof(HeapNode) * H->Capacity);
	}

	H->Nodes[CurrentPosition].Data = NewData;

	while (CurrentPosition > 0 
		&& H->Nodes[CurrentPosition].Data < H->Nodes[ParentPosition].Data)
	{
		HEAP_SwapNodes(H, CurrentPosition, ParentPosition);

		CurrentPosition = ParentPosition;
		ParentPosition = HEAP_GetParent(CurrentPosition);
	}

	H->UsedSize++;
}

void HEAP_DeleteMin(Heap* H, HeapNode* Root)
{
	int ParentPosition = 0;
	int LeftPosition = 0;
	int RightPosition = 0;

	memcpy(Root, &H->Nodes[0], sizeof(HeapNode)); // Root 에 최소값을 저장한다.
	memset(&H->Nodes[0], 0, sizeof(HeapNode));

	H->UsedSize--;
	HEAP_SwapNodes(H, 0, H->UsedSize); // 힙의 첫 번째 요소에 마지막 요소의 값을 복사한다.

	LeftPosition = HEAP_GetLeftChild(0);
	RightPosition = LeftPosition + 1;

	// 힙순서 속성 만족할 떄까지 자식 노드와의 교환을 반복
	while (1)
	{
		int SelectedChild = 0;

		if (LeftPosition >= H->UsedSize)
		{
			break;
		}

		if (RightPosition >= H->UsedSize)
		{
			SelectedChild = LeftPosition;
		}
		else
		{
			// 자식노드중 작은 것 선택
			if (H->Nodes[LeftPosition].Data > H->Nodes[RightPosition].Data)	
			{
				SelectedChild = RightPosition;
			}
			else
			{
				SelectedChild = LeftPosition;
			}
		}

		// 선택된 작은값의 자식노드와 부모 노드를 비교. 부모노드가 크면 교환
		if (H->Nodes[SelectedChild].Data < H->Nodes[ParentPosition].Data)
		{
			HEAP_SwapNodes(H, ParentPosition, SelectedChild);
			ParentPosition = SelectedChild;
		}
		else
		{
			break;
		}

		LeftPosition = HEAP_GetLeftChild(ParentPosition);
		RightPosition = LeftPosition + 1;

	}
	// 메모리 절약? 현재 사용 공간이 Capacity 의 절반이하이면 배열사이즈 줄임.
	if (H->UsedSize < (H->Capacity / 2))
	{
		H->Capacity /= 2;
		H->Nodes = (HeapNode*)realloc(H->Nodes, sizeof(HeapNode) * H->Capacity);
	}
}

int HEAP_GetParent(int Index)
{
	return (int)((Index - 1) / 2);
}

int HEAP_GetLeftChild(int Index)
{
	return (2 * Index) + 1;
}

void HEAP_SwapNodes(Heap* H, int Index1, int Index2)
{
	int CopySize = sizeof(HeapNode);
	HeapNode* Temp = (HeapNode*)malloc(sizeof(CopySize));

	memcpy(Temp, &H->Nodes[Index1], CopySize);
	memcpy(&H->Nodes[Index1], &H->Nodes[Index2], CopySize);
	memcpy(&H->Nodes[Index2], Temp, CopySize);

	free(Temp);
}
void HEAP_PrintNodes(Heap* H)
{
	int i = 0;
	for (i=0; i<H->UsedSize;i++)
	{
		printf("%d\n", H->Nodes[i].Data);
	}
	printf("\n");
}