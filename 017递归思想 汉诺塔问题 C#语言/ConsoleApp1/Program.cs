using System;

namespace ConsoleApp1
{
    #region hanio汉诺塔
//        QQ:582521582
//        QQ群：322085520
//        汉诺塔5层 执行步骤
//        n = 5时候 将n-1从A搬到B 最后一个 直接从A搬到C 
//        此时问题分解成B上n-1个柱子 从B搬到A 最后一个从B搬到C
//        此时又回到最初的状态 A上剩余n-1个柱子 B上没有 最大的一个柱子已经搬到了C
//        那么在程序上是如何表现的呢
//        n = 5是 调用hanio(4,'A','C','B');
//        hanio(3,'A','B','C');
//        loop:hanio(2,'A','C','B');
//        hanio(1,'A','B','C'); 此时开始返回执行 print(A->C);
//        返回到第二层 第二层的hanio(2,'A','C','B');已经接收到了返回 所以会执行print(A->B)
//        接着执行loop:hanio(2,'C','A','B')
//        再次调用 hanio(1,'C','B','A') 执行print(C-A); 注意这个loop是递归调用下去的
//        不着急返回 先要执行完下面的print和hanio()；
//        此时的loop:hanio(2,'A''C','B')已经执行完成 才返回给hanio(3,'A','B','C')；
//        此时接着重复上述的步骤 hanio(3,'A','B','C')接受到hanio(2)的返回 就执行下一步 A->C
//        然后在执行hanio(3,'B','A','C') 注意这个问题 又要划分子问题成为 重复的子问题
//        移动次数为 2^n -1 
    #endregion
    public class Program
    {
        private static long count = 0;
        static void Hanio(int n ,char from,char to,char p)
        {
            if (n == 1)
            {
                Console.WriteLine("{0} -> {1}", from, p);
                count++;
            }
            else
            {
                Hanio(n - 1, from, p, to);
                Console.WriteLine("{0} -> {1}", from, p);
                count++;
                Hanio(n-1,to,from,p);
            }
        }
        private static void Main()
        {
            Hanio(n:10,from:'A',to:'B',p:'C');
            Console.WriteLine("移动完毕 移动次数 {0} 次",count);
            Console.ReadKey();
        }
    }
}
