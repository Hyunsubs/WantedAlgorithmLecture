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

// 노드 색상을 나타내는 열거형.
enum class Color
{
	Red,
	Black
};

// 노드 클래스.
class Node
{
public:

	// 생성자.
	Node(int data = 0, Color color = Color::Red);

	// 소멸자.
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
	// 데이터.
	int data = 0;

	// 색상을 나타내는 변수.
	Color color = Color::Red;

	// 부모 노드.
	Node* parent = nullptr;

	// 왼쪽 자식 노드.
	Node* left = nullptr;

	// 오른쪽 자식 노드.
	Node* right = nullptr;
};

// 노드를 생성하는 데 사용할 함수.
Node* CreateNode(int data = 0, Color color = Color::Red);