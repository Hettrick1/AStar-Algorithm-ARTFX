#include "Node.h"

Node::Node(Vector2D _position)
{
    position = _position;
}

Node::~Node()
{
}

float Node::GetDistance(Node* from)
{
    return position.Distance(from->position);
}
