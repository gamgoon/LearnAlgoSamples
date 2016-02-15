#include "MakingChange.h"
#include <stdio.h>

void GetChange(int Price, int Pay, int CoinUnits[], int Change[], int Size)
{
	int i = 0;
	int ChangeAmount = Pay - Price;

	for (i=0;i<Size;i++) // 해 검사 : 큰 단위 동전부터 작은 단위의 동전까지 필요한 개수를 세면 거스름돈이 완성
	{
		Change[i] = CountCoins(ChangeAmount, CoinUnits[i]); // 해 선택 : 현 단계에서 가능한 한 큰 단위의 동전을 고른다

		ChangeAmount = ChangeAmount - (CoinUnits[i] * Change[i]);
	}
}

int CountCoins(int Amount, int CoinUnit)
{
	int CoinCount = 0;
	int CurrentAmount = Amount;

	while (CurrentAmount >= CoinUnit)
	{
		CoinCount++;
		CurrentAmount = CurrentAmount - CoinUnit;
	}

	return CoinCount;
}

void PrintChange(int CoinUnits[], int Change[], int Size)
{
	int i = 0;

	for (i=0; i<Size; i++)
	{
		printf("%8d원 : %d개\n", CoinUnits[i], Change[i]);
	}
}
