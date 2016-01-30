#버블정렬 Bubble sort
- 정렬 대상을 하나씩 줄여나간다.
- 집합의 범위를 n개, n-1 만큼 반복 (순회)
- 비교 횟수 : n(n-1)/2

#삽입 정렬 Insertion sort
- 정렬 대상을 하나씩 늘려나가는 방식
- 비교 횟수 : 최악 n(n-1)/2 , 최선 n-1 , 평균 (n^2+n-2)/2
- 평균적으로는 삽입 정렬이 버블 정렬보다 더 나은 성능을 보인다.

#memmove
- [memmove() 메모리 영역 복사, 자기 영역도 가능](http://forum.falinux.com/zbxe/index.php?document_srl=408167&mid=C_LIB)