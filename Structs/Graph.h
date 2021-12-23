#pragma once
#include "CoreMinimal.h"
#include "GraphComponents.h"
#define GRAPH_DEFAULT_VERTICES 30


template<typename T>
struct TGraph
{
	using FEdge = TEdge<T>;
	using FVertex = TVertex<T>;

	S_PRIVATE(uint16 maxVertices);
	S_PRIVATE(uint16 currentEdges);
	S_PRIVATE(uint16 currentVertices);
	FVertex* NodeTable;

	explicit TGraph(uint16 inSize = GRAPH_DEFAULT_VERTICES)
		:maxVertices(inSize),
		currentVertices(0),
		currentEdges(0),
		NodeTable(new FVertex[maxVertices])
	{
		for (uint16 i = 0; i < maxVertices; i++)
		{
			NodeTable->LinkHead = nullptr;
		}
	}

	~TGraph()
	{
		delete[] NodeTable;
	}

	T Get(int16 inIndex) const
	{
		return (inIndex >= 0 && inIndex < currentVertices ? NodeTable[inIndex].Data : 0);
	}

	bool Connected(int16 inV1, int16 inV2)
	{
		if (inV1 != -1 && inV2 != -1)
		{
			FEdge*temp = NodeTable[inV1].LinkHead;
			while (temp && temp->Dest != inV2)
			{
				temp = temp->link;
			}
			if (temp)
			{
				return temp->Connection;
			}
		}
		return false;
	}

	void InsertVertex(const T& inVertex)
	{
		if (currentVertices == maxVertices) return;
		NodeTable[currentVertices].Data = inVertex;
		currentVertices++;
	}

	template<typename ... Ts>
	void InsertVertex(const T& inVertex, const Ts& ... inVertexs)
	{
		InsertVertex(inVertex);
		InsertVertex(T(inVertexs) ...);
	}

	/*void RemoveVertex(int16 inV)
	{
		if (currentVertices == 1) return;
		//FEdge*
	}*/

	void InsertEdge(uint16 inFrom, uint16 inTo, bool inConnection, bool& outInsertSuccess)
	{
		outInsertSuccess = false;
		using FEdgePtr = FEdge*;
		auto isBetween = [](uint16 inX, uint16 inMin, uint16 inMax)->bool {return inX >= inMin && inX < inMax;};
		if (!(isBetween(inFrom, 0, currentVertices) && isBetween(inTo, 0, currentVertices)))
		{
			return;
		}
		FEdgePtr edgeP = NodeTable[inFrom].LinkHead;
		FEdgePtr edgeQ;
		while (edgeP && edgeP->Dest != inTo)
		{
			edgeP = edgeP->link;
		}
		if (edgeP)
		{
			return;
		}
		edgeP = new FEdge(inTo, inConnection);
		edgeP->link = (NodeTable[inFrom].LinkHead = edgeP);
		edgeQ = new FEdge(inFrom, inConnection);
		edgeQ->link = (NodeTable[inTo].LinkHead = edgeQ);
		currentEdges++;
		outInsertSuccess = true;
	}

	/*void RemoveEdge(int16 inV1, int16 inV2)
	{
		
	}*/

	int16 FirstNeighbor(int16 inV)
	{
		if (inV != -1)
		{
			const FEdge* temp = NodeTable[inV].LinkHead;
			if (temp)
			{
				return temp->Dest;
			}
		}
		return -1;
	}

	int16 NextNeighbor(int16 inV, int16 inW)
	{
		if (inV != -1)
		{
			FEdge* temp = NodeTable[inV].LinkHead;
			while (temp && temp->Dest != inW)
			{
				temp = temp->link;
			}
			if (temp && temp->link)
			{
				return temp->link->Dest;
			}
		}
		return -1;
	}

	template<typename FunctionType>
	void ForEach_DFS(const T& inVertex, FunctionType inFunction)
	{
		uint16 vertices = currentVertices;
		bool* visited = new bool[vertices]{false};
		const int16 position = GetVertexPosition(inVertex);
		ForEach_DFS(position, visited, inFunction);
		delete[] visited;
	}

private:

	template<typename FunctionType>
	void ForEach_DFS(int16 inV, bool* inVisitArray, FunctionType inFunction)
	{
		if (inV == -1) return;
		inFunction(Get(inV));
		inVisitArray[inV] = true;
		int16 firstNeighbor = FirstNeighbor(inV);
		while (firstNeighbor != -1)
		{
			if (!inVisitArray[firstNeighbor])
			{
				ForEach_DFS(firstNeighbor, inVisitArray, inFunction);
			}
			firstNeighbor = NextNeighbor(inV, firstNeighbor);
		}
	}

	int16 GetVertexPosition(const T& inVertex)
	{
		for (int16 i = 0; i < currentVertices; i++)
		{
			if (NodeTable[i].Data == inVertex) return i;
		}
		return -1;
	}
};

#include "Graph.inl"