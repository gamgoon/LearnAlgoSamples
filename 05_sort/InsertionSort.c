#include <stdio.h>
#include <string.h>

void InsertionSort(int DataSet[], int Length)
{
	int i = 0;
	int j = 0;
	int value = 0;

	for (i=1;i<Length;i++)
	{
		// i 가 매 반복마다 추가될 비교 대상
		// 매 방복시 이전의 DataSet 은 이미 정렬이 된 상태기에
		// 바로 앞의 값과 비교해 DataSet[i]보다 작으면 더이상 비교할 필요가 없음.
		if (DataSet[i-1] <= DataSet[i])
		{
			continue;
		}

		value = DataSet[i];

		for (j=0;j<i;j++)
		{
			if (DataSet[j] > value)
			{
				memmove(&DataSet[j+1], &DataSet[j], sizeof(DataSet[0]) * (i-j));
				DataSet[j] = value;
				break;
			}
		}
	}
}

int main(void)
{
	int DataSet[] = {6,4,2,3,1,5};

	int Length = sizeof DataSet / sizeof DataSet[0];
	int i = 0;

	InsertionSort(DataSet, Length);

	for (i = 0; i<Length; i++)
	{
		printf("%d ", DataSet[i]);
	}

	printf("\n");

	return 0;
}