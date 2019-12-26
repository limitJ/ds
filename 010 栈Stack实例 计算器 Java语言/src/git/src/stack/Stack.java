package git.src.stack;
class ListElement<T>{
	public T data = null;
	public ListElement<T> next = null;
}

public class Stack<T> {
	public ListElement<T> head = null;
	public ListElement<T> tail = null;
	public int size = 0;
	public void free(ListElement<T> element) {
		element.data = null;
		element = null;
		System.gc();
	}
	public void push(T data) {
		ListElement<T> new_element = new ListElement<>();
		new_element.data = data;
		if(size == 0) {
			tail = new_element;
		}
		new_element.next = head;
		head = new_element;
		size++;
	}
	public T pop(){
		T dataT = head.data;
		if(size == 0) {
			try {
				throw new Exception();
			} catch (Exception e) {
				System.out.println("Õ»¿Õ");
				e.printStackTrace();
			}
		}
		head = head.next;
		if(size == 1) {
			tail = null;
		}
		size--;
		return dataT;
	}
	public T peek() {
		return head.data;
	}
	@Override
	public String toString() {
		StringBuilder sBuilder = new StringBuilder();
		ListElement<T> elmt = head;
		while (elmt!=null) {
			sBuilder.append(elmt.data+" ");
			elmt = elmt.next;
		}
		return sBuilder.toString();
	}
}
