// https://qoj.ac/contest/4071/problem/20019
// 这道题需要观察力惊人
// 第一次看题目吧题目的要求理解错了，第二次才看懂，题目很难读懂，在此看的时候要注意
// pi 实际上是随便排的，但是要满足有解的情况才可以
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define ll long long
#define fl float
#define dl double
#define pii pair<int, int>
#define lowbit(x) (x & -x)
#define all(x) x.begin(), x.end()
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
template <typename K, typename V>
using UMAP = unordered_map<K, V, custom_hash>;
const int INF = 1e18;
const int N = 2e5 + 10;
const int MOD = 998244353;

void _MasTeRW_()
{
    int n;
    cin >> n;
    vector<int> p(n + 1);
    UMAP<int, int> mp;

    for (int i = 1; i <= n; i++)
        cin >> p[i], mp[p[i]]++;
    // mp[p[i]] 记录的是 p[i] 这个元素的需求，由于 pi 可以随便排序，因此只需记录个数即可
    int s1 = 0, s0 = 0;
    // 前面 1 的个数 和 前面 0 的个数

    int res = 1;
    // 答案
    for (int i = 1; i <= n; i++)
    {
        if (s0 == s1)
            res = (res * 2) % MOD;
        // 如果前面的 0 1 个数相同，说明在此时的这个格子
        // 放 0 和放 1 的影响都是一样的，所以放其中任意一个都可以，因此答案乘 2

        if (mp[s1] > 0)
            mp[s1]--, s0++; // 如果此时前面 s1 在我的需求当中，那我就在这个位子上补充 0
                            //因为题目要求的是该位与前面不同的个数为 pi 
                            // 那么就多一个 s0，少一个 s1 的需求
        else
            mp[s0]--, s1++; // 同理
    }
    cout << res << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    // cin >> T;
    while (T--)
        _MasTeRW_();
    return 0;
}