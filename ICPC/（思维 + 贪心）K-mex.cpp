// https://qoj.ac/contest/4113/problem/20246
// 最遗憾的一道题，赛时思路和正确答案的思路完全相同，但是！
// 赛时 O(n^2) 被卡了，一怒之下直接暴走，没想到这个 map 可以用 vector 优化
// 其次是这个小细节，贪心的选择思路，小的塞进去，大的是后考虑的，这点有点瑕疵
// 其余的和标准答案一模一样，也算是有所进步吧

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
    UMAP<int, int> mp;
    for (int i = 1; i <= n; i++)
    {
        int a;
        cin >> a;
        mp[a]++;
    }
    int mex = 0;
    int L = n;
    while (mp.count(mex))
    {
        mp[mex]--;
        L--;
        mex++;
    }
    vector<int> b(L);
    vector<int> c;
    int j = 0;
    for (auto &[x, k] : mp)
    {
        for (int i = 0; i < k; i++)
        {
            b[j] = x;
            j++;
            if (i && c.back() == x + mex)
                continue;
            c.push_back(x + mex);
        }
    }
    int len = b.size();
    UMAP<int, int> res;
    vector<int> val(n + 2);
    for (int k : c)
    {
        if (res.count(k))
            continue;
        fill(val.begin(), val.end(), 0);
        int dmex = mex;
        for (int j = 0; j < len; j++)
        {
            int d1 = k - b[j];
            int d0 = b[j];
            if (d1 < d0)
                swap(d1, d0);
            if (d0 >= mex && d0 <= n && !val[d0])
            {
                val[d0] = 1;
            }
            else if (d1 >= mex && d1 <= n && !val[d1])
            {
                val[d1] = 1;
            }
        }
        while (val[dmex])
        {
            dmex++;
        }
        res[k] = dmex;
    }
    int ans = 0;
    int q;
    cin >> q;
    while (q--)
    {
        int k;
        cin >> k;
        if (res.find(k) == res.end())
            ans ^= mex;
        else
            ans ^= res[k];
    }
    cout << ans << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
        _MasTeRW_();
    return 0;
}