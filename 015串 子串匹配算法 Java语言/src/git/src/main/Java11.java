package git.src.main;

/*
* 串 子串匹配算法
* QQ:582521582
* QQ群: 322085520
* * */
public class Java11{
	public static void main(String[] args) {
		char[] S = "I Love Java And Python".toCharArray();
		char[] T = "Java".toCharArray();
		int findIndex = findStr(S,T,2);//从下标为2的位置开始寻找子串T
		System.out.println(findIndex);
	}

	private static int findStr(char[] s, char[] t, int pos) {
		int i = pos;
		int j = 0;
		if(pos<0||pos>s.length||t.length>s.length) {
			try {
				throw new ArrayIndexOutOfBoundsException();
			} catch (ArrayIndexOutOfBoundsException e) {
				System.err.println("越界"+pos);
			}
		}
		while (i<s.length&&j<t.length) {
			if(s[i++] == t[j++]) {
				continue;
			}else {
				i = i-j+1;
				j = 0;
			}
		}
		if(j == t.length) {
			return i-j;
		}else {
			return 0;
		}
	}
}