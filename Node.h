#pragma once
#include "Vector2D.h"

struct Node
{
	Vector2D position;
	int g, h, f;
	Node* parent;
	Node(Vector2D _position = Vector2D::One);
	~Node();

	int GetDistance(Node* from);
};
