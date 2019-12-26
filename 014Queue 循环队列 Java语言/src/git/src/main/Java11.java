package git.src.main;

import git.src.queue.Queue;

/*
* 循环队列
* QQ:582521582
* QQ群: 322085520
* * */
public class Java11{
	public static void main(String[] args) {
		Queue<Object> queue = new Queue<Object>();
		queue.push(1);
		queue.push(2);
		queue.push(3);
		queue.push(4);
		queue.push(5);
		System.out.println(queue.pop());
		System.out.println(queue.pop());
		System.out.println(queue.pop());
		System.out.println(queue.pop());
		
		System.out.println(queue.pop());
	}
}