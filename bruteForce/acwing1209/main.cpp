/**1209. 带分数
 * https://www.acwing.com/problem/content/description/1211/
   题目
   提交记录
   讨论
   题解
   视频讲解

100 可以表示为带分数的形式：100=3+69258714
还可以表示为：100=82+3546197
注意特征：带分数中，数字 1∼9 分别出现且只出现一次（不包含 0）。

类似这样的带分数，100 有 11 种表示法。
*/
#include <iostream>

using namespace std;

//  数组大小为十是为了通过索引1～9能直接访问
int nums[10], cnt = 0;
bool used[10];

// [l, r]
int calc(int l, int r) {
    int res = 0;
    for (int i = l; i <= r; i++) {
        res = res * 10 + nums[i];
    }
    return res;
}

void travel (int used_num, int tar) {
    if (used_num == 9) {
        // 共9个数，所以index为 [0 ~ 8]
        // 分为[0, i] [i+1, j] [j +1, 8]
        for (int i = 0; i < 7; i ++) {  //  i [0 ~ 7]
            for (int j = i +1; j < 8; j ++) {
                //  a + b / c = target
                int a = calc(0, i), b = calc(i +1, j), c = calc(j + 1, 8);

                if (a * c + b == tar * c) cnt ++;
            }
        }
        return;
    }

    //  使用到的数字未齐全，继续向nums中添加数字
    for (int i = 1; i <= 9; i ++) {
        if (!used[i]) {
            used[i] = true;
            nums[used_num] = i;
            travel(used_num + 1, tar);
            used[i] = false;
        }
    }
}

int main() {
    int tar;
    cin >> tar;
    travel(0, tar);
    cout << cnt;


}