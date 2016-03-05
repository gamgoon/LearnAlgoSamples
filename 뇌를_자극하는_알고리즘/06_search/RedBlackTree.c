#include "RedBlackTree.h"

extern RBTNode* Nil;

RBTNode* RBT_CreateNode(ElementType NewData)
{
	RBTNode* NewNode = (RBTNode*)malloc(sizeof(RBTNode));
	NewNode->Parent = NULL;
	NewNode->Left = NULL;
	NewNode->Right = NULL;
	NewNode->Data = NewData;
	NewNode->Color = BLACK;

	return NewNode;
}


void RBT_DestroyNode(RBTNode* Node)
{
	free(Node);
}

void RBT_DestroyTree(RBTNode* Tree)
{
	if (Tree->Right != Nil)
	{
		RBT_DestroyTree(Tree->Right);
	}
	if (Tree->Left != Nil)
	{
		RBT_DestroyTree(Tree->Left);
	}
	Tree->Left = Nil;
	Tree->Right = Nil;
	RBT_DestroyNode(Tree);
}

RBTNode* RBT_SearchNode(RBTNode* Tree, ElementType Target)
{
	if (Tree == Nil)
	{
		return NULL;
	}

	if (Tree->Data > Target)
	{
		return RBT_SearchNode(Tree->Left, Target);
	}
	else if (Tree->Data < Target)
	{
		return RBT_SearchNode(Tree->Right, Target);
	}
	else
	{
		return Tree;
	}
}

RBTNode* RBT_SearchMinNode(RBTNode* Tree)
{
	if (Tree == Nil)
	{
		return Nil;
	}

	if (Tree->Left == Nil)
	{
		return Tree;
	}
	else
	{
		return RBT_SearchMinNode(Tree->Left);
	}
}

void RBT_InsertNode(RBTNode** Tree, RBTNode* NewNode)
{
	RBT_InsertNodeHelper(Tree, NewNode);

	NewNode->Color = RED;
	NewNode->Left = Nil;
	NewNode->Right = Nil;

	RBT_RebuildAfterInsert(Tree, NewNode);
}
void RBT_InsertNodeHelper(RBTNode** Tree, RBTNode* NewNode)
{
	if ((*Tree) == NULL)
	{
		(*Tree) = NewNode;
	}

	if ((*Tree)->Data < NewNode->Data)
	{
		if ((*Tree)->Right == Nil)
		{
			(*Tree)->Right = NewNode;
			NewNode->Parent = (*Tree);
		}
		else
		{
			RBT_InsertNodeHelper(&(*Tree)->Right , NewNode);
		}
	}
	else if ((*Tree)->Data > NewNode->Data)
	{
		if ((*Tree)->Left == Nil)
		{
			(*Tree)->Left = NewNode;
			NewNode->Parent = (*Tree);
		}
		else
		{
			RBT_InsertNodeHelper(&(*Tree)->Left, NewNode);
		}
	}
}

RBTNode* RBT_RemoveNode(RBTNode** Root, ElementType Data)
{
	RBTNode* Removed = NULL;
	RBTNode* Successor = NULL;
	RBTNode* Target = RBT_SearchNode((*Root), Data); // 삭제 대상 노드

	if (Target == NULL)
	{
		return NULL;
	}

	if (Target->Left == Nil || Target->Right == Nil)
	{
		Removed = Target;
	}
	else
	{
		// 삭제 대상 노드의 자식 노드가 있는 경우는 오른쪽 자식 트리중 자강 작은 값의 노드를 삭제된 노드에 옮긴다.
		Removed = RBT_SearchMinNode(Target->Right);
		Target->Data = Removed->Data;
	}

	if (Removed->Left != Nil)
	{
		printf("이건 찍히면 안되는건가....\n" );
		Successor = Removed->Left;
	}
	else
	{
		printf("이것만 찍혀야 하나....\n" );
		Successor = Removed->Right;
	}

	Successor->Parent = Removed->Parent;

	if (Removed->Parent == NULL)
	{
		(*Root) = Successor;
	}
	else
	{
		if (Removed == Removed->Parent->Left)
		{
			Removed->Parent->Left = Successor;
		}
		else
		{
			Removed->Parent->Right = Successor;
		}
	}

	if (Removed->Color == BLACK)
	{
		RBT_RebuildAfterRemove(Root, Successor);
	}

	return Removed;
}

void RBT_RebuildAfterInsert(RBTNode** Root, RBTNode* X)
{
	while (X != (*Root) && X->Parent->Color == RED)
	{
		if (X->Parent == X->Parent->Parent->Left) // rotate 방향 기준
		{
			RBTNode* Uncle = X->Parent->Parent->Right;
			if (Uncle->Color == RED)
			{
				X->Parent->Color = BLACK;
				Uncle->Color = BLACK;
				X->Parent->Parent->Color = RED;

				X = X->Parent->Parent;
			}
			else
			{
				if (X == X->Parent->Right) // 삼촌이 검은색이고 X 가 오른쪽 자식일떄
				{
					X = X->Parent;	// 회전 노드를 부모로 바꾸고
					RBT_RotateLeft(Root, X); // 회전 시킨다. 회전 시키고 나면 X 는 부모의 왼쪽 자식이 된다.
				}

				// 현재는 X 즉 새로 삽입한 노드가 부모의 왼쪽이다.
				X->Parent->Color = BLACK;
				X->Parent->Parent->Color = RED;

				RBT_RotateRight(Root, X->Parent->Parent);
			}
		}
		else
		{
			// 회전 방향과 기준이 되는 자식의 위치(왼쪽,오른쪽) 만 다르다.
			RBTNode* Uncle = X->Parent->Parent->Left;
			if (Uncle->Color == RED)
			{
				X->Parent->Color = BLACK;
				Uncle->Color = BLACK;
				X->Parent->Parent->Color = RED;

				X = X->Parent->Parent;
			}
			else
			{
				if (X == X->Parent->Left)
				{
					X = X->Parent;	
					RBT_RotateRight(Root, X); 
				}

				X->Parent->Color = BLACK;
				X->Parent->Parent->Color = RED;

				RBT_RotateLeft(Root, X->Parent->Parent);
			}
		}
	}
}
void RBT_RebuildAfterRemove(RBTNode** Root, RBTNode* Successor)
{
	RBTNode* Sibling = NULL;

	while (Successor->Parent != NULL && Successor->Color == BLACK)
	{
		if (Successor == Successor->Parent->Left)
		{
			Sibling = Successor->Parent->Right;

			if (Sibling->Color == RED) // 형제가 빨간색이면
			{
				Sibling->Color = BLACK; // 형제를 검은색으로 바꾸고
				Successor->Parent->Color = RED; // 부모를 빨간색으로 바꾼다.
				RBT_RotateLeft(Root, Successor->Parent); // 부모 기준으로 좌회전
				Sibling = Successor->Parent->Right; // 현재가 이젠 검은색이 되었다
			}
			else
			{ 	// 형제의 색이 검은색이면

				if (Sibling->Left->Color == BLACK &&
					Sibling->Right->Color == BLACK)
				{
					// 형제의 양쪽 자식이 모두 검은색인 경우
					// 형제를 빨간색으로 바꾸고, Successor의 부모를 Successor로 바꾼다.  
					Sibling->Color = RED;
					Successor = Successor->Parent;
				}
				else
				{
					if (Sibling->Left->Color == RED)
					{
						Sibling->Left->Color = BLACK;
						Sibling->Color = RED;

						RBT_RotateRight(Root, Sibling);
						Sibling = Successor->Parent->Right; // 결국 형제의 오른쪽 자식이 빨간색인 상태로 바뀐 상황
					}

					Sibling->Color = Successor->Parent->Color;
					Successor->Parent->Color = BLACK;
					Sibling->Right->Color = BLACK;
					RBT_RotateLeft(Root, Successor->Parent);
					Successor = (*Root);

				}
			}
		}
		else
		{
			Sibling = Successor->Parent->Left;

			if (Sibling->Color == RED) // 형제가 빨간색이면
			{
				Sibling->Color = BLACK; // 형제를 검은색으로 바꾸고
				Successor->Parent->Color = RED; // 부모를 빨간색으로 바꾼다.
				RBT_RotateRight(Root, Successor->Parent); 
				Sibling = Successor->Parent->Left; 
			}
			else
			{ 	// 형제의 색이 검은색이면

				if (Sibling->Right->Color == BLACK &&
					Sibling->Left->Color == BLACK)
				{
					// 형제의 양쪽 자식이 모두 검은색인 경우
					// 형제를 빨간색으로 바꾸고, Successor의 부모를 Successor로 바꾼다.  
					Sibling->Color = RED;
					Successor = Successor->Parent;
				}
				else
				{
					if (Sibling->Right->Color == RED)
					{
						Sibling->Right->Color = BLACK;
						Sibling->Color = RED;

						RBT_RotateLeft(Root, Sibling);
						Sibling = Successor->Parent->Left; // 결국 형제의 오른쪽 자식이 빨간색인 상태로 바뀐 상황
					}

					Sibling->Color = Successor->Parent->Color;
					Successor->Parent->Color = BLACK;
					Sibling->Left->Color = BLACK;
					RBT_RotateRight(Root, Successor->Parent);
					Successor = (*Root);

				}
			}
		}
	}

	Successor->Color = BLACK;
}

void RBT_PrintTree(RBTNode* Node, int Depth, int BlackCount)
{
	int i = 0;
	char c = 'X';
	int v = -1;
	char cnt[100];

	if (Node == NULL || Node == Nil)
	{
		return;
	}

	if (Node->Color == BLACK)
	{
		BlackCount++;
	}

	if (Node->Parent != NULL)
	{
		v = Node->Parent->Data;

		if (Node->Parent->Left == Node)
		{
			c = 'L';
		}
		else
		{
			c = 'R';
		}
	}

	if (Node->Left == Nil && Node->Right == Nil)
	{
		sprintf(cnt, "------- %d", BlackCount);
	}
	else
	{
		sprintf(cnt, "");
	}

	for ( i = 0; i < Depth; i++)
	{
		printf("  ");
	}

	printf("%d %s [%c, %d] %s\n", Node->Data,
		(Node->Color == RED)?"RED":"BLACK", c, v, cnt);

	RBT_PrintTree(Node->Left, Depth+1, BlackCount);
	RBT_PrintTree(Node->Right, Depth+1, BlackCount);
}
void RBT_RotateLeft(RBTNode** Root, RBTNode* Parent)
{
	RBTNode* RightChild = Parent->Right;

	Parent->Right = RightChild->Left;

	if (RightChild->Left != Nil)
	{
		RightChild->Left->Parent = Parent;
	}

	RightChild->Parent = Parent->Parent;

	if (Parent->Parent == NULL)
	{
		(*Root) = RightChild;
	}
	else
	{
		if (Parent == Parent->Parent->Left)
		{
			Parent->Parent->Left = RightChild;
		}
		else
		{
			Parent->Parent->Right = RightChild;
		}
	}

	RightChild->Left = Parent;
	Parent->Parent = RightChild;
}
void RBT_RotateRight(RBTNode** Root, RBTNode* Parent)
{
	RBTNode* LeftChild = Parent->Left;

	Parent->Left = LeftChild->Right;

	if (LeftChild->Right != Nil)
	{
		LeftChild->Right->Parent = Parent;
	}

	LeftChild->Parent = Parent->Parent;

	if (Parent->Parent == NULL)
	{
		(*Root) = LeftChild;
	}
	else
	{
		if (Parent == Parent->Parent->Left)
		{
			Parent->Parent->Left = LeftChild;
		}
		else
		{
			Parent->Parent->Right = LeftChild;
		}
	}

	LeftChild->Left = Parent;
	Parent->Parent = LeftChild;
}