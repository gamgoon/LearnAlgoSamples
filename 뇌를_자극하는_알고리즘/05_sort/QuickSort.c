#include <stdio.h>

void Swap(int* A, int* B)
{
	int Temp = *A;
	*A = *B;
	*B = Temp;
}

int Partition(int DataSet[], int Left, int Right)
{
	int First = Left;
	int Pivot = DataSet[First];

	++Left;

	while (Left < Right)
	{
		// 기준 값 보다 작은 값을 찾는다
		while (DataSet[Left] <= Pivot)
		{
			++Left;
		}

		// 기준 값보다 큰 값을 찾는다
		while (DataSet[Right] > Pivot)
		{
			--Right;
		}

		// 기준값 보다 큰 값의 위치가 작은 값의 위치보다 오른쪽에 있으면 서로 교환.
		if (Left < Right)
		{
			Swap(&DataSet[Left], &DataSet[Right]);
		}
		else
		{
			break;
		}
	}

	// 기준 값을 이동 시킴.
	Swap(&DataSet[First], &DataSet[Right]); 

	// 기준 값이 이동된 인덱스를 리턴
	return Right;
}

void QuickSort(int DataSet[], int Left, int Right)
{
	if (Left < Right)
	{
		int Index = Partition(DataSet, Left, Right);

		QuickSort(DataSet, Left, Index - 1);
		QuickSort(DataSet, Index + 1, Right);
	}
}

int main(void)
{
	int DataSet[] = {6,4,2,3,1,5};
	int Length = sizeof DataSet / sizeof DataSet[0];
	int i = 0;

	QuickSort(DataSet, 0, Length - 1);

	for (i=0; i<Length ; i++)
	{
		printf("%d", DataSet[i]);
	}

	printf("\n");

	return 0;

}