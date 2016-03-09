#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NameCard.h"

// NameCard 구조체 변수의 동적 할당 및 초기화 후 주소 값 반환
NameCard* MakeNameCard(char* name, char* phone)
{
  NameCard* nameCard = (NameCard*)malloc(sizeof(NameCard));
  strcpy(nameCard->name, name);   // strcpy 활용. 문자열 복사.
  strcpy(nameCard->phone, phone);
  return nameCard;
}

// NameCard 구조체 변수의 정보 출력
void ShowNameCardInfo(NameCard* pcard)
{
  printf("name: %s, phone: %s \n", pcard->name, pcard->phone);
}

// 이름이 같으면 0, 다르면 0이 아닌 값 반환
int NameCompare(NameCard* pcard, char* name)
{
  return strcmp(pcard->name, name);   // strcmp 활용. 문자열 비교
}

// 전화번호 정보를 변경
void ChangePhoneNum(NameCard* pcard, char* phone)
{
  strcpy(pcard->phone, phone);
}
