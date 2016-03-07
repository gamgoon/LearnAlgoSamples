#include <stdio.h>
#include "ArrayList.h"

void ListInit(List* plist)
{
  plist->numOfData = 0;
  plist->curPosition = -1;
}

void LInsert(List* plist, LData data)
{
  if (plist->numOfData > LIST_LEN) {
    puts("저장이 불가능합니다.");
    return;
  }

  plist->arr[plist->numOfData] = data;
  plist->numOfData += 1;
}

int LFirst(List* plist, LData* pdata)
{
  if (plist->numOfData == 0) {
    return FALSE;
  }
  plist->curPosition = 0;
  *pdata = plist->arr[plist->curPosition];

  return TRUE;
}

int LNext(List* plist, LData* pdata)
{
  if (plist->curPosition >= plist->numOfData - 1) {
    return FALSE;
  }

  plist->curPosition += 1;
  *pdata = plist->arr[plist->curPosition];

  return TRUE;
}

LData LRemove(List* plist)
{
  // 삭제
  int rpos = plist->curPosition; // 삭제할 데이터의 인덱스 값
  int num = plist->numOfData;
  int i;
  LData rdata = plist->arr[rpos]; // 삭제할 데이터

  for (i = rpos; i < num - 1; i++) {
    plist->arr[i] = plist->arr[i+1];
  }
  plist->curPosition -= 1;
  plist->numOfData -= 1;

  return rdata;
}

int LCount(List* plist)
{
  return plist->numOfData;
}
