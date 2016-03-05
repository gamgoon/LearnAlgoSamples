#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

enum VisitMode {Visited, NotVisited};

typedef int ElementType;

typedef struct tagVertex
{
	ElementType 		Data;
	int					Visited;		// 방문 여부
	int 				Index;			// 정점의 인덱스

	struct 	tagVertex* 	Next;			// 다음 정점을 가리키는 포인터.
	struct 	tagEdge*	AdjacencyList;	// 인접 정점의 목록에 대한 포인터. Edge구조체의 Next 포이터를 이용해서 구성.
} Vertex;

typedef struct tagEdge
{
	int 				Weight;			// 간선의 가중치. 최소 신장 트리나 최단 경로 탐색 알고리즘에서 정점 사이의 거리나 비용 등을 표현하기 위해 사용.
	struct 	tagEdge*	Next;			// 다음 간선을 가리키는 포인터.
	Vertex* 			From;			// 시작 정점
	Vertex*				Target;			// 끝 정점
} Edge;

typedef struct tagGraph
{
	Vertex* Vertices;					// 정점 목록
	int		VertexCount;				// 정점의 수
} Graph;

Graph* 	CreateGraph();
void	DestroyGraph(Graph* G);

Vertex*	CreateVertex(ElementType Data);
void	DestroyVertex(Vertex* V);

Edge* 	CreateEdge(Vertex* From, Vertex* Target, int Weight);
void 	DestroyEdge(Edge* E);

void 	AddVertex(Graph* G, Vertex* V);
void 	AddEdge(Vertex* V, Edge* E);
void 	PrintGraph(Graph* G);

#endif