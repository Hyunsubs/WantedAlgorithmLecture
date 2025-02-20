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
	// 트리가 비어 있다면, nullptr 반환.
	if (root == nil)
	{
		return nullptr;
	}

	// 루트에서부터 재귀 적으로 검색.
	return FindRecursive(root, data);
}

bool RedBlackTree::Insert(int data)
{
	// 추가할 데이터가 이미 트리에 있으면 실패.
	if (Find(data))
	{
		std::cout << "오류 - 노드 추가 실패: 이미 같은 값이 트리에 있습니다. 입력값: " << data << "\n";
		return false;
	}

	// 트리에 새 노드 추가.
	Insert(CreateNode(data));
	return true;
}

bool RedBlackTree::Remove(int data)
{
	// 삭제할 노드 검색에 실패했으면 삭제 실패.
	if (Find(data) == nullptr)
	{
		std::cout << "오류 - 노드 삭제 실패: 삭제할 노드를 찾지 못했습니다. (검색 값: " << data << ")\n";
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
	// 재귀 함수 탈출 조건.
	if (node == nil)
	{
		return;
	}

	// 왼쪽/오른쪽 자식 노드.
	Node* left = node->Left();
	Node* right = node->Right();

	// 자식 노드가 없는 경우에는 노드 삭제.
	if (left == nil && right == nil)
	{
		SafeDelete(node);
		return;
	}

	// 자식이 있는 경우에는 재귀적으로 삭제 진행.
	DestroyRecursive(left);
	DestroyRecursive(right);

	// 노드 삭제.
	SafeDelete(node);
}

Node* RedBlackTree::FindMin()
{
	// 재귀적으로 최소값 노드 검색.
	return FindMinRecursive(root);
}

Node* RedBlackTree::FindMax()
{
	// 재귀적으로 최대값 노드 검색.
	return FindMaxRecursive(root);
}

Node* RedBlackTree::FindRecursive(Node* node, int data)
{
	// 재귀 함수 탈출 조건 (검색에 실패하면 nullptr 반환).
	if (node == nil)
	{
		return nullptr;
	}

	// 찾은 경우 현재 노드 반환
	if (node->Data() == data)
	{
		return node;
	}

	// 검색할 데이터가 현재 노드 값 보다 작으면 왼쪽으로 검색 진행.
	if (node->Data() > data)
	{
		return FindRecursive(node->Left(), data);
	}

	// 검색할 데이터가 현재 노드 값 보다 크면 오쪽으로 검색 진행.
	else
	{
		return FindRecursive(node->Right(), data);
	}
}

Node* RedBlackTree::FindMinRecursive(Node* node)
{
	// 재귀 함수 탈출 조건.
	if (node == nil)
	{
		return nullptr;
	}

	// 왼쪽 하위 노드가 더 이상 없으면 현재 노드가 최소값.
	if (node->Left() == nil)
	{
		return node;
	}

	return FindMinRecursive(node->Left());
}

Node* RedBlackTree::FindMaxRecursive(Node* node)
{
	// 재귀 함수 탈출 조건.
	if (node == nil)
	{
		return nullptr;
	}

	// 오쪽 하위 노드가 더 이상 없으면 현재 노드가 최대값.
	if (node->Right() == nil)
	{
		return node;
	}

	return FindMaxRecursive(node->Right());
}

void RedBlackTree::Insert(Node* newNode)
{
	// 트리가 비어 있는 경우, 새 노드를 루트로 설정 후 종료.
	if (root == nil)
	{
		root = newNode;
		root->SetColor(Color::Black);
		return;
	}

	// 트리가 비어 있지 않은 경우에는, 재귀적으로 트리에 노드 삽입.
	InsertRecursive(root, newNode);

	// 삽입한 새 노드의 색상 및 자식 노드 설정.
	newNode->SetColor(Color::Red);
	newNode->SetLeft(nil);
	newNode->SetRight(nil);

	// 삽입 후 재정렬 진행.
	RestructureAfterInsert(newNode);
}

void RedBlackTree::InsertRecursive(Node* node, Node* newNode)
{
	// 새 노드의 데이터가 현재 노드보다 작으면, 왼쪽 하위 트리로 삽입 진행.
	if (node->Data() > newNode->Data())
	{
		// 왼쪽 하위 노드가 비었으면, 새 노드 삽입.
		if (node->Left() == nil)
		{
			node->SetLeft(newNode);
			newNode->SetParent(node);
		}

		// 비어 있지 않다면, 왼쪽 하위 트리로 삽입을 위한 검색 진행.
		else
		{
			InsertRecursive(node->Left(), newNode);
		}
	}

	// 새 노드의 데이터가 현재 노드보다 크면, 오른쪽 하위 트리로 삽입 진행.
	else
	{
		// 오른쪽 하위 노드가 비었으면, 새 노드 삽입.
		if (node->Right() == nil)
		{
			node->SetRight(newNode);
			newNode->SetParent(node);
		}

		// 비어 있지 않다면, 오른쪽 하위 트리로 삽입을 위한 검색 진행.
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

	// 삭제할 노드에 자손이 없는 경우 삭제할 노드 저장.
	if (target->Left() == nil || target->Right() == nil)
	{
		removed = target;

		// 삭제할 노드가 nil이라면 함수 종료(예외 처리).
		if (removed == nil)
		{
			return;
		}
	}

	// 자손이 있는 경우에는 이진 탐색 트리의 성격을 유지시키기 위해 노드 위치 변경.
	else
	{
		// 왼쪽 하위 노드에서 가장 큰 값을 삭제할 노드 위치로 설정.
		removed = FindMaxRecursive(target->Left());

		// 대체 노드가 존재하면, 해당 데이터를 설정.
		if (removed != nullptr && removed != nil)
		{
			// 대체 노드의 값 설정.
			target->SetData(removed->Data());
		}
	}

	// removed가 null이면 안되기 때문에 예외 처리.
	if (removed == nullptr || removed == nil)
	{
		return;
	}

	// removed의 자식 노드가 하나만 있는 경우, 자식을 trail로 설정.
	// 이 때 removed가 리프 노드(자손이 모두 nil)라면 trail은 nil 노드가 됨.
	if (removed->Left() != nil)
	{
		trail = removed->Left();
	}
	else
	{
		trail = removed->Right();
	}

	// removed의 부모와 trail을 연결해 removed 노드를 제거할 준비.
	trail->SetParent(removed->Parent());

	// removed가 루트 노드인 경우, trail을 루트로 설정.
	if (removed->Parent() == nullptr)
	{
		root = trail;
	}

	// 루트 노드가 아닌 경우.
	else
	{
		// trail 노드를 removed의 원래 위치에 설정.
		if (removed == removed->Parent()->Left())
		{
			removed->Parent()->SetLeft(trail);
		}
		else
		{
			removed->Parent()->SetRight(trail);
		}
	}

	// 레드 블랙 트리의 규칙을 유지하기 위해 재조정 진행.
	// 이때 삭제한 노드가 빨간색인 경우에는 필요하지 않고, 검은색인 경우에만 진행.
	if (removed->GetColor() == Color::Black && trail != nil)
	{
		// 재정렬 진행
		RestructureAfterRemove(trail);
	}

	// 제거할 노드 삭제.
	SafeDelete(removed);
}

void RedBlackTree::RestructureAfterInsert(Node* newNode)
{
	// 부모 노드가 빨간색인 경우에는 
	// 빨간색 노드가 연속으로 나올 수 없다는 조건을 
	// 만족하지 않기 때문에 이를 해결하기 위해 재정렬 진행(Case2: Red-Red Conflict).
	while (newNode != root && newNode->Parent()->GetColor() == Color::Red)
	{
		// 해결 방법 (삼촌이 빨간색인 경우/삼촌이 검은색인 경우).
		// 삼촌 구하기 #1: 새 노드의 부모가 조부모의 왼쪽 자손인 경우.
		if (newNode->Parent() == newNode->Parent()->Parent()->Left())
		{
			// 삼촌.
			Node* uncle = newNode->Parent()->Parent()->Right();

			// 삼촌 노드가 빨간색일 때.
			// 해결: 부모와 삼촌은 검은색으로 변경하고, 조부모를 빨간색으로 변경해서
			// 문제를 위로 올린다.
			if (uncle->GetColor() == Color::Red)
			{
				newNode->Parent()->SetColor(Color::Black);
				uncle->SetColor(Color::Black);
				newNode->Parent()->Parent()->SetColor(Color::Red);

				// 색상을 변경한 뒤에 위쪽 노드에서도 같은 문제가 발생하지는 않는지 확인.
				newNode = newNode->Parent()->Parent();
				continue;
			}
			// 삼촌 노드가 검은색일 때.
			// 해결: 부모, 조부모, 새 노드의 위치에 따라서 회전을 수행.
			// #1: 새 노드가 부모와 반대 위치일 때 -> 부모를 중심으로 1차 회전 후 다시 회전.
			// #2: 새 노드가 부모와 같은 위치일 때 -> 회전 및 색상 재설정을 통해 위치 재정렬.
			else
			{
				// 부모와 반대 위치인 경우 (추가 회전).
				// 부모와 새 노드의 위치를 맞추기 위해.
				if (newNode == newNode->Parent()->Right())
				{
					// 부모를 중심으로 회전 진행.
					newNode = newNode->Parent();
					LeftRotate(newNode);
				}

				// 조부모를 중심으로 회전 및 색상 변경.
				newNode->Parent()->SetColor(Color::Black);
				newNode->Parent()->Parent()->SetColor(Color::Red);

				RightRotate(newNode->Parent()->Parent());
			}
		}

		// 삼촌 구하기 #2: 새 노드의 부모가 조부모의 오른쪽 자손인 경우.
		else
		{
			// 삼촌.
			Node* uncle = newNode->Parent()->Parent()->Left();

			// 삼촌 노드가 빨간색일 때.
			// 해결: 부모와 삼촌은 검은색으로 변경하고, 조부모를 빨간색으로 변경해서
			// 문제를 위로 올린다.
			if (uncle->GetColor() == Color::Red)
			{
				newNode->Parent()->SetColor(Color::Black);
				uncle->SetColor(Color::Black);
				newNode->Parent()->Parent()->SetColor(Color::Red);

				// 색상을 변경한 뒤에 위쪽 노드에서도 같은 문제가 발생하지는 않는지 확인.
				newNode = newNode->Parent()->Parent();
				continue;
			}
			// 삼촌 노드가 검은색일 때.
			// 해결: 부모, 조부모, 새 노드의 위치에 따라서 회전을 수행.
			// #1: 새 노드가 부모와 반대 위치일 때 -> 부모를 중심으로 1차 회전 후 다시 회전.
			// #2: 새 노드가 부모와 같은 위치일 때 -> 회전 및 색상 재설정을 통해 위치 재정렬.
			else
			{
				// 부모와 반대 위치인 경우 (추가 회전).
				// 부모와 새 노드의 위치를 맞추기 위해.
				if (newNode == newNode->Parent()->Left())
				{
					// 부모를 중심으로 회전 진행.
					newNode = newNode->Parent();
					RightRotate(newNode);
				}

				// 조부모를 중심으로 회전 및 색상 변경.
				newNode->Parent()->SetColor(Color::Black);
				newNode->Parent()->Parent()->SetColor(Color::Red);

				LeftRotate(newNode->Parent()->Parent());
			}
		}
	}

	// 루트 노드를 블랙으로 설정.
	root->SetColor(Color::Black);
}

void RedBlackTree::RestructureAfterRemove(Node* node)
{
	// 삭제된 노드의 색상이 검은색인 경우, Double Black 문제 해결.
	while (node->Parent() != nullptr && node->GetColor() == Color::Black)
	{
		// 형제 노드 저장을 위한 변수 선언.
		Node* sibling = nullptr;

		// 현재 노드가 부모의 왼쪽 자식 노드인 경우.
		if (node == node->Parent()->Left())
		{
			// 오른쪽 자식 노드를 형제 노드로 저장.
			sibling = node->Parent()->Right();
			if (sibling == nullptr || sibling == nil)
			{
				break;
			}

			// Case1: 형제 노드가 빨간색.
			// 해결: 부모와 형제 노드의 색상을 교체하고, 부모를 기준으로 좌회전.
			if (sibling->GetColor() == Color::Red)
			{
				// 부모와 형제 노드의 색상을 교체.
				sibling->SetColor(Color::Black);
				node->Parent()->SetColor(Color::Red);

				// 부모 노드를 기준으로 좌회전.
				LeftRotate(node->Parent());
			}

			// Case2: 형제 노드가 검은색인 경우.
			else
			{
				// 형제 노드의 두 자식 노드가 모두 검은색일 때.
				// 해결: 형제 노드를 빨간색으로 변경하고, 문제를 부모로 올려서 처리 진행.
				if (sibling->Left()->GetColor() == Color::Black
					&& sibling->Right()->GetColor() == Color::Black)
				{
					sibling->SetColor(Color::Red);
					node = node->Parent();
					continue;
				}

				else
				{
					// Case3: 형제 노드는 검은색, 형제 노드의 왼쪽 자식이 빨간색인 경우.
					// 해결: 형제의 왼쪽 자식을 Black으로 만들고, 형제 노드를 Red로 변경한 후 형제 노드를 기준으로 우회전.
					if (sibling->Left()->GetColor() == Color::Red)
					{
						sibling->Left()->SetColor(Color::Black);
						sibling->SetColor(Color::Red);

						RightRotate(sibling);

						// 회전 처리 후 새로운 형제 노드를 업데이트 해 재설정 진행.
						sibling = node->Parent()->Right();
					}


					// Case4: 형제 노드가 검은색인데, 형제의 자식 노드가 빨간색인 경우.
					// 해결: 형제 노드와 부모 노드를 같은색으로 설정하고, 부모 노드를 검은색으로 변경한 뒤,
					// 형제 노드의 오른쪽 자손을 검은색으로 변경한 후, 부모 노드를 기준으로 좌회전.
					sibling->SetColor(node->Parent()->GetColor());
					sibling->Parent()->SetColor(Color::Black);
					sibling->Right()->SetColor(Color::Black);
					LeftRotate(node->Parent());

					// 트리의 루트까지 변경 완료.
					node = root;
				}
			}
		}

		// 부모 기준 오른쪽
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

	// 마지막으로 노드를 검은색으로 설정해 더블 블랙 문제 제거.
	node->SetColor(Color::Black);
}

void RedBlackTree::LeftRotate(Node* node)
{
	// 회전을 위해 오른쪽 자식 노드 저장.
	Node* right = node->Right();

	// 오른쪽 자식 노드의 왼쪽 자식 노드를 부모의 오른쪽 자식으로 등록.
	node->SetRight(right->Left());

	// 하위 노드의 부모 변경 처리.
	if (right->Left() != nil)
	{
		right->Left()->SetParent(node);
	}

	// 오른쪽 자식 노드의 변경된 부모 설정(기존 부모의 조부모를 부모로 설정).
	right->SetParent(node->Parent());

	// 부모가 null인 경우에 이 노드는 root.
	// 이 때는 오른쪽 자식 노드를 root로 설정.
	if (right->Parent() == nullptr)
	{
		root = right;
	}

	// Root가 아닐 때는 회전 처리.
	else
	{
		// 오른쪽 자식 노드를 부모 노드가 있던 위치로 설정.
		// 조부모의 자식 위치.
		if (node == node->Parent()->Left())
		{
			node->Parent()->SetLeft(right);
		}
		else
		{
			node->Parent()->SetRight(right);
		}
	}

	// 좌회전 처리.
	right->SetLeft(node);
	node->SetParent(right);
}

void RedBlackTree::RightRotate(Node* node)
{
	// 회전을 위해 왼쪽 자식 노드 저장.
	Node* left = node->Left();

	// 왼쪽 자식 노드의 오른쪽 자식 노드를 부모의 왼쪽 자식으로 등록.
	node->SetLeft(left->Right());

	// 하위 노드의 부모 변경 처리.
	if (left->Right() != nil)
	{
		left->Right()->SetParent(node);
	}

	// 왼쪽 자식 노드의 변경된 부모 설정(기존 부모의 조부모를 부모로 설정).
	left->SetParent(node->Parent());

	// 부모가 null인 경우에 이 노드는 root.
	// 이 때는 왼쪽 자식 노드를 root로 설정.
	if (left->Parent() == nullptr)
	{
		root = left;
	}

	// Root가 아닐 때는 회전 처리.
	else
	{
		// 왼쪽 자식 노드를 부모 노드가 있던 위치로 설정.
		// 조부모의 자식 위치.
		if (node == node->Parent()->Left())
		{
			node->Parent()->SetLeft(left);
		}
		else
		{
			node->Parent()->SetRight(left);
		}
	}

	// 우회전 처리.
	left->SetRight(node);
	node->SetParent(left);
}

void RedBlackTree::PrintRecursive(Node* node, int depth, int blackCount)
{
	// 재귀 함수 탈출 조건.
	if (node == nil)
	{
		return;
	}

	// 노드 색상이 검은색이면 blackCount 증가.
	if (node->GetColor() == Color::Black)
	{
		++blackCount;
	}

	// 부모 표기를 위한 문자열 설정.
	int parentData = 0;
	const char* position = "Root";

	// 부모 노드가 있는지 확인 후 진행.
	if (node->Parent())
	{
		// 부모 노드의 데이터 저장.
		parentData = node->Parent()->Data();

		// 부모 노드로부터 현재 노드의 위치 설정.
		if (node == node->Parent()->Left())
		{
			position = "Left";
		}
		else
		{
			position = "Right";
		}
	}

	// 검은색 노드 수 출력을 위한 문자열 설정.
	char blackCountString[50] = { };

	// 자손이 없는 노드인 경우, 현재까지의 검은색 노드 수 설정.
	if (node->Left() == nil && node->Right() == nil)
	{
		sprintf_s(blackCountString, "-------- %d", blackCount);
	}

	// Depth 출력.
	for (int ix = 0; ix < depth; ++ix)
	{
		std::cout << " ";
	}

	// 노드 위치에 따른 콘솔 색상 설정 및 최종 출력.
	if (node->GetColor() == Color::Red)
	{
		SetTextColor(TextColor::Red);
	}
	else
	{
		SetTextColor(TextColor::White);
	}

	// 현재 노드 값 출력.
	std::cout << node->Data() << " " << node->ColorString() << " [" << position << ", " << parentData << "]" << " " << blackCountString << "\n";

	// 색상 원래대로 재설정.
	SetTextColor(TextColor::White);

	// 하위 노드 출력.
	PrintRecursive(node->Left(), depth + 1, blackCount);
	PrintRecursive(node->Right(), depth + 1, blackCount);
}

void SetTextColor(TextColor color)
{
	static HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (int)color);
}