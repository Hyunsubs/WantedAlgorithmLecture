#include <iostream>


// �� ���� ���� ��ȯ�ϴ� �Լ�
void Swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

// ���� ���� �Լ�
void BubbleSort(int array[], int length)
{
	// ����
	for (int i = 0; i < length - 1; i++)
	{
		for (int j = 0; j < length - 1; j++)
		{
			//�ΰ��� ��
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
	
	// �迭 ����
	int length = sizeof(numbers) / sizeof(int);

	std::cout << "������ \n";

	// ���� ��
	for (auto i : numbers)
	{
		std::cout << i << "\n";
	}

	std::cout << "\n";
	std::cout << "������ \n";
	BubbleSort(numbers, length);

	// ���� ��
	for (auto i : numbers)
	{
		std::cout << i << "\n";
	}

	return 0;
}