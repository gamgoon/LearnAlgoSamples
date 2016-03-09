#include <stdio.h>
#include <stdlib.h>
#include "NameCard.h"
#include "ArrayListNameCard.h"

int main(void)
{
  List list;

  NameCard* nameCard;

  ListInit(&list);

  // 총 3명의 전화번호 정보를, 앞서 우리가 구현한 리스트에 저장한다.
  nameCard = MakeNameCard("gamgoon", "1111111");
  LInsert(&list, nameCard);

  nameCard = MakeNameCard("gamgoon2", "2222222");
  LInsert(&list, nameCard);

  nameCard = MakeNameCard("gamgoon3", "3333333");
  LInsert(&list, nameCard);

  // 특정 이름을 대상으로 탐색을 진행하여, 그 사람의 정보를 출력한다.
  if (LFirst(&list, &nameCard)) {
    if (NameCompare(nameCard, "gamgoon") == 0) {
      ShowNameCardInfo(nameCard);
    }

    while (LNext(&list, &nameCard))
    {
      if (NameCompare(nameCard, "gamgoon") == 0)
      {
        ShowNameCardInfo(nameCard);
        break;
      }
    }
  }

  // 특정 이름을 대상으로 탐색을 진행하여, 그 사람의 전화번호 정보를 변경한다.
  if (LFirst(&list, &nameCard)) {
    if (NameCompare(nameCard, "gamgoon2") == 0) {
      ChangePhoneNum(nameCard, "99999");
    }

    while (LNext(&list, &nameCard))
    {
      if (NameCompare(nameCard, "gamgoon2") == 0)
      {
        ChangePhoneNum(nameCard, "99999");
        break;
      }
    }
  }

  ShowNameCardInfo(nameCard);

  // 특정 이름을 대상으로 탐색을 진행하여, 그 사람의 정보를 삭제한다.
  if (LFirst(&list, &nameCard)) {
    if (NameCompare(nameCard, "gamgoon3") == 0) {
      nameCard = LRemove(&list);
      free(nameCard);
    }

    while (LNext(&list, &nameCard))
    {
      if (NameCompare(nameCard, "gamgoon3") == 0)
      {
        nameCard = LRemove(&list);
        free(nameCard);
        break;
      }
    }
  }

  // 이런 오류가 계속 나는데 도저히 못 찾겠네;;;
  // namecardtest(63399,0x7fff767c7000) malloc: *** error for object 0x63c03260: pointer being freed was not allocated
  // *** set a breakpoint in malloc_error_break to debug
  // [1]    63399 abort      ./namecardtest

  printf("현재 데이터의 수: %d \n", LCount(&list));

  // 끝으로 남아있는 모든 사람의 전화번호 정보를 출력한다.
  if (LFirst(&list, &nameCard )) {
    ShowNameCardInfo(nameCard);
    while (LNext(&list, &nameCard)) {
      ShowNameCardInfo(nameCard);
    }
  }

  return 0;
}
