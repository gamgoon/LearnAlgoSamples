#Hash Table

##Hash
- 잘게 쪼개고 다시 뭉쳐서... (뭐.. 의미적으로 그렇다고 생각하자)

##Hash의 용도
- 해시 테이블 : 데이터의 해시 값을 테이블 내의 주소로 이용하는 탐색 알고리즘.
- 암호화 : SHA(Secure Hash Algorithm)
- 데이터 축약 : 길이가 서로 다른 입력 데이터에 대해 일정한 길이의 출력을 만들 수 있다. 커다란 데이터를 '해시'하면 짧은 길이로 축약할 수 있다. 

##Hash Table
- 데이터를 담을 테이블을 미리 크게 확보해 놓은 후 입력받은 데이터를 해시하여 테이블 내의 주소를 계산하고 이 주소에 데이터를 담는 것.

##해시 함수 Hash Function
###나눗셈법 Division Method
- 해시 함수 중 가장 간단한 알고리즘.
- 입력 값을 테이블의 크기로 나누고, 그 '나머지'를 테이블의 주소로 사용.
` 주소 = 입력 값 % 테이블의 크기 `
- 테이블의 크기 n을 소수(Prime Number)로 정하는 것이 테이블 내의 공간을 효율적으로 사용 가능. 특히 2의 제곱수와 거리가 먼 소수를 사용한 해시 함수가 좋은 성는을 낸다.
- 단점 
	- 동일한 주소를 반환할 가능성이 높다 (충돌 Collision)
	- 해시 테이블 내의 일부 지역의 주소들을 집중적으로 반환하는 결과로 데이터들이 한 곳에 모이는 문제가 발생할 가능성이 높다. (클러스터 Cluster)

` **충돌이나 클러스터링의 문제를 완벽하게 제거할 수 있는 해싱 알고리즘은 존재하지 않는다** `

###자릿수 접기 Digits Folding
- 문제를 일으킬 가능성을 줄인 알고리즘 중 하나.
- 숫자를 접다.
```
8129335  // 7자리 숫자
31 = 8 + 1 + 2 + 9 + 3 + 3 + 5  // 각 자릿수를 더하면 새로운 값 31
								// **즉 8129335가 31로 접혔다.**
148 = 81 + 29 + 33 + 5 // 두 자리씩 더하면 148 로 접힌다.
```
- 숫자의 각 자릿수를 더해 해시 값을 만드는 것을 의미.
- 일정한 범위 내의 해시 값을 얻을 수 있다. 
	- 10진수의 경우 모든 수는 각 자리마다 0~9까지의 값을 가질 수 있으니, 7자리 수에 대해 '한 자리씩 접기' 를 하는 경우 최소 0에서 최대 63(9+9+9+9+9+9+9)까지의 해시 값을 얻을 수 있고, '두자리씩 접기' 하는 경우 최소 0에서 최대 306(99+99+99+9)까지의 해시 값을 얻을 수 있다.
- 문자열을 키로 사용하는 해시 테이블에 특히 잘 어울리는 알고리즘이다.
	- 문자열의 각 요소를 ASCII 코드 번호(이 번호는 0~127)로 바꾸고, 이 값들을 각각 더하여 접으면 문자열을 깔끔하게 해시 테이블 내의 주소로 바꿀 수 있다.
	- 해시 테이블의 폐가 문제
		- 해시 테이블의 크기가 12289이고 문자열 키의 최대 길이 10자리라고 한다면, 해시 함수는 10x127=1270이므로 0에서 1270 사이의 주소만을 반환하게 되어 1271~12288 사이의 주소는 전혀 활용되지 않는다. 
		- 테이블의 크기 12289를 2진수로 표현하면 11000000000001 총 14개의 비트. 반면 최대 주소값은 1270 (10011110110) 11비트만 사용. 3개의 비트는 절대 사용되지 않는다.
		- HashValue 를 왼쪽으로 3비트씩 밀어올린 다음 ASCII 코드 번호를 더하면 이론적으로 해시 테이블 내의 모든 주소를 해싱할 수 있다. ==> **이부분은 좀 다시 확인 해봐야겠다.**
		```
		int Hash(KeyType Key, int KeyLength, int TableSize)
		{
			int i = 0;
			int HashValue = 0;

			for (i=0;i<KeyLength;i++)
			{
				HashValue = (HashValue << 3) + Key[i];
			}

			return HashValue % TableSize;
		}
		```
###해시 함수의 한계: 충돌 Collision
- 해시 함수가 서로 다른 입력 값에 대해 동일한 해시 테이블 주소를 반환하는 것.
####충돌 해결하기
1. 개방 해싱 (Open Hashing) : 해시 테이블의 주소 바깥에 새로운 공간을 할당하여 문제를 수습.
2. 폐쇄 해싱 (Closed Hashing) : 주어진 해시 테이블의 공간 안에서 문제를 해결하는 것.

##### 체이닝 Chaining
- 개방 해싱 기반 (폐쇄 주소법)
- 충돌이 발생하면 각 데이터를 해당 주소에 있는 링크드 리스트에 삽입하여 문제를 해결하는 기법.
- 충돌이 일어나면 링크드 리스트에 사슬처럼 주렁주렁 엮는다는 의미로 붙여진 이름.
- 이진 탐색 트리를 이용한 체이닝 구현

#####개방 주소법
- 충돌이 일어날 때 해시 함수에 의해 얻어진 주소가 아니더라도 얼마든지 다른 주소를 사용할 수 있도록 허용하는 충돌 해결 알고리즘.
- 충돌이 일어나면 해시 테이블 내의 새로운 주소를 탐사(Probe)하여 충동된 데이터를 입력하는 방식
- 탐사
	- 선형 탐사 Linear Probing
		- 충돌이 일어나면 현재 주소에서 고정 폭으로 다음 주소로 이동. 또 충돌이 발생하면 또 고정 폭만큼 다음 주소로....
		- 클러스터 현상이 매우 잘 발생. 새로운 주소를 찾기 위해 수행하는 선형 탐사 시간이 길어짐.
	- 제곱 탐사 Quadratic Probing
		- 선형 탐사와 동일하나 다음 주소를 찾기 위한 **고정폭이 제곱수**로 늘어나는 것
		- 첫번째 충돌시 1의 제곱만큼 이동, 두번째 충돌시 2의 제곱 만큼, 세변째는 3의 제곱만큼 .... 이렇게.
		- 이 역시 클러스터가 발생함. 선형 탐사와는 조금 다른... **이유는 충돌이 발생하면 탐사할 위치가 정해져 있기 때문**
		- 충돌 했을 떄 탐사할 새로운 주소에 대한 규칙성을 없애면 된다. (이중해싱)
	- 이중 해싱 Double Hashing
		- 고정 폭 대신 두번째 해싱함수를 이용하여 주소를 얻는 것. 
	- 재해싱 Rehashing
		- 해시 테이블의 여유 공간이 모두 차버려서 발생하는 성능 저하를 해결.
		- 해시 테이블의 크기를 늘리고, 늘어난 해시 테이블의 크기에 맞추어 테이블 내의 모든 데이터를 다시 해싱한다.
		- 통계적으로 해시 테이블의 공간 사용률이 70~80%에 이르면 성능 저하가 나타남.
		- 재해싱 역시 만만치 않은 오버헤드 요구. 따라서 임계치는 75% 정도를 사용하는 것이 보통.

#참고링크
- [memset](http://itguru.tistory.com/104)
- [memcpy](http://itguru.tistory.com/77)
- [strcpy](http://itguru.tistory.com/79)