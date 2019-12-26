package git.src.java;

import java.util.*;

public class J11{
    private static int[] func(int[] scroe, int[] result, int count) {
        if (count != -1) {
            scroe[count] = new Random().nextInt(101);
            result[scroe[count] == 100 ? 9 : scroe[count] / 10]++;
            func(scroe, result, count - 1);
        }
        return result;
    }
    private static int func1(int num, int sum, int i) {
        return num == 0 ? sum : func1(num - 1, sum *= i, i + 1);
    }
    private static int func2(int num, int sum, int i, int j) {
        return num == 0 ? sum + i : func2(num - 1, sum + i, i * j, j + 1);
    }
    private static void fun1(int i,int j){
        if(i>9){
            return ;
        }
        if(i<j){
            System.out.println();
            fun1(i+1,1);
            return ;
        }
        System.out.print(i+"*"+j+"="+i*j+" ");
        fun1(i, j+1);
    }
    private static void fun2(int i,int j){
        if(i>9){
            return ;
        }
        if(i<j){
            fun2(i+1,1);
            System.out.println();
            return ;
        }
        fun2(i, j+1);
        System.out.print(i+"*"+j+"="+i*j+" ");
    }
    private static void change(int d, int r) {
        if (d > 0) {
            change(d/r,r);
            print(d % r);
        }
    }
    private static void print(int d) {
        if (d < 10) {
            System.out.print(d+" ");
        }else{
            System.out.print((char)(d - 10 + 'A')+" ");
        }
    }
    public static void main(String[] args) {
        System.out.println("进制转换");
        change(582521582, 16);
        System.out.println();
        change(582521582,8);
        System.out.println();
        System.out.println("99乘法表正序");
        fun1(1,1);
        System.out.println("\n99乘法表逆序");
        fun2(1,1);
        System.out.println("统计50名学生成绩 按分段(0-9,10-19...90-100)填入result数组中");
        System.out.println(Arrays.toString(func(new int[50], new int[10], 50 - 1)));
        System.out.println("求1/1!+1/2!+...1/20!");
        double sum = 0d;
        for (int i = 1; i <= 20; i++) {
            sum += 1.0 / func1(i, 1, 1);
        }
        System.out.println(sum);
        System.out.println("求sum(1!,10!):");
        System.out.println(func2(10, -1, 1, 1));
    }
}