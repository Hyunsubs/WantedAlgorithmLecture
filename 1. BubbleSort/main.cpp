#include <iostream>


// 두 값을 서로 교환하는 함수
void Swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

// 버블 정렬 함수
void BubbleSort(int array[], int length)
{
	// 정렬
	for (int i = 0; i < length - 1; i++)
	{
		for (int j = 0; j < length - 1; j++)
		{
			//두개씩 비교
			if (array[j] > array[j + 1])
			{
				Swap(array[j], array[j + 1]);
			}
		}
	}
}


int main()
{
	int numbers[] = {
	411,47,54,162,2345,2513,60,30
	};
	
	// 배열 길이
	int length = sizeof(numbers) / sizeof(int);

	std::cout << "정렬전 \n";

	// 정렬 전
	for (auto i : numbers)
	{
		std::cout << i << "\n";
	}

	std::cout << "\n";
	std::cout << "정렬후 \n";
	BubbleSort(numbers, length);

	// 정렬 후
	for (auto i : numbers)
	{
		std::cout << i << "\n";
	}

	return 0;
}