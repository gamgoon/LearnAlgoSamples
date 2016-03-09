#ifndef __POINT_H__
#define __POINT_H__

typedef struct _point
{
  int xpos;
  int ypos;
} Point;

void SetPointPos(Point* ppos, int xpos, int ypos);  // Point 변수의 xpos, ypos 값 설정
void ShowPointPos(Point* ppos);                     // Point 변수의 xpos, ypos 정보 출력
/*
 * 두 Point 변수의 멤버 xpos만 같으면 1 반환
 * 두 Point 변수의 멤버 ypos만 같으면 2 반환
 * 두 Point 변수의 멤버가 모두 같으면 0 반환
 * 두 Point 변수의 멤버가 모두 다르면 -1 반환
 */
int PointComp(Point* pos1, Point* pos2);           // 두 Point 변수의 비교

#endif
