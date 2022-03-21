#pragma once
#include <Vector2.h>
#include "ActorArray.h"

namespace NodeGraph
{
	struct Node;

	struct Edge
	{
		Node* target;
		float cost;
	};

	struct Node
	{
		MathLibrary::Vector2 position;

		float gScore;
		float hScore;
		float fScore;
		bool walkable = true;
		unsigned int color = 0xFFFFFFFFF;

		Node* previous;

		DynamicArray<Edge> edges;
	};

	DynamicArray<Node*> findPath(Node* start, Node* end);

	void drawGraph(Node* start);

	void drawNode(Node* node, float size = 14);

	void drawConnectedNodes(Node* node, DynamicArray<Node*>& drawnList);

	void resetGraphScore(Node* start);
	void resetConnectedNodes(Node* node, DynamicArray<Node*>& resetList);
}