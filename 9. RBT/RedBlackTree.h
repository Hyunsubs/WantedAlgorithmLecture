#include <iostream>
#include "Node.h"
#include <string>
#include <Windows.h>

class RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();

	// 노드를 검색하는 함수.
	Node* Find(int data);

	// 노드 추가 함수 (데이터 사용).
	bool Insert(int data);

	// 노드 삭제 함수 (데이터 사용).
	bool Remove(int data);

	// 출력 함수.
	void Print(int depth = 0, int blackCount = 0);

private:

	// 트리 삭제 함수.
	void DestroyRecursive(Node* node);

	// 트리에서 최소 값을 가진 노드를 검새하는 함수.
	Node* FindMin();

	// 트리에서 최대 값을 가진 노드를 검새하는 함수.
	Node* FindMax();

	// 노드 검색 재귀 함수.
	Node* FindRecursive(Node* node, int data);

	// 최소값 노드 검색 재귀 함수.
	Node* FindMinRecursive(Node* node);

	// 최대값 노드 검색 재귀 함수.
	Node* FindMaxRecursive(Node* node);

	// 노드 추가 함수 (노드 사용).
	void Insert(Node* newNode);

	// 트리에 노드를 추가하는 재귀 함수.
	void InsertRecursive(Node* node, Node* newNode);

	// 노드 삭제 재귀 함수.
	void RemoveImpl(Node* node, int data);

	// 새 노드를 삽입한 후에 트리를 재정렬하는 함수.
	void RestructureAfterInsert(Node* newNode);

	// 노드 삭제 후 트리를 재정렬하는 함수.
	void RestructureAfterRemove(Node* node);

	// 좌회전 함수.
	void LeftRotate(Node* node);

	// 우회전 함수.
	void RightRotate(Node* node);

	// 출력 재귀 함수.
	void PrintRecursive(Node* node, int depth, int blackCount);

	// 노드를 생성하는 데 사용할 함수.
	Node* CreateNode(int data = 0, Color color = Color::Red);

private:
	Node* root = nullptr;
	static Node* nil;
};

// 콘솔 색상 열거형.
enum class TextColor
{
	Red = FOREGROUND_RED,
	Green = FOREGROUND_GREEN,
	Blue = FOREGROUND_BLUE,
	White = Red | Green | Blue,
};

// 콘솔 텍스트 색상 설정 함수.
void SetTextColor(TextColor color);