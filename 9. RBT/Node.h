#pragma once

#include <iostream>
#include <string>

template<typename T>
void SafeDelete(T*& pointer)
{
	if (pointer != nullptr)
	{
		delete pointer;
		pointer = nullptr;
	}
}

// ��� ������ ��Ÿ���� ������.
enum class Color
{
	Red,
	Black
};

// ��� Ŭ����.
class Node
{
public:

	// ������.
	Node(int data = 0, Color color = Color::Red);

	// �Ҹ���.
	~Node() = default;

	// Getter/Setter.
	const char* ColorString() const;

	const int Data() const;
	void SetData(int newData);

	const Color GetColor() const;
	void SetColor(Color newColor);

	Node* Parent() const;
	void SetParent(Node* newParent);

	Node* Left() const;
	void SetLeft(Node* newLeft);

	Node* Right() const;
	void SetRight(Node* newRight);

private:
	// ������.
	int data = 0;

	// ������ ��Ÿ���� ����.
	Color color = Color::Red;

	// �θ� ���.
	Node* parent = nullptr;

	// ���� �ڽ� ���.
	Node* left = nullptr;

	// ������ �ڽ� ���.
	Node* right = nullptr;
};

// ��带 �����ϴ� �� ����� �Լ�.
Node* CreateNode(int data = 0, Color color = Color::Red);