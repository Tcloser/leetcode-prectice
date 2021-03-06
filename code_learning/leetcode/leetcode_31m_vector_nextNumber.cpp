#include <iostream>
#include <vector>
#include <algorithm> // 包含reverse

/* -------------------------------------------
 * vector reverse使用
 * 下一个更大数 前一个更小数 从后往前挨个遍历然后翻转的思路很精妙
 * 说不上来为啥
 * ------------------------------------------*/
using namespace std;

void nextPermutation(vector<int>& nums) {
    if(nums.size()<=1)return;
    int length = (int)nums.size();
    for(int i = length-2;i>=0;i--)
    {
        if(nums[i]<nums[i+1])// 两两相邻的比较 找到后面大于前面数的位置
        {
            for(int j = length-1;j>i;j++)// 再从后向前找一个比前面 找到的数值第一个大的元素 因为后面已经有序
            {
                if(nums[j]>nums[i])
                {
                    swap(nums[i],nums[j]);
                    reverse(nums.begin()+i+1,nums.end());
                    return;
                }
            }
            swap(nums[i],nums[i+1]);
            reverse(nums.begin()+i+1,nums.end());
            return;
        }
    }
    // 已经是最大值 翻转为最小值
    reverse(nums.begin(),nums.end());
    
    return;
}


int main()
{
    vector<int> array {1,4,7,5,2,6,1};

    nextPermutation(array);

    return 0;
}