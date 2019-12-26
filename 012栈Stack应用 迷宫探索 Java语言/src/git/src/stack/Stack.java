package git.src.stack;

public class Stack<T> {
    private class ListElement<E>{
        E data = null;
        ListElement<E> next = null;
    }
    private ListElement<T> head = null;
    private int size = 0;
    private int maxSize = 128;
    public void push(T data) {
        if(getSize()>=getMaxSize()) {
            try {
                throw new Exception();
            } catch (Exception e) {
                System.err.print("\n栈已达最上限! ");
                return;
            }
        }
        ListElement<T> new_element = new ListElement<>();
        new_element.data = data;
        new_element.next = head;
        head = new_element;
        size++;
    }
    public T pop(){
        T dataT = head.data;
        head.data = null;
        System.gc();
        if(getSize() == 0) {
            try {
                throw new Exception();
            } catch (Exception e) {
                System.out.println("栈空");
                e.printStackTrace();
            }
        }
        head = head.next;
        size--;
        return dataT;
    }

    public T peek() {
        return head.data;
    }
    public boolean isEmpty() {
        return null == head;
    }
    @Override
    public String toString() {
        StringBuilder sBuilder = new StringBuilder();
        ListElement<T> elmt = head;
        while (elmt!=null) {
            sBuilder.append(elmt.data).append(" ");
            elmt = elmt.next;
        }
        return sBuilder.toString();
    }
    public int getSize() {
        return size;
    }

    public int getMaxSize() {
        return maxSize;
    }
    public void setAddMaxSize(int addSize) {
        if (addSize < 0) {
            try {
                throw new Exception();
            }catch (Exception e){
                System.err.print("\naddSize不可以低于0 ");
                e.printStackTrace();
            }
        }
        this.maxSize += addSize;
    }
}
