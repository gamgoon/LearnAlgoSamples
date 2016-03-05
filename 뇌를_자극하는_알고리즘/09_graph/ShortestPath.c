#include "ShortestPath.h"

void Dijkstra(Graph* G, Vertex* StartVertex, Graph* ShortestPath)
{
	int i = 0;

	PQNode StartNode = { 0, StartVertex};
	PriorityQueue* PQ = PQ_Create(10);

	Vertex* CurrentVertex = NULL;
	Edge* CurrentEdge = NULL;

	int* Weights = (int*)malloc(sizeof(int) * G->VertexCount);

	Vertex** ShortestPathVertices = (Vertex**)malloc(sizeof(Vertex*) * G->VertexCount);
	Vertex** Fringes = (Vertex**)malloc(sizeof(Vertex*) * G->VertexCount);
	Vertex** Precendences = (Vertex**)malloc(sizeof(Vertex*) * G->VertexCount);

	CurrentVertex = G->Vertices;

	// 모든 정점에 대한 경로길이를 무한대(여기서는 MAX_WEIGHT)로 초기화 
	while (CurrentVertex != NULL)
	{
		Vertex* NewVertex = CreateVertex(CurrentVertex->Data);
		AddVertex(ShortestPath, NewVertex);

		Fringes[i] = NULL;
		Precendences[i] = NULL;
		ShortestPathVertices[i] = NewVertex;
		Weights[i] = MAX_WEIGHT;
		CurrentVertex = CurrentVertex->Next;
		i++;
	}

	PQ_Enqueue(PQ, StartNode);	// 시작 정점을 큐에 넣는다.
	Weights[StartVertex->Index] = 0;	// 시작 정점의 경로 길이는 0

	while (!PQ_IsEmpty(PQ))
	{
		PQNode Popped;

		PQ_Dequeue(PQ, &Popped);
		CurrentVertex = (Vertex*)Popped.Data;

		Fringes[CurrentVertex->Index] = CurrentVertex;

		CurrentEdge = CurrentVertex->AdjacencyList;
		while (CurrentEdge != NULL)
		{
			Vertex* TargetVertex = CurrentEdge->Target;

			if (Fringes[TargetVertex->Index] == NULL && 
				Weights[CurrentVertex->Index] + CurrentEdge->Weight < Weights[TargetVertex->Index])
			{
				PQNode NewNode = { CurrentEdge->Weight, TargetVertex};
				PQ_Enqueue(PQ, NewNode);

				Precendences[TargetVertex->Index] = CurrentEdge->From;
				Weights[TargetVertex->Index] = Weights[CurrentVertex->Index] + CurrentEdge->Weight;
			}

			CurrentEdge = CurrentEdge->Next;
		}
	}

	for (i=0; i<G->VertexCount; i++)
	{
		int FromIndex, ToIndex;

		if (Precendences[i] == NULL)
		{
			continue;
		}

		FromIndex = Precendences[i]->Index;
		ToIndex = i;

		AddEdge(ShortestPathVertices[FromIndex], CreateEdge(ShortestPathVertices[FromIndex],
															ShortestPathVertices[ToIndex],
															Weights[i]));
	}

	free(Fringes);
	free(Precendences);
	free(ShortestPathVertices);
	free(Weights);

	PQ_Destroy(PQ);

}