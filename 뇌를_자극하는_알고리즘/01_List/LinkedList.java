
/**
 * JDK의 LinkedList 구현을 둘러보자
 * 당연히 사용하기만 하면 되던 것들의 구현을 생각해보려니 쉽진 않구나...
 */
public class LinkedList<E> 
	extends AbstractSequentialList<E> 
	implements List<E>, Deque<E>, Cloneable, java.io.Serializable {
	
	transient int size = 0;

	transient Node<E> first;

	transient Node<E> last;

	public LinkedList() {
	}

	public LinkedList(Collection<? extends E> c) {
		this();
		addAll(c);
	}

	private void linkFirst(E e) {
		final Node<E> f = first;
		final Node<E> newNode = new Node<>(null, e, f); // 신규 노드 생성,(기존 first 노드를 next로 가지는)
		first = newNode;
		if (f == null) { // 기존에 빈 리스트 였다면
			last = newNode;
		} else {
			f.prev = newNode;
		}
		size++;
		modCount++;
	}

	void linkLast(E e) {
		final Node<E> l = last;
		final Node<E> newNode = new Node<>(l, e, null);
		last = newNode;
		if (l == null) {
			first = newNode;
		}else {
			l.next = newNode;
		}
		size++;
		modCount++;
	}

	void linkBefore(E e, Node<E> succ) {
		final Node<E> pred = succ.prev;
		final Node<E> newNode = new Node<>(pred, e, succ);
		succ.prev = newNode;
		if (pred == null) {
			first = newNode;
		} else {
			pred.next = newNode;
		}
		size++;
		modCount++;
	}

	E unlink(Node<E> x) {
		final E element = x.item;
		final Node<E> next = x.next;
		final Node<E> prev = x.prev;

		if (prev == null) {
			first = next;
		} else {
			prev.next = next;
			x.prev = null;
		}

		if (next == null) {
			last = prev;
		} else {
			next.prev = prev;
			x.next = null;
		}

		x.item = null;
		size--;
		modCount++;
		return element;
	}

	public boolean addAll(Collection<? extends E> c) {
		return addAll(size, c);
	}

	public boolean addAll(int index, Collection<? extends E> c) {
		checkPositionIndex(index); // 인덱스의 유효성 체크, IndexOutOfBoundsException 발생

		Object[] a = c.toArray();
		int numNew = a.length;
		if (numNew == 0) {
			return false;
		}

		Node<E> pred, succ;
		if (index == size) { // 테일로 추가되는 경우
			succ = null;
			pred = last;
		} else {	// 중간에 삽입 되는 경우
			succ = node(index);
			pred = succ.prev;
		}

		// pred 를 기준으로 (없으면 신규) Collection c 의 엘리먼트를 하나씩 리스트에 붙인다. 
		for (Object o : a) {
			E e = (E) o;
			Node<E> newNode = new Node<>(pred, e, null);
			if (pred == null) {
				first = newNode;
			} else {
				pred.next = newNode;
			}
			pred = newNode;
		}

		if (succ == null) {
			last = pred;
		} else {
			pred.next = succ;
			succ.prev = pred;
		}

		size += numNew;
		modCount++; // http://stackoverflow.com/questions/11042552/what-does-the-modcount-variable-when-debugging-the-collection?answertab=active#tab-top
		return true;
	}

	public void clear() {
		for (Node<E> x = first; x != null; ) {
			Node<E> next = x.next;
			x.item = null;
			x.next = null;
			x.prev = null;
			x = next;
		}
		first = last = null;
		size = 0;
		modCount++;
	}

	public E get(int index) {
		checkElementIndex(index);
		return node(index).item;
	}

	public E set(int index, E element) {
		checkElementIndex(index);
		Node<E> x = node(index);
		E oldVal = x.item;
		x.item = element;
		return oldVal; // 이전 값을 리턴
	}

	public void add(int index, E element) {
		checkPositionIndex(index);

		if (index == size) {
			linkLast(element);
		} else {
			linkBefore(element, node(index));
		}

	}

	public E remove(int index) {
		checkElementIndex(index);
		return unlink(node(index));
	}

	Node<E> node(int index) {
		// index 의 위치에 따라 앞 또는 뒤에서 탐색
		if (index < (size >> 1)) {
			Node<E> x = first;
			for (int i = 0; i < index ; i++) {
				x = x.next;
			}
			return x;
		} else {
			Node<E> x = last;
			for (int i = size; i > index ; i--) {
				x = x.prev;
			}
			return x;
		}
	}

	private static class Node<E> {
		E item;
		Node<E> next;
		Node<E> prev;

		Node(Node<E> prev, E element, Node<E> next) {
			this.item = element;
			this.next = next;
			this.prev = prev;
		}
	}

	public Object[] toArray() {
		Obejct[] result = new Object[size];
		int i = 0;
		for (Node<E> x = first; x != null ; x = x.next ) {
			result[i++] = x.item;
		}
		return result;
	}
}