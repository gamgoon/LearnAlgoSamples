# tree
## 용어
- Root , Branch , Leaf(Terminal)
- Parent, Children, Sibling
- Path, Length
- Depth, Level, Height
	- Level : 깊이가 같은 노드의 집합
	- Height : 트리의 높이가 가장 깊은 곳에 있는 입 노드까지의 깊이
- Degree (차수)
	- 노드의 차수 : 노드의 자식 노드 개수
	- 트리의 차수 : 트리 내의 노드 중 자식 노드가 가장 많은 노드의 차수

## 트리의 다른 표현법
- Nested Parenthesis
	- 예 : (A(B(C(D(E)(F))))(G(H))(I(J(K))))
- Nested Set
- Indentation

## 노드의 표현
- N-Link : 노드의 차수가 N이라면, 노드가 N개의 링크를 가지고 있는 것. 차수가 노드마다 달라지는 트리엔 적용이 어려움.
- Left Child-Right Sibling : 왼쪽의 자식과 오른쪽의 형제에 대한 포인터를 갖는 구조. 두 개의 포인터만 가짐.

### 이진 트리 (Binary Tree)
- 자료를 담기 위한 자료구조가 아닌 컴파일러나 검색 등에 사용되는 특수 자료구조.
- Full Binary Tree (포화 이진 트리) : leaf을 제외한 모든 노드의 children이 2개씩, leaf 노드들이 모두 같은 깊이에 존재.
- Complete Binary Tree (완전 이진 트리) : 포화 이진 트리의 전 단계. leaf 노드들이 왼쪽부터 차곡차곡 채워진 것이 특징.
	- leaf 노드들 사이에 이빨이 빠져있는 경우는 완전 이진 트리가 될 수 없다.
- Height Balanced Tree (높이 균형 트리) : 루트 노드를 기준으로 왼쪽 하위 트리와 오른쪽 하위트리의 높이가 1이상 차이나지 않는 이진 트리.
- Completely Height Balanced Tree (완전 높이 균형 트리) : 루트 노드를 기준으로 왼쪽 하위 트리와 오른쪽 하위 트리의 높이가 같은 이진 트리.

#### 이진트리의 순회(Traversal)
- 전위 순회 (Preorder Traversal) : 루트 노드부터 잎 노드까지 아래 방향으로 방문
- 중위 순회 (Inorder Traversal) : 왼쪽 하위 트리부터 오른쪽 하위 트리 방향으로 방문 (왼쪽하위->루트->오른쪽하위) - 수식트리 (중위표현식)
- 후위 순회 (Postorder Traversal) : 왼쪽 하위 트리, 오른쪽 하위 트리, 루트 순으로 방문 - 수식트리 (후위표현식)