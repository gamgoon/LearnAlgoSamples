#include "LinkedListStack.h"

void LLS_CreateStack(LinkedListStack** Stack) {

	(*Stack) = (LinkedListStack*)malloc(sizeof(LinkedListStack));
	(*Stack)->List = NULL;
	(*Stack)->Top = NULL;
}

void LLS_DestroyStack(LinkedListStack* Stack) {

	while (!LLS_IsEmpty(Stack)) {

		Node* Popped = LLS_Pop(Stack);
		free(Popped);
	}

	free(Stack);
}

Node* LLS_CreateNode(char* NewData) {

	Node* NewNode = (Node*)malloc(sizeof(Node));
	NewNode->Data = (char*)malloc(strlen(NewData) + 1); // TODO: +1 을 해주는 이유는?

	strcpy(NewNode->Data, NewData);

	NewNode->NextNode = NULL;

	return NewNode;
}

void LLS_DestroyNode(Node* _Node) {

	free(_Node->Data);
	free(_Node);
}

void LLS_Push(LinkedListStack* Stack, Node* NewNode) {

	if (Stack->List == NULL)
	{
		Stack->List = NewNode;
	} else {
		Node* OldTop = Stack->List;
		while (OldTop->NextNode != NULL)
		{
			OldTop = OldTop->NextNode;
		}

		OldTop->NextNode = NewNode;
	}

	Stack->Top = NewNode;
}

Node* LLS_Pop(LinkedListStack* Stack) {

	Node* TopNode = Stack->Top;

	if (Stack->List == Stack->Top)	// Node 가 하나 밖에 없는 경우.
	{
		Stack->List = NULL;
		Stack->Top = NULL;
	} 
	else
	{
		Node* CurrentTop = Stack->List;
		while (CurrentTop != NULL && CurrentTop->NextNode != Stack->Top )
		{
			CurrentTop = CurrentTop->NextNode;
		}

		Stack->Top = CurrentTop;
		CurrentTop->NextNode = NULL;
	}

	return TopNode;
}

Node* LLS_Top(LinkedListStack* Stack) {

	return Stack->Top;
}
int LLS_GetSize(LinkedListStack* Stack) {

	int count = 0;
	Node* Current = Stack->List;

	while (Current != NULL)
	{
		Current = Current->NextNode;
		count++;
	}

	return count;
}

int LLS_IsEmpty(LinkedListStack* Stack) {

	return (Stack->List == NULL);
}