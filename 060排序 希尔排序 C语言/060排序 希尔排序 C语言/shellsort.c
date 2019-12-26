/* 数据结构
 * 希尔排序
 * 希尔排序有几个重要的结论
 * 1：每次缩小增量进行直接插入排序的时候
 * 绝对不影响上一层缩小增量排过序的结果 每次做缩小增量排序 实质上也是调整逆序对的问题
 * 2：希尔排序目的是解决直接插入排序在大量数据和基本无序的情况下效率不佳的问题
 * 但是也带来了2点负面影响 一个是希尔排序变成了不稳定排序 第二个是最坏情况下
 * 希尔排序的每一次缩小增量排序什么也没做 是无用功 结果反而还不如直接插入排序效率来的高
 * 3：希尔排序的平均时间复杂度是一个世界性难题 目前数学学科还无法证明出希尔排序的复杂度
 * 只能得出一个大概的范围是O(n^1.3-2) 所以网上说的平均O(n^2)复杂度纯属瞎扯淡！
 *
 * */
#include <stdio.h>
#define len(arr) ((int)(sizeof(arr)/sizeof(arr[0])))
int main(int argc, char *argv[])
{
      int arr[] = {18,188,3,9,29,5,1,4,7,6,2,0};
      for (int gap = len(arr)/2; gap >=1 ; gap/=2) {
          for (int i = gap; i < len(arr); ++i) {
              for (int j = i-gap; j>=0&&arr[j]>arr[j+gap];j=j-gap) {
                  arr[j] = arr[j]+arr[j+gap]-(arr[j+gap]=arr[j]);
              }
          }
      }
      for (int i = 0; i < len(arr); ++i) {
          printf("%d ",arr[i]);
      }
    return 0;
}
