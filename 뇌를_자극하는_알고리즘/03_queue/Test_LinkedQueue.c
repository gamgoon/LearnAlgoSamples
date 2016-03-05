#include "LinkedQueue.h"

int main(void)
{
	Node* Popped;
	LinkedQueue* Queue;

	LQ_CreateQueue(&Queue);

	LQ_Enqueue(Queue, LQ_CreateNode("abc"));
	LQ_Enqueue(Queue, LQ_CreateNode("def"));
	LQ_Enqueue(Queue, LQ_CreateNode("efg"));
	LQ_Enqueue(Queue, LQ_CreateNode("hij"));

	printf("Queue Size : %d\n", Queue->Count);

	int c = 1;
	while (LQ_IsEmpty(Queue) == 0)
	{
		printf("%d\n", c);
		Popped = LQ_Dequeue(Queue);

		printf("Dequeue: %s \n", Popped->Data);

		LQ_DestroyNode(Popped);
		c++;
	}

	LQ_DestroyQueue(Queue);

	return 0;
}