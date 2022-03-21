#include "NodeGraph.h"
#include <raylib.h>
#include <xlocinfo>

DynamicArray<NodeGraph::Node*> reconstructPath(NodeGraph::Node* start, NodeGraph::Node* end)
{
	DynamicArray<NodeGraph::Node*> path;
	NodeGraph::Node* currentNode = end;

	while (currentNode != start->previous)
	{
		currentNode->color = 0xFFFF00FF;
		path.insert(currentNode, 0);
		currentNode = currentNode->previous;
	}

	return path;
}

float diagonalDistance(NodeGraph::Node* node, NodeGraph::Node* goal, float cardinalCost, float diagonalCost)
{
	float displacementX = abs(node->position.x - goal->position.x);
	float displacementY = abs(node->position.y - goal->position.y);

	return cardinalCost * (displacementX + displacementY) + (diagonalCost - 2 * cardinalCost) * fmin(displacementX, displacementY);
}

void sortFScore(DynamicArray<NodeGraph::Node*>& nodes)
{
	NodeGraph::Node* key = nullptr;
	int j = 0;

	for (int i = 1; i < nodes.getLength(); i++) {
		key = nodes[i];
		j = i - 1;
		while (j >= 0 && nodes[j]->fScore > key->fScore) {
			nodes[j + 1] = nodes[j];
			j--;
		}

		nodes[j + 1] = key;
	}
}

void sortGScore(DynamicArray<NodeGraph::Node*>& nodes)
{
	NodeGraph::Node* key = nullptr;
	int j = 0;

	for (int i = 1; i < nodes.getLength(); i++) {
		key = nodes[i];
		j = i - 1;
		while (j >= 0 && nodes[j]->gScore > key->gScore) {
			nodes[j + 1] = nodes[j];
			j--;
		}
		nodes[j + 1] = key;
	}
}


DynamicArray<NodeGraph::Node*> NodeGraph::findPath(Node* start, Node* goal)
{
	//Creats a List for the currently list being identified
	DynamicArray<NodeGraph::Node*> openList;
	//The Nodes that have already been identified and been processed 
	DynamicArray<NodeGraph::Node*> closedList;

	resetGraphScore(start);
	

	//Sets the current node to be the first node in the open list 
	/*NodeGraph::Node* currentNode = start;*/

	//adds start to the open list
	openList.addItem(start);

	//While the open list has a node . . . 
	while (openList.getLength() > 0) {

		////Sorts the open List based Off the Nodes G - Score
		//sortGScore(openList);

		//Sorts The Open List Based OFf the Nodes F - Score
		sortFScore(openList);

		NodeGraph::Node* currentNode = openList[0];
		
		float gScore = currentNode->gScore;

		//Removes the node thats currently being processed from the open list
		openList.remove(currentNode);

		if (!closedList.contains(currentNode))
		{//Adds that current node to the closed list 
			closedList.addItem(currentNode);

			//Itarates through the nodes on the edges of the current node 
			for (int i = 0; i < currentNode->edges.getLength(); i++)
			{
				//Current target being Looked At 
				Node* currentTarget = currentNode->edges[i].target;

				//Callcualtes edges the G Score by ading the edges cost and the currentNodes g Score  
				currentTarget->gScore = currentNode->edges[i].cost + currentNode->gScore;
				
				//Calculates the h Score by getting the manhattan distance of the current edge and the goal 
				currentTarget->hScore = abs(currentTarget->position.x - goal->position.x) + abs(currentTarget->position.y - goal->position.y);

				//Calculates the f score by adding the g Score and the h Score together 
				currentTarget->fScore = currentTarget->gScore + currentTarget->hScore;

				//If the node on the edge already exists in the closed
				if (!closedList.contains(currentTarget))
				{
					//sets this target edge to be the current node 
					currentTarget->previous = currentNode;
					//Sets the hex color value to be that of (RED)
					currentTarget->color = 0xFB0F0FFF;
				}
				else
					// Skips any node thats has already been calculated
					continue;

				//Addeds the current edge target
				openList.addItem(currentTarget);
			}
		}
		//If the current Node is that of the goal 
		if (currentNode == goal)
			//Just return the reconstructed path
			return reconstructPath(start, goal);
	}

	//Retruns What Happens in the Reconstruction path function 
	return reconstructPath(start, goal);
}

void NodeGraph::drawGraph(Node* start)
{
	DynamicArray<Node*> drawnList = DynamicArray<Node*>();
	drawConnectedNodes(start, drawnList);
}

void NodeGraph::drawNode(Node* node, float size)
{
	static char buffer[10];
	sprintf_s(buffer, "%.0f", node->gScore);

	//Draw the circle for the outline
	DrawCircle((int)node->position.x, (int)node->position.y, size + 1, GetColor(node->color));
	//Draw the inner circle
	DrawCircle((int)node->position.x, (int)node->position.y, size, GetColor(node->color));
	//Draw the text
	DrawText(buffer, (int)node->position.x, (int)node->position.y, .8f, BLACK);
}

void NodeGraph::drawConnectedNodes(Node* node, DynamicArray<Node*>& drawnList)
{
	drawnList.addItem(node);
	if (node->walkable)
		drawNode(node, 8);

	for (int i = 0; i < node->edges.getLength(); i++)
	{
		Edge e = node->edges[i];
		////Draw the Edge
		//DrawLine((int)node->position.x, (int)node->position.y, (int)e.target->position.x, (int)e.target->position.y, WHITE);
		////Draw the cost
		//MathLibrary::Vector2 costPos = { (node->position.x + e.target->position.x) / 2, (node->position.y + e.target->position.y) / 2 };
		//static char buffer[10];
		//sprintf_s(buffer, "%.0f", e.cost);
		//DrawText(buffer, (int)costPos.x, (int)costPos.y, 16, RAYWHITE);
		//Draw the target node
		if (!drawnList.contains(e.target)) {
			drawConnectedNodes(e.target, drawnList);
		}
	}
}

void NodeGraph::resetGraphScore(Node * start)
{
	DynamicArray<Node*> resetList = DynamicArray<Node*>();
	resetConnectedNodes(start, resetList);
}

void NodeGraph::resetConnectedNodes(Node* node, DynamicArray<Node*>& resetList)
{
	resetList.addItem(node);

	for (int i = 0; i < node->edges.getLength(); i++)
	{
		node->edges[i].target->gScore = 0;
		node->edges[i].target->hScore = 0;
		node->edges[i].target->fScore = 0;
		node->edges[i].target->color = 0xFFFFFFFF;

		//Draw the target node
		if (!resetList.contains(node->edges[i].target)) {
			resetConnectedNodes(node->edges[i].target, resetList);
		}
	}
}