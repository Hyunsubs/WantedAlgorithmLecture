#include <iostream>
using namespace std;

void SelectionSort(int* array, int length)
{
	for (int i = 0; i < length - 1; i++)
	{
		// 최소값 저장할 변수
		int minIndex = i;
		for (int j = i + 1; j < length; j++)
		{
			// 비교
			if (array[j] < array[minIndex])
			{
				minIndex = j;
			}
		}
		// 값 바꾸기
		std::swap<int>(array[i], array[minIndex]);
	}
}


// 출력 함수.
void PrintArray(int* array, int length)
{
	for (int ix = 0; ix < length; ++ix)
	{
		std::cout << array[ix] << " ";
	}

	std::cout << "\n";
}

int main()
{
	int array[] = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };

	// 배열 길이
	int length = sizeof(array) / sizeof(int);

	std::cout << "정렬전 \n";

	// 정렬 전
	PrintArray(array, length);

	std::cout << "\n";
	std::cout << "정렬후 \n";
	SelectionSort(array, length);

	// 정렬 후
	PrintArray(array, length);


	return 0;
}