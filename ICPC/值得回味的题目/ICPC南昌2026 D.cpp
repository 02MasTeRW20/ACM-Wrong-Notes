#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define ll long long
#define fl float
#define dl double
#define pii pair<int, int>
#define lowbit(x) (x & -x)
#define all(x) x.begin() + 1, x.end()
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
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count()); // rng() 随机数
template <typename K, typename V>
using UMAP = unordered_map<K, V, custom_hash>;
const int INF = 9e18;
const int N = 2e5 + 10;
const int MOD = 998244353;
using ull = unsigned long long;

void _MasTeRW_()
{
    int n, m;
    cin >> n >> m;
    vector<pii> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i].first >> a[i].second;
    sort(all(a));
    vector<int> dp1(m + 1, -1);
    vector<priority_queue<pii>> dp2(m + 1);
    int res = 0;
    for (int i = 1; i <= n; i++)
    {
        auto &[w, c] = a[i];
        if (c > m)
            continue;
        fill(dp1.begin(), dp1.end(), -1);
        if (w == 1)
            dp1[c] = 1;
        for (int j = m; j >= c; j--)
        {
            auto &pq = dp2[j - c];
            while (pq.size() && pq.top().second < w - 1)
                pq.pop();
            if (!pq.size())
                continue;
            dp1[j] = pq.top().first + w;
        }
        for (int j = m; j >= c; j--)
        {
            if (dp1[j] == -1)
                continue;
            dp2[j].push({dp1[j], dp1[j] - w});
            res = max(res, dp1[j]);
        }
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