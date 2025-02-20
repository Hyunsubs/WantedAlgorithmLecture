#include "RedBlackTree.h"
#include <Windows.h>

Node* RedBlackTree::nil = nullptr;

Node* RedBlackTree::CreateNode(int data, Color color)
{
	Node* newNode = new Node(data, color);
	newNode->SetParent(nullptr);
	newNode->SetLeft(nil);
	newNode->SetRight(nil);

	return newNode;
}

RedBlackTree::RedBlackTree()
{
	if (nil == nullptr)
	{
		nil = CreateNode(0, Color::Black);
	}

	root = nil;
}

RedBlackTree::~RedBlackTree()
{
	DestroyRecursive(root);
	SafeDelete(nil);
}

Node* RedBlackTree::Find(int data)
{
	// Ʈ���� ��� �ִٸ�, nullptr ��ȯ.
	if (root == nil)
	{
		return nullptr;
	}

	// ��Ʈ�������� ��� ������ �˻�.
	return FindRecursive(root, data);
}

bool RedBlackTree::Insert(int data)
{
	// �߰��� �����Ͱ� �̹� Ʈ���� ������ ����.
	if (Find(data))
	{
		std::cout << "���� - ��� �߰� ����: �̹� ���� ���� Ʈ���� �ֽ��ϴ�. �Է°�: " << data << "\n";
		return false;
	}

	// Ʈ���� �� ��� �߰�.
	Insert(CreateNode(data));
	return true;
}

bool RedBlackTree::Remove(int data)
{
	// ������ ��� �˻��� ���������� ���� ����.
	if (Find(data) == nullptr)
	{
		std::cout << "���� - ��� ���� ����: ������ ��带 ã�� ���߽��ϴ�. (�˻� ��: " << data << ")\n";
		return false;
	}

	RemoveImpl(root, data);
	return true;
}

void RedBlackTree::Print(int depth, int blackCount)
{
	PrintRecursive(root, depth, blackCount);
}

void RedBlackTree::DestroyRecursive(Node* node)
{
	// ��� �Լ� Ż�� ����.
	if (node == nil)
	{
		return;
	}

	// ����/������ �ڽ� ���.
	Node* left = node->Left();
	Node* right = node->Right();

	// �ڽ� ��尡 ���� ��쿡�� ��� ����.
	if (left == nil && right == nil)
	{
		SafeDelete(node);
		return;
	}

	// �ڽ��� �ִ� ��쿡�� ��������� ���� ����.
	DestroyRecursive(left);
	DestroyRecursive(right);

	// ��� ����.
	SafeDelete(node);
}

Node* RedBlackTree::FindMin()
{
	// ��������� �ּҰ� ��� �˻�.
	return FindMinRecursive(root);
}

Node* RedBlackTree::FindMax()
{
	// ��������� �ִ밪 ��� �˻�.
	return FindMaxRecursive(root);
}

Node* RedBlackTree::FindRecursive(Node* node, int data)
{
	// ��� �Լ� Ż�� ���� (�˻��� �����ϸ� nullptr ��ȯ).
	if (node == nil)
	{
		return nullptr;
	}

	// ã�� ��� ���� ��� ��ȯ
	if (node->Data() == data)
	{
		return node;
	}

	// �˻��� �����Ͱ� ���� ��� �� ���� ������ �������� �˻� ����.
	if (node->Data() > data)
	{
		return FindRecursive(node->Left(), data);
	}

	// �˻��� �����Ͱ� ���� ��� �� ���� ũ�� �������� �˻� ����.
	else
	{
		return FindRecursive(node->Right(), data);
	}
}

Node* RedBlackTree::FindMinRecursive(Node* node)
{
	// ��� �Լ� Ż�� ����.
	if (node == nil)
	{
		return nullptr;
	}

	// ���� ���� ��尡 �� �̻� ������ ���� ��尡 �ּҰ�.
	if (node->Left() == nil)
	{
		return node;
	}

	return FindMinRecursive(node->Left());
}

Node* RedBlackTree::FindMaxRecursive(Node* node)
{
	// ��� �Լ� Ż�� ����.
	if (node == nil)
	{
		return nullptr;
	}

	// ���� ���� ��尡 �� �̻� ������ ���� ��尡 �ִ밪.
	if (node->Right() == nil)
	{
		return node;
	}

	return FindMaxRecursive(node->Right());
}

void RedBlackTree::Insert(Node* newNode)
{
	// Ʈ���� ��� �ִ� ���, �� ��带 ��Ʈ�� ���� �� ����.
	if (root == nil)
	{
		root = newNode;
		root->SetColor(Color::Black);
		return;
	}

	// Ʈ���� ��� ���� ���� ��쿡��, ��������� Ʈ���� ��� ����.
	InsertRecursive(root, newNode);

	// ������ �� ����� ���� �� �ڽ� ��� ����.
	newNode->SetColor(Color::Red);
	newNode->SetLeft(nil);
	newNode->SetRight(nil);

	// ���� �� ������ ����.
	RestructureAfterInsert(newNode);
}

void RedBlackTree::InsertRecursive(Node* node, Node* newNode)
{
	// �� ����� �����Ͱ� ���� ��庸�� ������, ���� ���� Ʈ���� ���� ����.
	if (node->Data() > newNode->Data())
	{
		// ���� ���� ��尡 �������, �� ��� ����.
		if (node->Left() == nil)
		{
			node->SetLeft(newNode);
			newNode->SetParent(node);
		}

		// ��� ���� �ʴٸ�, ���� ���� Ʈ���� ������ ���� �˻� ����.
		else
		{
			InsertRecursive(node->Left(), newNode);
		}
	}

	// �� ����� �����Ͱ� ���� ��庸�� ũ��, ������ ���� Ʈ���� ���� ����.
	else
	{
		// ������ ���� ��尡 �������, �� ��� ����.
		if (node->Right() == nil)
		{
			node->SetRight(newNode);
			newNode->SetParent(node);
		}

		// ��� ���� �ʴٸ�, ������ ���� Ʈ���� ������ ���� �˻� ����.
		else
		{
			InsertRecursive(node->Right(), newNode);
		}
	}
}

void RedBlackTree::RemoveImpl(Node* node, int data)
{
	Node* removed = nullptr;
	Node* trail = nullptr;
	Node* target = FindRecursive(node, data);

	// ������ ��忡 �ڼ��� ���� ��� ������ ��� ����.
	if (target->Left() == nil || target->Right() == nil)
	{
		removed = target;

		// ������ ��尡 nil�̶�� �Լ� ����(���� ó��).
		if (removed == nil)
		{
			return;
		}
	}

	// �ڼ��� �ִ� ��쿡�� ���� Ž�� Ʈ���� ������ ������Ű�� ���� ��� ��ġ ����.
	else
	{
		// ���� ���� ��忡�� ���� ū ���� ������ ��� ��ġ�� ����.
		removed = FindMaxRecursive(target->Left());

		// ��ü ��尡 �����ϸ�, �ش� �����͸� ����.
		if (removed != nullptr && removed != nil)
		{
			// ��ü ����� �� ����.
			target->SetData(removed->Data());
		}
	}

	// removed�� null�̸� �ȵǱ� ������ ���� ó��.
	if (removed == nullptr || removed == nil)
	{
		return;
	}

	// removed�� �ڽ� ��尡 �ϳ��� �ִ� ���, �ڽ��� trail�� ����.
	// �� �� removed�� ���� ���(�ڼ��� ��� nil)��� trail�� nil ��尡 ��.
	if (removed->Left() != nil)
	{
		trail = removed->Left();
	}
	else
	{
		trail = removed->Right();
	}

	// removed�� �θ�� trail�� ������ removed ��带 ������ �غ�.
	trail->SetParent(removed->Parent());

	// removed�� ��Ʈ ����� ���, trail�� ��Ʈ�� ����.
	if (removed->Parent() == nullptr)
	{
		root = trail;
	}

	// ��Ʈ ��尡 �ƴ� ���.
	else
	{
		// trail ��带 removed�� ���� ��ġ�� ����.
		if (removed == removed->Parent()->Left())
		{
			removed->Parent()->SetLeft(trail);
		}
		else
		{
			removed->Parent()->SetRight(trail);
		}
	}

	// ���� �� Ʈ���� ��Ģ�� �����ϱ� ���� ������ ����.
	// �̶� ������ ��尡 �������� ��쿡�� �ʿ����� �ʰ�, �������� ��쿡�� ����.
	if (removed->GetColor() == Color::Black && trail != nil)
	{
		// ������ ����
		RestructureAfterRemove(trail);
	}

	// ������ ��� ����.
	SafeDelete(removed);
}

void RedBlackTree::RestructureAfterInsert(Node* newNode)
{
	// �θ� ��尡 �������� ��쿡�� 
	// ������ ��尡 �������� ���� �� ���ٴ� ������ 
	// �������� �ʱ� ������ �̸� �ذ��ϱ� ���� ������ ����(Case2: Red-Red Conflict).
	while (newNode != root && newNode->Parent()->GetColor() == Color::Red)
	{
		// �ذ� ��� (������ �������� ���/������ �������� ���).
		// ���� ���ϱ� #1: �� ����� �θ� ���θ��� ���� �ڼ��� ���.
		if (newNode->Parent() == newNode->Parent()->Parent()->Left())
		{
			// ����.
			Node* uncle = newNode->Parent()->Parent()->Right();

			// ���� ��尡 �������� ��.
			// �ذ�: �θ�� ������ ���������� �����ϰ�, ���θ� ���������� �����ؼ�
			// ������ ���� �ø���.
			if (uncle->GetColor() == Color::Red)
			{
				newNode->Parent()->SetColor(Color::Black);
				uncle->SetColor(Color::Black);
				newNode->Parent()->Parent()->SetColor(Color::Red);

				// ������ ������ �ڿ� ���� ��忡���� ���� ������ �߻������� �ʴ��� Ȯ��.
				newNode = newNode->Parent()->Parent();
				continue;
			}
			// ���� ��尡 �������� ��.
			// �ذ�: �θ�, ���θ�, �� ����� ��ġ�� ���� ȸ���� ����.
			// #1: �� ��尡 �θ�� �ݴ� ��ġ�� �� -> �θ� �߽����� 1�� ȸ�� �� �ٽ� ȸ��.
			// #2: �� ��尡 �θ�� ���� ��ġ�� �� -> ȸ�� �� ���� �缳���� ���� ��ġ ������.
			else
			{
				// �θ�� �ݴ� ��ġ�� ��� (�߰� ȸ��).
				// �θ�� �� ����� ��ġ�� ���߱� ����.
				if (newNode == newNode->Parent()->Right())
				{
					// �θ� �߽����� ȸ�� ����.
					newNode = newNode->Parent();
					LeftRotate(newNode);
				}

				// ���θ� �߽����� ȸ�� �� ���� ����.
				newNode->Parent()->SetColor(Color::Black);
				newNode->Parent()->Parent()->SetColor(Color::Red);

				RightRotate(newNode->Parent()->Parent());
			}
		}

		// ���� ���ϱ� #2: �� ����� �θ� ���θ��� ������ �ڼ��� ���.
		else
		{
			// ����.
			Node* uncle = newNode->Parent()->Parent()->Left();

			// ���� ��尡 �������� ��.
			// �ذ�: �θ�� ������ ���������� �����ϰ�, ���θ� ���������� �����ؼ�
			// ������ ���� �ø���.
			if (uncle->GetColor() == Color::Red)
			{
				newNode->Parent()->SetColor(Color::Black);
				uncle->SetColor(Color::Black);
				newNode->Parent()->Parent()->SetColor(Color::Red);

				// ������ ������ �ڿ� ���� ��忡���� ���� ������ �߻������� �ʴ��� Ȯ��.
				newNode = newNode->Parent()->Parent();
				continue;
			}
			// ���� ��尡 �������� ��.
			// �ذ�: �θ�, ���θ�, �� ����� ��ġ�� ���� ȸ���� ����.
			// #1: �� ��尡 �θ�� �ݴ� ��ġ�� �� -> �θ� �߽����� 1�� ȸ�� �� �ٽ� ȸ��.
			// #2: �� ��尡 �θ�� ���� ��ġ�� �� -> ȸ�� �� ���� �缳���� ���� ��ġ ������.
			else
			{
				// �θ�� �ݴ� ��ġ�� ��� (�߰� ȸ��).
				// �θ�� �� ����� ��ġ�� ���߱� ����.
				if (newNode == newNode->Parent()->Left())
				{
					// �θ� �߽����� ȸ�� ����.
					newNode = newNode->Parent();
					RightRotate(newNode);
				}

				// ���θ� �߽����� ȸ�� �� ���� ����.
				newNode->Parent()->SetColor(Color::Black);
				newNode->Parent()->Parent()->SetColor(Color::Red);

				LeftRotate(newNode->Parent()->Parent());
			}
		}
	}

	// ��Ʈ ��带 ������ ����.
	root->SetColor(Color::Black);
}

void RedBlackTree::RestructureAfterRemove(Node* node)
{
	// ������ ����� ������ �������� ���, Double Black ���� �ذ�.
	while (node->Parent() != nullptr && node->GetColor() == Color::Black)
	{
		// ���� ��� ������ ���� ���� ����.
		Node* sibling = nullptr;

		// ���� ��尡 �θ��� ���� �ڽ� ����� ���.
		if (node == node->Parent()->Left())
		{
			// ������ �ڽ� ��带 ���� ���� ����.
			sibling = node->Parent()->Right();
			if (sibling == nullptr || sibling == nil)
			{
				break;
			}

			// Case1: ���� ��尡 ������.
			// �ذ�: �θ�� ���� ����� ������ ��ü�ϰ�, �θ� �������� ��ȸ��.
			if (sibling->GetColor() == Color::Red)
			{
				// �θ�� ���� ����� ������ ��ü.
				sibling->SetColor(Color::Black);
				node->Parent()->SetColor(Color::Red);

				// �θ� ��带 �������� ��ȸ��.
				LeftRotate(node->Parent());
			}

			// Case2: ���� ��尡 �������� ���.
			else
			{
				// ���� ����� �� �ڽ� ��尡 ��� �������� ��.
				// �ذ�: ���� ��带 ���������� �����ϰ�, ������ �θ�� �÷��� ó�� ����.
				if (sibling->Left()->GetColor() == Color::Black
					&& sibling->Right()->GetColor() == Color::Black)
				{
					sibling->SetColor(Color::Red);
					node = node->Parent();
					continue;
				}

				else
				{
					// Case3: ���� ���� ������, ���� ����� ���� �ڽ��� �������� ���.
					// �ذ�: ������ ���� �ڽ��� Black���� �����, ���� ��带 Red�� ������ �� ���� ��带 �������� ��ȸ��.
					if (sibling->Left()->GetColor() == Color::Red)
					{
						sibling->Left()->SetColor(Color::Black);
						sibling->SetColor(Color::Red);

						RightRotate(sibling);

						// ȸ�� ó�� �� ���ο� ���� ��带 ������Ʈ �� �缳�� ����.
						sibling = node->Parent()->Right();
					}


					// Case4: ���� ��尡 �������ε�, ������ �ڽ� ��尡 �������� ���.
					// �ذ�: ���� ���� �θ� ��带 ���������� �����ϰ�, �θ� ��带 ���������� ������ ��,
					// ���� ����� ������ �ڼ��� ���������� ������ ��, �θ� ��带 �������� ��ȸ��.
					sibling->SetColor(node->Parent()->GetColor());
					sibling->Parent()->SetColor(Color::Black);
					sibling->Right()->SetColor(Color::Black);
					LeftRotate(node->Parent());

					// Ʈ���� ��Ʈ���� ���� �Ϸ�.
					node = root;
				}
			}
		}

		// �θ� ���� ������
		else
		{
			sibling = node->Parent()->Left();
			if (sibling == nullptr || sibling == nil)
			{
				break;
			}

			if (sibling->GetColor() == Color::Red)
			{
				sibling->SetColor(Color::Black);
				node->Parent()->SetColor(Color::Red);
				RightRotate(node->Parent());
			}
			else
			{
				if (sibling->Right()->GetColor() == Color::Black
					&& sibling->Left()->GetColor() == Color::Black)
				{
					sibling->SetColor(Color::Red);
					node = node->Parent();
					continue;
				}
				else
				{
					if (sibling->Right()->GetColor() == Color::Red)
					{
						sibling->Right()->SetColor(Color::Black);
						sibling->SetColor(Color::Red);

						LeftRotate(sibling);
						sibling = node->Parent()->Left();
					}

					sibling->SetColor(node->Parent()->GetColor());
					node->Parent()->SetColor(Color::Black);
					sibling->Left()->SetColor(Color::Black);

					RightRotate(node->Parent());
					node = root;
				}
			}
		}
	}

	// ���������� ��带 ���������� ������ ���� �� ���� ����.
	node->SetColor(Color::Black);
}

void RedBlackTree::LeftRotate(Node* node)
{
	// ȸ���� ���� ������ �ڽ� ��� ����.
	Node* right = node->Right();

	// ������ �ڽ� ����� ���� �ڽ� ��带 �θ��� ������ �ڽ����� ���.
	node->SetRight(right->Left());

	// ���� ����� �θ� ���� ó��.
	if (right->Left() != nil)
	{
		right->Left()->SetParent(node);
	}

	// ������ �ڽ� ����� ����� �θ� ����(���� �θ��� ���θ� �θ�� ����).
	right->SetParent(node->Parent());

	// �θ� null�� ��쿡 �� ���� root.
	// �� ���� ������ �ڽ� ��带 root�� ����.
	if (right->Parent() == nullptr)
	{
		root = right;
	}

	// Root�� �ƴ� ���� ȸ�� ó��.
	else
	{
		// ������ �ڽ� ��带 �θ� ��尡 �ִ� ��ġ�� ����.
		// ���θ��� �ڽ� ��ġ.
		if (node == node->Parent()->Left())
		{
			node->Parent()->SetLeft(right);
		}
		else
		{
			node->Parent()->SetRight(right);
		}
	}

	// ��ȸ�� ó��.
	right->SetLeft(node);
	node->SetParent(right);
}

void RedBlackTree::RightRotate(Node* node)
{
	// ȸ���� ���� ���� �ڽ� ��� ����.
	Node* left = node->Left();

	// ���� �ڽ� ����� ������ �ڽ� ��带 �θ��� ���� �ڽ����� ���.
	node->SetLeft(left->Right());

	// ���� ����� �θ� ���� ó��.
	if (left->Right() != nil)
	{
		left->Right()->SetParent(node);
	}

	// ���� �ڽ� ����� ����� �θ� ����(���� �θ��� ���θ� �θ�� ����).
	left->SetParent(node->Parent());

	// �θ� null�� ��쿡 �� ���� root.
	// �� ���� ���� �ڽ� ��带 root�� ����.
	if (left->Parent() == nullptr)
	{
		root = left;
	}

	// Root�� �ƴ� ���� ȸ�� ó��.
	else
	{
		// ���� �ڽ� ��带 �θ� ��尡 �ִ� ��ġ�� ����.
		// ���θ��� �ڽ� ��ġ.
		if (node == node->Parent()->Left())
		{
			node->Parent()->SetLeft(left);
		}
		else
		{
			node->Parent()->SetRight(left);
		}
	}

	// ��ȸ�� ó��.
	left->SetRight(node);
	node->SetParent(left);
}

void RedBlackTree::PrintRecursive(Node* node, int depth, int blackCount)
{
	// ��� �Լ� Ż�� ����.
	if (node == nil)
	{
		return;
	}

	// ��� ������ �������̸� blackCount ����.
	if (node->GetColor() == Color::Black)
	{
		++blackCount;
	}

	// �θ� ǥ�⸦ ���� ���ڿ� ����.
	int parentData = 0;
	const char* position = "Root";

	// �θ� ��尡 �ִ��� Ȯ�� �� ����.
	if (node->Parent())
	{
		// �θ� ����� ������ ����.
		parentData = node->Parent()->Data();

		// �θ� ���κ��� ���� ����� ��ġ ����.
		if (node == node->Parent()->Left())
		{
			position = "Left";
		}
		else
		{
			position = "Right";
		}
	}

	// ������ ��� �� ����� ���� ���ڿ� ����.
	char blackCountString[50] = { };

	// �ڼ��� ���� ����� ���, ��������� ������ ��� �� ����.
	if (node->Left() == nil && node->Right() == nil)
	{
		sprintf_s(blackCountString, "-------- %d", blackCount);
	}

	// Depth ���.
	for (int ix = 0; ix < depth; ++ix)
	{
		std::cout << " ";
	}

	// ��� ��ġ�� ���� �ܼ� ���� ���� �� ���� ���.
	if (node->GetColor() == Color::Red)
	{
		SetTextColor(TextColor::Red);
	}
	else
	{
		SetTextColor(TextColor::White);
	}

	// ���� ��� �� ���.
	std::cout << node->Data() << " " << node->ColorString() << " [" << position << ", " << parentData << "]" << " " << blackCountString << "\n";

	// ���� ������� �缳��.
	SetTextColor(TextColor::White);

	// ���� ��� ���.
	PrintRecursive(node->Left(), depth + 1, blackCount);
	PrintRecursive(node->Right(), depth + 1, blackCount);
}

void SetTextColor(TextColor color)
{
	static HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (int)color);
}