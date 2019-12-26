package git.src.main;
import java.util.Arrays;
import git.src.stack.Stack;
public class Java11 {
	private static Stack<Character> shu = new Stack<>();
	private static Stack<Character> fu = new Stack<>();
	static char[] chars = "(1+2)-2*(4-1)+6/3".toCharArray();
	public static void main(String[] args) {
		for (int i = 0; i < chars.length; i++) {
			char ch = chars[i];
			switch (ch) {
				case '+':fu.push(chars[i]);break;
				case '-':fu.push(chars[i]);break;
				case '*':fu.push(chars[i]);break;
				case '/':fu.push(chars[i]);break;
				case '(':fu.push(chars[i]);break;
				case ')':
					while (fu.peek() != '(') {
						shu.push(fu.pop());
					}
					if ((char) fu.peek() == '(') {
						fu.pop();
					}
					while (fu.size != 0) {
						if (fu.peek() == '*' || fu.peek() == '/') {
							shu.push(fu.peek());
							fu.pop();
						} else {
							break;
						}
					}
				break;
				default:shu.push(chars[i]);break;
			}
		}
		System.out.println("只支持个位数操作,不支持小数点不支持负数!");
		System.out.println("原字符串：" + Arrays.toString(chars) );
		while (fu.size != 0) {
			shu.push(fu.pop());
		}

		System.out.println("进栈顺序：" + shu);
		shu = Reverse(shu);//出栈
		System.out.println("结果: "+JiSuan(shu));
	}

	public static int JiSuan(Stack<Character> stack) {
		Stack<Integer> temp = new Stack<>();// 存放后缀表达式的操作数的栈
		while (stack.size != 0) {
			char ch = stack.peek();
			switch (ch) {
				case '+':case '-':case '*':case '/':case '(':case ')':
					temp.push(op(ch,temp.pop(),temp.pop()));stack.pop();break;
					default:temp.push(Integer.valueOf(String.valueOf(stack.pop())));break;
			}
		}
		return temp.peek();
	}

	private static int op(char ch, Integer o2, Integer o1) {
		int res = 0;
		switch (ch) {
			case '+':res = o1+o2;break;
			case '-':res = o1-o2;break;
			case '*':res = o1*o2;break;
			case '/':res = o1/o2;break;
		}
		return res;
	}
	public static Stack<Character> Reverse(Stack<Character> shu) {
		Stack<Character> reverseStack = new Stack<>();
		while (shu.size != 0) {
			reverseStack.push(shu.pop());
		}
		System.out.println("出栈顺序,后缀表达式：" + reverseStack);
		return reverseStack;
	}
}