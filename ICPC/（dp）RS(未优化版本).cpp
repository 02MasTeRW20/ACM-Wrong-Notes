// https://qoj.ac/contest/4071/problem/20029
// 这是一个未优化版本，故名思义，就是用最暴力的方式来算出答案
// 优化版本是加了 CDQ 分治的版本，但最主要的是这个 dp 我其实也没想到可以这样写
// 最核心的是这个公式的转换和这个 dp 的递推式

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

void _MasTeRW_()
{
    int n;
    cin >> n;
    vector<int> r(n + 1), b(n + 1), y(n + 1);

    for (int i = 1; i <= n; i++)
    {
        cin >> r[i] >> y[i] >> b[i];
    }

    for (int i = 0; i < n; i++)
    {
        r[i + 1] += r[i];
        y[i + 1] += y[i];
        b[i + 1] += b[i];
    }
    // 三个颜色前缀和

    vector<int> A(n + 1), B(n + 1);
    // A[i] = r[i] - y[i];
    // B[i] = r[i] - b[i];
    for (int i = 1; i <= n; i++)
    {
        A[i] = r[i] - y[i];
        B[i] = r[i] - b[i];
    }
    // 公式推导
    // A[i] >= A[j], B[i] >= B[j], i >= j <----------------> i ~ j 为红色段

    vector<int> dp(n + 1, INF);
    dp[0] = 0;
    // dp[i] : i 前面的所有非红色段的最小值

    // dp[i] = min(dp[i - 1] + 1, min dp[j]);
    // dp[i - 1] + 1 : i - 1 ~ i 自成一段
    // min dp[j] : 满足以上公式推导的， 中间 i ~ j 为红色段，因此找到最小的 dp[j] 即可
    // ans = n - dp[n]
    for (int i = 1; i <= n; i++)
    {
        int mn = INF;
        for (int j = 0; j < i; j++) // i != j 因为这样子 i ~ j 就是空的，无意义
        {                           // 从 0 开始的原因是 0 ~ i 要满足
            if (A[i] >= A[j] && B[i] >= B[j])
                mn = min(dp[j], mn);
        }
        dp[i] = min(dp[i - 1] + 1, mn);
    }
    cout << n - dp[n] << endl;
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