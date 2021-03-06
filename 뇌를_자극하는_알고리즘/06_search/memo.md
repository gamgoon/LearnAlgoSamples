#Search
##순차 탐색 Sequential Search
- 선형 탐색 Linear Search 이라고 부르기도 한다.
- 처음부터 끝까지 모든 요소를 검사
- 비효율
- 정렬되지 않은 데이터 집합 속에서 원하는 데이터를 찾을 수 있는 유일한 방법
- 높은 성능을 필요로 하지 않거나 데이터 집합의 크기가 작은 곳에 사용.

###자기 구성 순차 탐색 Self-Organizing Sequential Search
- 자주 사용되는 항목을 데이터 집합의 앞쪽에 배치함으로써 순차 탐색의 검색 효율을 끌어올리는 방법
- 자주 사용되는 항목을 어떻게 선별하는가
	- 전진 이동법(Move To Front)
	- 전위법(Transpose)
	- 빈도 계수법(Frequency Count)

####전진 이동법
- 한번 탐색된 항목을 데이터 집합의 가장 앞에 위치시킴.
- 한번 찾은 항목을 연이어 또 찾는 경우 단번에 탐색 완료.
- 한번 탐색된 항목이 곧 이어서 또 다시 검색될 가능성이 높은 데이터 집합에서만 사용

####전위법
- 탐색된 항목을 바로 이전 항목과 교환
- *자주* 탐색된 항목을 점진적으로 앞으로 옮긴다.

####계수법
- 데이터 집합 내의 각 요소들이 탐색된 횟수를 별도의 공간에 저장.
- 탐색된 횟수가 높은 순으로 데이터 집합을 재구성하는 전략.
- 전위법은 가장 뒤에 있는 데이터가 가장 많은 선택을 받더라도 데이터 집합의 크기가 크면 가장 앞에 올 수 있다는 보장을 받을 순 없다.
- 계수 결과를 저장하는 별도의 공간을 유지해야 하고 계수 결과에 따라 데이터 집합을 재배치해야 하는 비용이 소요됨

##이진 탐색 Binary Search
- 정렬된 데이터 집합에서 사용할 수 있는 *고속* 탐색 알고리즘
- 탐색 범위를 1/2씩 줄여나가는 방식
- 데이터 집합이 배열인 경우에만 사용. => 동적으로 크기가 달라지는 데이터 집합에는 이진 탐색 트리 이용
- c표준 라이브러리의 이진 탐색 함수 : bsearch()

###성능 측정
- 데이터 집합의 크기를 n , 탐색 반복 횟수를 x 라고 한다면, 마지막 데이터 범위의 크기 1은 n 에 1/2의 x제곱을 곱한 값과 같다.

$$1 = n * (1/2)^x$$
$$1 = n * 1/2^x$$
$$2^x = n$$
$$x = log_2n$$

##이진 탐색 트리 Binary Search Tree
- 각 노드는 *왼쪽 자식 노드는 나보다 작고, 오른쪽 자식 노드는 나보다 크다.* 는 규칙을 따른다.
- 노드 삭제
	- 삭제 대상 노드의  자식 노드가 있는 경우
		- 양쪽 자식 노드를 모두 갖고 있는경우
			- 삭제된 노드의 오른쪽 하위 트리에서 가장 작은 값을 가진 노드(최소값 노드)를 삭제된 노드의 위치에 옮겨 놓는다.
			- 옮겨 놓은 '최소값 노드'가 자식이 있는 경우
				- 최소값 노드는 오른쪽 자식만 있으므로, 이 오른쪽 자식을 최소값 노드의 원래 부모에게 연결해준다.
		- 왼쪽 또는 오른쪽 중 어느 한쪽 노드만 갖고 있는 경우
			- 삭제되는 노드의 자식을 삭제되는 노드의 부모에게 연결

##레드 블랙 트리 Red Black Tree
- 잎 노드는 모두 NIL로 표시. NIL 노드는 아무 데이터도 갖고 있지 않지만 색깔만 검은색인 더미 노드이다.
- 규칙
	1. 모든 노드는 빨간색 아니면 검은색이다.
	2. 루트 노드는 검은색이다.
	3. 잎 노드는 검은색이다.
	4. 빨간 노드의 자식들은 모두 검은색이다. 하지만 검은색 노드의 자식이 빨간색일 필요는 없다.
	5. 루트 노드에서 모든 잎 노드 사이에 있는 검은색 노드의 수는 모두 동일하다.
- 기본 연산
	- NIL 노드는 한 개만 전역으로 생성해서 새 노드를 생성할 때마다 동일한 Nil 노드를 사용.
	- 회전
		- 우회전을 할 때에는 왼쪽 자식 노드의 오른쪽 자식 노드를 부모 노드의 왼쪽 자식으로 연결.
		- 좌회원을 할 때에는 오른쪽 자식 노드의 왼쪽 자식 노드를 부모 노드의 오른쪽 자식으로 연결.
	- 삽입
		- 삽입 된 노드를 빨간색으로 칠한 다음 양쪽 자식에 NIL 노드를 연결.
		- 무너진 레드 블랙 트리의 규칙을 복구.
			- *빨간 노드의 자식들은 모두 검은 색이다* 규칙이 위배됨. 즉 새로운 노드가 빨간색 노드 빝에 붙는 경우.
			- 3가지 경우 (부모노드가 할아버지 노드의 왼쪽 자식일 경우 : 오른쪽 자식인 경우는 아래의 왼쪽/오른쪽을 바꿔주면 됨.)
				- 삼촌도 빨간색인 경우
					- 부모 노드와 삼촌 노드를 검은색으로 칠하고, 할아버지 노드를 빨간색으로 칠한다.
					- 다시 할아버지 노드를 새로 삽인한 노드로 간주하고 다시 규칙위반 경우를 따져본다.
					- 부모노드가 검은색이거나 새로 삽입한(새로 삽입한 것으로 간주한) 노드가 루트여야 끝남.
				- 삼촌이 검은색이며 새로 삽입한 노드가 부모 노드의 오른쪽 자식인 경우
					- 부모 노드를 왼쪽으로 회전시켜 이 상황을 아래의 세번째 경우의 상황으로 바꾼다.
				- 삼촌이 검은색이며 새로 삽입한 노드가 부모 노드의 왼쪽 자식인 경우
	- 삭제
		- 기본적인 이진 탐색 트리의 삭제 방법과 동일
		- 이후 레드 블랙 트리의 규칙 위반을 따져본다.
		- *삭제한 노드가 빨간색인 경우에는 어떤 뒷처리도 할 필요가 없다*
		- 검은색 노드를 삭제하는 경우 규칙 5번(루트 노드에서 모든 잎 노드 사이에 있는 검은색 노드의 수는 모두 동일)에 위배됨.
		- 삭제한 노드의 부모와 삭제한 노드의 자식이 모두 빨간색인 경우 규칙 4번도 위배
		- 무너진 두가지 규칙을 보완하는 방법
			- *삭제된 노드를 대체하는 노드를 검은색으로 칙한다*
			- 문제는 삭제한 노드를 대체하는 노드가 검은 색이라면?
				- 규칙 4를 위배하진 않지만, 5번 규칙을 위반하게 된다. 또한 이미 검은색 노드라 5번 규칙을 보완하는 방법은???
				- 대체 노드(이미 검은색인)를 검은색으로 덧칠한다.
				- *예외적으로 검은색을 '두개' 가지게 하므로써 규칙 5를 복원한다.* => '이중흑색'노드
				- 그런데 '이중흑색'은 규칙 1의 모든 노드는 빨간색 아니면 검은색이어야 하는 규칙에 위배된다고 한다. 즉 '이중흑색'노드는 빨간색도 검은색도 아닌 색임.
				- 색깔은 개념적인 표현이며, 무너진 규칙 5번을 규칙 1번이 무너진 것으로 간주함으로써 문제를 더 풀기 쉬운 상태로 만들기 위한 도구.
				- *이중 흑색 노드*의 처리 방법* (이중 흑색 노드가 부모 노드의 왼쪽 자식인 경우. 오른쪽 자식의 경우에는 아래의 왼쪽/오른쪽만 바꾸면 된다.)
					- 형제가 빨간색인 경우
					- 형제가 검은색이고
						- 형제의 양쪽 자식이 모두 검은색인 경우
						- 형제의 왼쪽 자식은 빨간색, 오른쪽 자식은 검은색인 경우
						- 형제의 오른쪽 자식이 빨간색인 경우