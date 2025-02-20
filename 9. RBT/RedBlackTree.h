#include <iostream>
#include "Node.h"
#include <string>
#include <Windows.h>

class RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();

	// ��带 �˻��ϴ� �Լ�.
	Node* Find(int data);

	// ��� �߰� �Լ� (������ ���).
	bool Insert(int data);

	// ��� ���� �Լ� (������ ���).
	bool Remove(int data);

	// ��� �Լ�.
	void Print(int depth = 0, int blackCount = 0);

private:

	// Ʈ�� ���� �Լ�.
	void DestroyRecursive(Node* node);

	// Ʈ������ �ּ� ���� ���� ��带 �˻��ϴ� �Լ�.
	Node* FindMin();

	// Ʈ������ �ִ� ���� ���� ��带 �˻��ϴ� �Լ�.
	Node* FindMax();

	// ��� �˻� ��� �Լ�.
	Node* FindRecursive(Node* node, int data);

	// �ּҰ� ��� �˻� ��� �Լ�.
	Node* FindMinRecursive(Node* node);

	// �ִ밪 ��� �˻� ��� �Լ�.
	Node* FindMaxRecursive(Node* node);

	// ��� �߰� �Լ� (��� ���).
	void Insert(Node* newNode);

	// Ʈ���� ��带 �߰��ϴ� ��� �Լ�.
	void InsertRecursive(Node* node, Node* newNode);

	// ��� ���� ��� �Լ�.
	void RemoveImpl(Node* node, int data);

	// �� ��带 ������ �Ŀ� Ʈ���� �������ϴ� �Լ�.
	void RestructureAfterInsert(Node* newNode);

	// ��� ���� �� Ʈ���� �������ϴ� �Լ�.
	void RestructureAfterRemove(Node* node);

	// ��ȸ�� �Լ�.
	void LeftRotate(Node* node);

	// ��ȸ�� �Լ�.
	void RightRotate(Node* node);

	// ��� ��� �Լ�.
	void PrintRecursive(Node* node, int depth, int blackCount);

	// ��带 �����ϴ� �� ����� �Լ�.
	Node* CreateNode(int data = 0, Color color = Color::Red);

private:
	Node* root = nullptr;
	static Node* nil;
};

// �ܼ� ���� ������.
enum class TextColor
{
	Red = FOREGROUND_RED,
	Green = FOREGROUND_GREEN,
	Blue = FOREGROUND_BLUE,
	White = Red | Green | Blue,
};

// �ܼ� �ؽ�Ʈ ���� ���� �Լ�.
void SetTextColor(TextColor color);