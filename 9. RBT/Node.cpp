#include "Node.h"

Node* CreateNode(int data, Color color)
{
    return new Node(data, color);
}

Node::Node(int data, Color color)
    : data(data), color(color)
{
}

const char* Node::ColorString() const
{
    return color == Color::Red ? "RED" : "BLACK";
}

const int Node::Data() const
{
    return data;
}

void Node::SetData(int newData)
{
    data = newData;
}

const Color Node::GetColor() const
{
    return color;
}

void Node::SetColor(Color newColor)
{
    color = newColor;
}

Node* Node::Parent() const
{
    return parent;
}

void Node::SetParent(Node* newParent)
{
    parent = newParent;
}

Node* Node::Left() const
{
    return left;
}

void Node::SetLeft(Node* newLeft)
{
    left = newLeft;
}

Node* Node::Right() const
{
    return right;
}

void Node::SetRight(Node* newRight)
{
    right = newRight;
}