#include <iostream>
#include "RedBlackTree.h"
#include <vector>
#include <Windows.h>
using namespace std;

// ��� ������ ���� ������
enum class Command
{
	None,
	Insert,
	Delete,
	Find,
	Print,
	Quit
};

// ȭ�� ����� �Լ�
void ClearScreen()
{
	system("cls");
}

void ProcessCommandInput(int& commandInput);

void ProcessParamInput(int& param)
{
	// �Է� ó�� ����
	char inputBuffer[100];

	// �Է� ó�� ���� 
	while (true)
	{
		cout << "�Ķ���͸� �Է��ϼ��� (1-200).\n";
		cin >> inputBuffer;

		// ����
		if (param = atoi(inputBuffer))
		{
			// ����ó��
			if (param < 1 || param > 200)
			{
				ClearScreen();
				cout << "���� : �Ķ���ʹ� 1-200 ������ ���ڸ� �Է��ؾ� �մϴ�.\n";
				continue;
			}
			break;
		}

		// ����ó��
		ClearScreen();
		cout << "���� : �Ķ���ʹ� ���ڸ� �Է��ؾ� �մϴ�.\n";
	}
}

// ��� ó�� �Լ�
void ProcessCommand(int commandInput, RedBlackTree& tree)
{
	// �Է� ���� ���������� ��ȯ
	Command command = (Command)commandInput;

	if (command == Command::Print)
	{
		ClearScreen();
		tree.Print();
	
		return;
	}

	// ���α׷� ����
	if (command == Command::Quit)
	{
		//exit(0);
		return;
	}

	// 1,2,3 ��� ó�� (�Ķ���� �Է��� �߰��� �ʿ���)
	int param = 0;
	ProcessParamInput(param);

	// 1/2/3 ��� ó��
	switch (command)
	{
		// ��� �߰�
		case Command::Insert:
		{
			ClearScreen();
			tree.Insert(param);
		}
		break;
		case Command::Delete:
		{
			ClearScreen();
			tree.Remove(param);
		}
		break;
		case Command::Find:
		{
			// �˻�
			Node* result = nullptr;
			if (result = tree.Find(param))
			{
				// �˻� ����
				if (result->GetColor() == Color::Red)
				{
					SetTextColor(TextColor::Red);
				}
				else
				{
					SetTextColor(TextColor::White);
				}

				cout << "�˻��� ��� : " << result->Data() << "(Color: " << result->ColorString() << ")\n";
				SetTextColor(TextColor::White);
				return;
			}

			else
			{
				cout << "��带 ã�� ���߽��ϴ�. (�˻� ��: " << param << ")n";
			}

		}
		break;
		case Command::Print:
		{

		}
		break;
		case Command::Quit:
		{

		}
		break;
	}
}

bool useInitData = true;

void Initialization(const char* path, RedBlackTree* tree)
{
	if (tree == nullptr)
	{
		std::cout << "����: ���޵� Ʈ���� null �Դϴ�.\n";
		return;
	}

	FILE* file = nullptr;
	fopen_s(&file, path, "r");
	if (file == nullptr)
	{
		std::cout << "����: ���� �б� ����.\n";
		return;
	}

	char line[1024] = { };
	if (!fgets(line, 1024, file))
	{
		std::cout << "����: ���� �б� ����.\n";
		fclose(file);
		return;
	}

	fclose(file);

	std::vector<int> datas;

	// ù ��� �б�.
	char* context = nullptr;
	char* splitString = strtok_s(line, ",", &context);
	if (splitString)
	{
		if (int parsed = atoi(splitString))
		{
			datas.emplace_back(parsed);
		}
	}

	// ������ ��� �б�.
	while (context)
	{
		splitString = strtok_s(nullptr, ",", &context);
		if (!splitString)
		{
			break;
		}

		if (int parsed = atoi(splitString))
		{
			datas.emplace_back(parsed);
		}
	}

	// Ʈ���� ������ �߰�.
	for (auto data : datas)
	{
		tree->Insert(data);
	}

	// �ʱ� �����͸� ������ ���� ������ ���.
	std::cout << "�ʱ� �����Ͱ� ����Ǿ����ϴ�.\n";
	tree->Print();
	std::cout << "\n";
}


int main()
{
	// ���� �� Ʈ�� ����
	RedBlackTree tree;

	if (useInitData)
	{
		Initialization("../Assets/InitData.txt", &tree);
	}

	while (true)
	{
		// ��� �Է� ó��
		int commandInput = 0;
		ProcessCommandInput(commandInput);

		// ��� ó��
		ProcessCommand(commandInput, tree);

		// ���� ó��
		if (commandInput == (int)Command::Quit)
		{
			break;
		}
	}

	return 0;
}

void ProcessCommandInput(int& commandInput) 
{
	// �Է� ó��
	char inputBuffer[100] = {};

	while (true)
	{
		cout << "��� ���ڸ� �Է��ϼ���.\n";
		cout << "(1)��� �߰�, (2)��� ����, (3)��� �˻�, 4(��� ���), (5)����\n";
		cin >> inputBuffer;

		if (commandInput = atoi(inputBuffer))
		{
			// ����ó��
			if (commandInput <= (int)Command::None
				|| commandInput > (int)Command::Quit)
			{
				ClearScreen();
				cout << "���� : �߸��� ���ڸ� �Է��߽��ϴ�.\n";
				continue;
			}


			break;
		}

		// ����ó��
		ClearScreen();
		cout << "���� : ����� ���ڸ� �Է��ؾ� �մϴ�.\n";
	}

}