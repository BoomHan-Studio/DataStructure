#pragma once
#include "CoreMinimal.h"

/**
 *@brief 图的边
 */
template<typename T>
struct TEdge
{
	using FEdge = TEdge<T>;

	template<typename T1>
	friend struct TGraph;
	
	int16 Dest;
	bool Connection;
	S_PRIVATE(FEdge* link);

	TEdge(uint16 inDest, bool inConnected)
		:Dest(inDest),
		Connection(inConnected),
		link(nullptr)
	{
		
	}

	bool operator !=(const TEdge& another) const noexcept
	{
		return (Dest != another.Dest);
	}
};

/**
 *@brief 图的顶点
 */
template<typename T>
struct TVertex
{
	template<typename T1>
	friend struct TGraph;
	
	T Data;
	TEdge<T>* LinkHead;
	TVertex(const T& inData = T(0), TEdge<T>* inHead = nullptr)
		:Data(inData),
		LinkHead(inHead)
	{
		
	}
};