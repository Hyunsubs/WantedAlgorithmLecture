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

	// ��
	int row;
	// ��
	int col;
};

// �� �迭.
int mapSize = 0;
std::vector<std::vector<char>> map;

// �̵� ���� ���� �Ǵ� �Լ�
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

// ���� ���� �˻� �Լ�
void FindStartLocation(int& row, int& col)
{
	for (int ix = 0; ix < mapSize; ix++)
	{
		for (int jx = 0; jx < mapSize; jx++)
		{

			// �� ���
			std::cout << map[ix][jx] << " ";

			// ���� ������ ��Ÿ���� ���� �˻�
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

// �̷� Ż�� �Լ�
void EscapeMaze()
{
	mapSize = (int)map.size();
	// ��ġ ������ ���� ���� ����
	int row = 0;
	int col = 0;

	// Ž�� ������ ���� ���� ��ġ
	FindStartLocation(row, col);

	// ���� ����
	std::stack<Location2D> stack;

	// ���ÿ� ���� ��ġ ����
	stack.push(Location2D(row, col));

	// �̷� Ž��
	while (!stack.empty())
	{
		// ���� ��ġ ��ȯ
		Location2D current = stack.top();
		stack.pop();

		// Ž�� ��ġ ���
		std::cout << "(" << current.row << "," << current.col << ") ";
		
		row = current.row;
		col = current.col;

		// Ż������
		if (map[row][col] == 'x')
		{
			std::cout << " \n�̷� Ž�� ����\n";
			return;
		}

		// Ž�� ����
		// �湮�� ���� ��ġ�� ��湮 ������ ���� ǥ��
		map[row][col] = '.';

		// �� �� �� �� ��ġ �� �̵� ������ ��ġ�� ���ÿ� ����
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

	std::cout << "\n�̷� Ž�� ����\n";
}

int main()
{
	ParseMap("../Assets/Map.txt");
	EscapeMaze();

	std::cin.get();

	return 0;
}