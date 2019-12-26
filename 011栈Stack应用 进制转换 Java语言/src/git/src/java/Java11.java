package git.src.java;

import git.src.stack.Stack;

import java.util.Scanner;

public class Java11{
    public static void main(String[] args) {
        Stack<Object> stack = new Stack<>();
        stack.setAddMaxSize(1024);
        System.out.println("输入一个10进制数: ");
        int D = new Scanner(System.in).nextInt();
        System.out.println("输入需要转换的进制数: ");
        int Hexadecimal = new Scanner(System.in).nextInt();
        while (D!=0) {
            if (Hexadecimal >=10) {
                switch (D%16){
                    case 10:stack.push('A');break;
                    case 11:stack.push('B');break;
                    case 12:stack.push('C');break;
                    case 13:stack.push('D');break;
                    case 14:stack.push('E');break;
                    case 15:stack.push('F');break;
                    default:stack.push(D%16);break;
                }
            }else{
                stack.push(D%Hexadecimal);
            }
            D /=Hexadecimal;
        }
        System.out.println(stack);
    }
}