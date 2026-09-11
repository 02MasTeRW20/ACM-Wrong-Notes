// https://codeforces.com/contest/2260/problem/D
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

pii get(char c)
{
    if (c == '+')
    {
        return {4, 6}; // 1 2 3
    }
    else if (c == '-')
    {
        return {0, 2}; // -3 -2 -1
    }
    else
    {
        return {3, 3}; // 0
    }
}

void _MasTeRW_()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<vector<int>> dp(n + 1, vector<int>(7, INF));
    // dp[i][j]  中 j - k 代表 -3～3，就是前缀和 3->0
    // dp[i][j] = 第 i 个位置及以前的最小的值
    dp[0][3] = 0;
    for (int i = 0; i < n; i++)
    {
        auto [l, r] = get(s[i]);
        for (int j = 0; j < 7; j++)
        {
            if (dp[i][j] == INF)
                continue;
            for (int k = l; k <= r; k++)
            {
                // 这个是 i + 1 的前缀和的范围

                if (j == k)
                    continue;
                dp[i + 1][k] = min(dp[i + 1][k], max(dp[i][j], abs(j - k)));
            }
        }
    }
    int res = *min_element(all(dp[n]));
    if (res == INF)
    {
        cout << -1 << endl;
        return;
    }
    cout << res << endl;
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