#include <stack>
#include <iostream>
#include <vector>
#include <string>

struct Location2D
{
	Location2D(int row = 0, int col = 0)
		: row(row), col(col)
	{

	}

	// 행
	int row;
	// 열
	int col;
};

// 맵 배열.
int mapSize = 0;
std::vector<std::vector<char>> map;

// 이동 가능 여부 판단 함수
bool IsValidLocation(int row, int col)
{
	if (row >= mapSize || col >= mapSize)
	{
		return false;
	}

	if (row < 0 || col < 0)
	{
		return false;
	}

	return map[row][col] == '0' || map[row][col] == 'x';
}

bool ParseMap(const char* path)
{
	FILE* pFile = nullptr;
	fopen_s(&pFile, path, "rt");

	if (pFile)
	{
		char buff[256];
		char* buff2;
		fgets(buff, 256, pFile);
		int size = 0;
		sscanf_s(buff, "size %d", &size);
		map.resize(size);
		for (int i = 0; i < size; i++)
		{
			fgets(buff, 256, pFile);
			for (int j = 0; j < size; j++)
			{
				if (0 == j)
				{
					map[i].emplace_back(*strtok_s(buff, ",", &buff2));
				}
				else
				{
					map[i].emplace_back(*strtok_s(NULL, ",", &buff2));
				}
			}
		}
		fclose(pFile);
		return true;
	}

	return false;
}

// 시작 지점 검색 함수
void FindStartLocation(int& row, int& col)
{
	for (int ix = 0; ix < mapSize; ix++)
	{
		for (int jx = 0; jx < mapSize; jx++)
		{

			// 맵 출력
			std::cout << map[ix][jx] << " ";

			// 시작 지점을 나타내는 문자 검색
			if (map[ix][jx] == 'e') 
			{
				row = ix;
				col = jx;
				// return;
			}
		}

		std::cout << "\n";
	}
}

// 미로 탈출 함수
void EscapeMaze()
{
	mapSize = (int)map.size();
	// 위치 저장을 위한 변수 선언
	int row = 0;
	int col = 0;

	// 탐색 시작을 위해 시작 위치
	FindStartLocation(row, col);

	// 스택 선언
	std::stack<Location2D> stack;

	// 스택에 현재 위치 ㅅ밧
	stack.push(Location2D(row, col));

	// 미로 탐색
	while (!stack.empty())
	{
		// 현재 위치 반환
		Location2D current = stack.top();
		stack.pop();

		// 탐색 위치 출력
		std::cout << "(" << current.row << "," << current.col << ") ";
		
		row = current.row;
		col = current.col;

		// 탈출조건
		if (map[row][col] == 'x')
		{
			std::cout << " \n미로 탐색 성공\n";
			return;
		}

		// 탐색 진행
		// 방문한 현재 위치는 재방문 방지를 위해 표시
		map[row][col] = '.';

		// 상 하 좌 우 위치 중 이동 가능한 위치를 스택에 삽입
		if (IsValidLocation(current.row - 1, current.col))
		{
			stack.push(Location2D(current.row - 1, current.col));
		}
		if (IsValidLocation(current.row + 1, current.col))
		{
			stack.push(Location2D(current.row + 1, current.col));
		}
		if (IsValidLocation(current.row, current.col - 1))
		{
			stack.push(Location2D(current.row, current.col - 1));
		}
		if (IsValidLocation(current.row, current.col + 1))
		{
			stack.push(Location2D(current.row, current.col + 1));
		}
	}

	std::cout << "\n미로 탐색 실패\n";
}

int main()
{
	ParseMap("../Assets/Map.txt");
	EscapeMaze();

	std::cin.get();

	return 0;
}