#include "Node.h"

Node::Node(Vector2D _position)
{
    position = _position;
}

Node::~Node()
{
}

int Node::GetDistance(Node* from)
{
    return static_cast<int>(position.Distance(from->position));
}
