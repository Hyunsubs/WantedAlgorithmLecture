#include <iostream>
using namespace std;

void Merge(int* array,
	int* leftArray,
	int leftArrayLength,
	int* rightArray,
	int rightArrayLength)
{
	int leftIndex = 0;
	int rightIndex = 0;
	int mergedIndex = 0;

	while (leftIndex < leftArrayLength && rightIndex < rightArrayLength)
	{
		if (leftArray[leftIndex] <= rightArray[rightIndex])
		{
			array[mergedIndex] = leftArray[leftIndex];
			leftIndex++;
		}
		else
		{
			array[mergedIndex] = rightArray[rightIndex];
			rightIndex++;
		}
		mergedIndex++;
	}

	// 위 과정에서 남은 왼쪽 배열 요소를 최종 배열에 복사.
	while (leftIndex < leftArrayLength)
	{
		array[mergedIndex] = leftArray[leftIndex];
		++mergedIndex;
		++leftIndex;
	}

	// 위 과정에서 남은 오른쪽 배열 요소를 최종 배열에 복사.
	while (rightIndex < rightArrayLength)
	{
		array[mergedIndex] = rightArray[rightIndex];
		++mergedIndex;
		++rightIndex;
	}

}


void MergeSort(int* array, int length)
{
	if (length <= 1)
		return;

	int mid = length / 2;

	int* leftArray = new int[mid];
	int* rightArray = new int[length - mid];

	memcpy(leftArray, array, sizeof(int) * mid);
	memcpy(rightArray, array + mid, sizeof(int) * (length - mid));

	// 재귀
	MergeSort(leftArray, mid);

	MergeSort(rightArray, length - mid);

	// 병합
	Merge(array, leftArray, mid, rightArray, length - mid);
	
}


// 배열 출력 함수.
void PrintArray(int array[], int length)
{
	for (int ix = 0; ix < length; ++ix)
	{
		std::cout << array[ix] << (ix < length - 1 ? ", " : "");
	}

	std::cout << "\n";
}




int main()
{

	// 배열.
	int array[] = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };

	// 길이 계산
	int length = _countof(array);

	// 정렬 전 출력
	cout << "정렬 전: ";
	PrintArray(array, length);

	MergeSort(array, length);

	// 정렬 후 출력
	cout << "정렬 후: ";
	PrintArray(array, length);


	return 0;
}