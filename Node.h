#pragma once
#include "Vector2D.h"

struct Node
{
	Vector2D position;
	int g, h, f;
	float weight = 1;
	Node* parent;
	Node(Vector2D _position = Vector2D::One);
	~Node();

	float GetDistance(Node* from);
};
