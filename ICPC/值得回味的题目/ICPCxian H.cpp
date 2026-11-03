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
    int n, x, y;
    cin >> n >> x >> y;
    vector<int> a(n + 1), b(n + 1);
    int sum = 0, mx = 0;
    map<int, int> mp;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i] >> b[i];
        int L = max(0LL, mx - a[i]);
        if (L < b[i])
        {                    // 小于就代表还需要P
            sum += b[i] - L; // 最初的花费
            mp[L]++, mp[b[i]]--;
        }
        mx = max(mx, b[i] + a[i]);
    }
    int cur = 0, cnt = 0;
    int res = sum * y;
    int now = res;
    for (auto &[pos, d] : mp)
    {
        int dsum = (pos - cur) * (x - y * cnt);
        now += dsum;
        res = min(res, now);
        cnt += d;
        cur = pos;
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