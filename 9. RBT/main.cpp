#include <iostream>
#include "RedBlackTree.h"
#include <vector>
#include <Windows.h>
using namespace std;

// 명령 구분을 위한 열거형
enum class Command
{
	None,
	Insert,
	Delete,
	Find,
	Print,
	Quit
};

// 화면 지우는 함수
void ClearScreen()
{
	system("cls");
}

void ProcessCommandInput(int& commandInput);

void ProcessParamInput(int& param)
{
	// 입력 처리 버퍼
	char inputBuffer[100];

	// 입력 처리 루프 
	while (true)
	{
		cout << "파라미터를 입력하세요 (1-200).\n";
		cin >> inputBuffer;

		// 검증
		if (param = atoi(inputBuffer))
		{
			// 예외처리
			if (param < 1 || param > 200)
			{
				ClearScreen();
				cout << "오류 : 파라미터는 1-200 사이의 숫자만 입력해야 합니다.\n";
				continue;
			}
			break;
		}

		// 예외처리
		ClearScreen();
		cout << "오류 : 파라미터는 숫자만 입력해야 합니다.\n";
	}
}

// 명령 처리 함수
void ProcessCommand(int commandInput, RedBlackTree& tree)
{
	// 입력 값을 열거형으로 변환
	Command command = (Command)commandInput;

	if (command == Command::Print)
	{
		ClearScreen();
		tree.Print();
	
		return;
	}

	// 프로그램 종료
	if (command == Command::Quit)
	{
		//exit(0);
		return;
	}

	// 1,2,3 명령 처리 (파라미터 입력이 추가로 필요함)
	int param = 0;
	ProcessParamInput(param);

	// 1/2/3 명령 처리
	switch (command)
	{
		// 노드 추가
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
			// 검색
			Node* result = nullptr;
			if (result = tree.Find(param))
			{
				// 검색 실패
				if (result->GetColor() == Color::Red)
				{
					SetTextColor(TextColor::Red);
				}
				else
				{
					SetTextColor(TextColor::White);
				}

				cout << "검색된 노드 : " << result->Data() << "(Color: " << result->ColorString() << ")\n";
				SetTextColor(TextColor::White);
				return;
			}

			else
			{
				cout << "노드를 찾지 못했습니다. (검색 값: " << param << ")n";
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
		std::cout << "오류: 전달된 트리가 null 입니다.\n";
		return;
	}

	FILE* file = nullptr;
	fopen_s(&file, path, "r");
	if (file == nullptr)
	{
		std::cout << "오류: 파일 읽기 실패.\n";
		return;
	}

	char line[1024] = { };
	if (!fgets(line, 1024, file))
	{
		std::cout << "오류: 파일 읽기 실패.\n";
		fclose(file);
		return;
	}

	fclose(file);

	std::vector<int> datas;

	// 첫 토근 읽기.
	char* context = nullptr;
	char* splitString = strtok_s(line, ",", &context);
	if (splitString)
	{
		if (int parsed = atoi(splitString))
		{
			datas.emplace_back(parsed);
		}
	}

	// 나머지 토근 읽기.
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

	// 트리에 데이터 추가.
	for (auto data : datas)
	{
		tree->Insert(data);
	}

	// 초기 데이터를 설정한 후의 데이터 출력.
	std::cout << "초기 데이터가 적용되었습니다.\n";
	tree->Print();
	std::cout << "\n";
}


int main()
{
	// 레드 블랙 트리 생성
	RedBlackTree tree;

	if (useInitData)
	{
		Initialization("../Assets/InitData.txt", &tree);
	}

	while (true)
	{
		// 명령 입력 처리
		int commandInput = 0;
		ProcessCommandInput(commandInput);

		// 명령 처리
		ProcessCommand(commandInput, tree);

		// 종료 처리
		if (commandInput == (int)Command::Quit)
		{
			break;
		}
	}

	return 0;
}

void ProcessCommandInput(int& commandInput) 
{
	// 입력 처리
	char inputBuffer[100] = {};

	while (true)
	{
		cout << "명령 숫자를 입력하세요.\n";
		cout << "(1)노드 추가, (2)노드 삭제, (3)노드 검색, 4(노드 출력), (5)종료\n";
		cin >> inputBuffer;

		if (commandInput = atoi(inputBuffer))
		{
			// 예외처리
			if (commandInput <= (int)Command::None
				|| commandInput > (int)Command::Quit)
			{
				ClearScreen();
				cout << "오류 : 잘못된 숫자를 입력했습니다.\n";
				continue;
			}


			break;
		}

		// 예외처리
		ClearScreen();
		cout << "오류 : 명령은 숫자만 입력해야 합니다.\n";
	}

}