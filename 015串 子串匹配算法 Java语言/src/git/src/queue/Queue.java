package git.src.queue;
/*
 * 循环队列
 * 
 * */
public class Queue<T> {
	Object[] array = new Object[3];
	int head = 0;
	int tail = 0;
	int size = 0;
	public Queue() {
	}
	public Queue(int maxSize) {
		array = new Object[maxSize];
	}
	public void push(T data) {
		if (tail == array.length) {
			tail = 0;
		}
		array[tail++] = data;
		size++;
	}
	public Object pop() {
		if (size == 0) {
			try {
				throw new Exception();
			} catch (Exception e) {
				System.err.println("队列已空");
			}
		}
		if(head == array.length) {
			head = 0;
		}
		size--;
		return array[head++];
	}
	public Object peek() {
		return array[head];
	}
	public boolean isEmpty() {
		return size == 0;
	}
	public boolean isFull() {
		return size == array.length;
	}
}
