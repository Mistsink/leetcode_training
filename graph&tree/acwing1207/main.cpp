/**
 * 1207. 大臣的旅费
 * https://www.acwing.com/problem/content/1209/
 * 很久以前，T王国空前繁荣。

为了更好地管理国家，王国修建了大量的快速路，用于连接首都和王国内的各大城市。

为节省经费，T国的大臣们经过思考，制定了一套优秀的修建方案，使得任何一个大城市都能从首都直接或者通过其他大城市间接到达。

同时，如果不重复经过大城市，从首都到达每个大城市的方案都是唯一的。

J是T国重要大臣，他巡查于各大城市之间，体察民情。

所以，从一个城市马不停蹄地到另一个城市成了J最常做的事情。

他有一个钱袋，用于存放往来城市间的路费。

聪明的J发现，如果不在某个城市停下来修整，在连续行进过程中，他所花的路费与他已走过的距离有关，在走第x千米到第x+1千米这一千米中（x是整数），他花费的路费是x+10这么多。也就是说走1千米花费11，走2千米要花费23。

J大臣想知道：他从某一个城市出发，中间不休息，到达另一个城市，所有可能花费的路费中最多是多少呢？
 */


//  因为首都到各城市仅有一条路，所以这个图是一棵树
//  通过两次 dfs 找到该树的直径
//  求得最长距离即可得路费

#include <iostream>
#include <vector>

using namespace std;

void dfs (vector<int> &dist, vector< pair<int, int> > *tree, int cur, int pre, int dis) {
    dist[cur] = pre == -1 ? 0 : dis;

    for (int i = 0; i < tree[cur].size(); i ++) {
        int next = tree[cur][i].first;
        if (next != pre) {
            dfs(dist, tree, next, cur, dis + tree[cur][i].second);
        }
    }
}

int main () {
    long n, a, b, c;
    cin >> n;
    //  记录树的各顶点 <node, dis>
    vector< pair<int, int> > vec[n+1];
    //  记录某点到索引点的距离
    vector<int> dist(n+1, -1);

    for (int i = 0; i < n-1; i ++) {
        cin >> a >> b >> c;
        vec[a].push_back(make_pair(b, c));
        vec[b].push_back(make_pair(a, c));
    }


    //  第一次dfs，找到 最远 的点-----也就是叶子节点
    dfs(dist, vec, 1, -1, 0);
    int max_v = 0;
    for (int i = 0; i <= n; i ++)
        if (dist[i] > dist[max_v])
            max_v = i;

    //  恢复状态
    for (int i = 0; i < dist.size(); i ++)
        dist[i] = -1;

    //  从上一个最远的 点出发，找到最远的点
    dfs(dist, vec, max_v, -1, 0);
    max_v = 0;
    for (int i = 0; i <= n; i ++)
        if (dist[i] > dist[max_v])
            max_v = i;


    long max_dis = dist[max_v];
    cout << 10 * max_dis + max_dis * (max_dis + 1) / 2;

}

