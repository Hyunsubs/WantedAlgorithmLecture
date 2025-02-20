#include "AStar.h"
#include "Node.h"

AStar::AStar()
{
}

AStar::~AStar()
{
    // 메모리 해제
    for (Node* node : openList)
    {
        SafeDelete(node);
    }

    openList.clear();

    for (Node* node : closedList)
    {
        SafeDelete(node);
    }

    closedList.clear();
}

std::vector<Node*> AStar::FindPath(Node* startNode, Node* goalNode, const std::vector<std::vector<int>>& grid)
{
	this->startNode = startNode;
	this->goalNode = goalNode;

	// 시작 노드를 열린 리스트(OpenList)에 추가.
	openList.emplace_back(startNode);

	// 상하좌우 및 대각선 이동 방향과 비용
	std::vector<Direction> directions =
	{
		// 하상우좌 이동.
		{ 0, 1, 1.0f }, { 0, -1, 1.0f }, { 1, 0, 1.0f }, { -1, 0, 1.0f },

		// 대각선 이동.
		{ 1, 1, 1.414f }, { 1, -1, 1.414f }, { -1, 1, 1.414f }, { -1, -1, 1.414f }
	};

	// 이웃 노드 탐색 (열린 리스트가 비어 있지 않은 동안 반복).
	while (!openList.empty())
	{
		// 현재 열린 리스트에서 fCost가 가장 낮은 노드 검색.
		Node* lowestNode = openList[0];
		for (Node* node : openList)
		{
			if (node->fCost < lowestNode->fCost)
			{
				lowestNode = node;
			}
		}

		// fCost가 가장 낮은 노드를 현재 노드로 설정.
		Node* currentNode = lowestNode;

		// 현재 노드가 목표 노드인지 확인 후 맞으면 종료.
		if (IsDestination(currentNode))
		{
			return ConstructPath(currentNode);
		}

		// 방문 처리를 위해 현재 노드를 열린 리스트에서 제거.
		for (int ix = 0; ix < static_cast<int>(openList.size()); ++ix)
		{
			if (*openList[ix] == *currentNode)
			{
				openList.erase(openList.begin() + ix);
				break;
			}
		}

		// 방문 처리를 위해 현재 노드를 닫힌 리스트에 추가.
		// 이미 닫힌 노드에 있는 노드인지 확인 후에 없으면 추가.
		bool isNodeInList = false;
		for (Node* node : closedList)
		{
			if (*node == *currentNode)
			{
				isNodeInList = true;
				break;
			}
		}

		if (isNodeInList)
		{
			continue;
		}

		closedList.emplace_back(currentNode);

		// 이웃 노드 방문(탐색). (하/상/우/좌 차례로 방문).
		for (const Direction& direction : directions)
		{
			// 다음에 이동할 위치 설정.
			int newX = currentNode->position.x + direction.x;
			int newY = currentNode->position.y + direction.y;

			// 그리드 밖이면 무시.
			if (!IsInRange(newX, newY, grid))
			{
				continue;
			}

			// 이동할 위치가 장애물인 경우에는 무시.
			if (grid[newY][newX] == 1)
			{
				continue;
			}

			// 이미 방문한 노드인 경우 무시.
			if (HasVisited(newX, newY, currentNode->gCost + direction.cost))
			{
				continue;
			}

			// 방문을 위한 이웃 노드 생성.
			// 방문할 노드의 gCost, hCost, fCost 계산.
			Node* neighborNode = new Node(newX, newY, currentNode);
			neighborNode->gCost = currentNode->gCost + direction.cost;
			neighborNode->hCost = CalculateHeuristic(neighborNode, goalNode);
			neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;

			// 이웃 노드가 열린 리스트에 있는지 확인.
			Node* openListNode = nullptr;
			for (Node* node : openList)
			{
				if (*node == *neighborNode)
				{
					openListNode = node;
					break;
				}
			}

			// 이웃 노드가 열린 리스트에 없는 경우, 방문을 위해 열린 리스트에 추가.
			// 이웃 노드가 열린 리스트에 있다면, gCost와 fCost를 비교해 더 나은 경우에 열린 리스트에 추가.
			if (openListNode == nullptr
				|| neighborNode->gCost < openListNode->gCost
				|| neighborNode->fCost < openListNode->fCost)
			{
				openList.emplace_back(neighborNode);
			}
			else
			{
				SafeDelete(neighborNode);
			}
		}
	}

	return {};
}

void AStar::DisplayGridWithPath(std::vector<std::vector<int>>& grid, const std::vector<Node*>& path)
{
    // 경로에 있는 위치는 2로 표기
    for (const Node* node : path)
    {
        grid[node->position.y][node->position.x] = 2;
    }

    // 맵 출력
    for (int y = 0; y < (int)grid.size(); y++)
    {
        for (int x = 0; x < (int)grid[0].size(); x++)
        {
            // 장애물
            if (grid[y][x] == 1)
            {
                std::cout << "1 ";
            }

            // 경로
            else if (grid[y][x] == 2)
            {
                std::cout << "+ ";
            }

            // 맵
            else if (grid[y][x] == 0)
            {
                std::cout << "0 ";
            }
        }

        std::cout << "\n";
    }
}

std::vector<Node*> AStar::ConstructPath(Node* goalNode)
{
    // 목표 노드로부터 부모 노드를 따라 역추적하면서 경로 설정
    std::vector<Node*> path;
    Node* currentNode = goalNode;

    while (currentNode != nullptr)
    {
        path.emplace_back(currentNode);
        currentNode = currentNode->parent;
    }

    // 시작 지점부터 목표지점으로 향하도록 배열 뒤집기
    std::reverse(path.begin(), path.end());

    return path;
}

float AStar::CalculateHeuristic(Node* currentNode, Node* goalNode)
{
    // 현재 노드에서 목표 노드까지의 차이 계산
    Position diff = *currentNode - *goalNode;
    return std::sqrtf((float)(diff.x * diff.x + diff.y * diff.y));
}

bool AStar::IsInRange(int x, int y, const std::vector<std::vector<int>>& grid)
{
    // 벗어난 경우인지 확인
    if (x < 0 || x >= grid[0].size() || y < 0 || y >= grid.size())
    {
        return false;
    }

    return true;
}

bool AStar::HasVisited(int x, int y, float gCost)
{
    // 열린/닫힌 리스트에 이미 해당 위치가 있으면 방문한 것으로 판단
    for (int ix = 0; ix < (int)openList.size(); ix++)
    {
        Node* node = openList[ix];
        if ((node->position.x == x && node->position.y == y))
        {
            // 위치도 같고, 비용이 더 크면 방문할 이유 없음
            if (gCost > node->gCost)
            {
                return true;
            }

            // 새 노드의 비용이 작은 경우에는 기존 노드 제거
            openList.erase(openList.begin() + ix);
            SafeDelete(node);
        }
    }

    for (int ix = 0; ix < (int)closedList.size(); ix++)
    {
        Node* node = closedList[ix];
        if ((node->position.x == x && node->position.y == y))
        {
            // 위치도 같고, 비용이 더 크면 방문할 이유 없음
            if (gCost > node->gCost)
            {
                return true;
            }

            // 새 노드의 비용이 작은 경우에는 기존 노드 제거
            closedList.erase(closedList.begin() + ix);
            SafeDelete(node);
        }
    }

    // 리스트에 없으면 방문하지 않은 것으로 판단
    return false;
}

bool AStar::IsDestination(const Node* node)
{
    return *node == *goalNode;
}
