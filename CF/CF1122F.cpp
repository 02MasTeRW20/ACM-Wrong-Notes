// https://codeforces.com/contest/2266/problem/F
// 这是贡献度的优化，要构造一个 M 的 mex ，那么就意味着起码需要一个 0 ～ M - 1 的序列存在
// 然后模拟，找这个 M ，找到了就找 M - 1 ，每次找下一个，都会有一个需求量 need
// need 就是当前的 x 的需求量，若达到需求，那么下一层的需求就还是 need
// 反之，缺少了多少个 x ， 那么我就需要多少个 0 ～ x - 1 ， 这就意味着，需求量 need 也要增加这么多
// 依次找下去
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
    vector<int> x(n + 1), y(n + 1);
    int mx = 0;
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> x[i] >> y[i];
        mp[x[i]] = y[i];
        mx = max(mx, x[i]);
        sum += y[i];
    }

    vector<int> keys;
    for (int i = 1; i <= n; i++)
        keys.push_back(x[i]);
    sort(keys.rbegin(), keys.rend());

    int L = sum + 1;

    auto check = [&](int t) -> int
    {
        int cnt0 = 0;
        int need = 1;
        int now = t - 1;

        for (auto &k : keys)
        {
            if (k > now)
            {
                cnt0 += mp[k];
                continue;
            }
            if (k < now)
            {
                int d = now - k;
                while (d--)
                {
                    need *= 2;
                    if (need > L)
                        return 0;
                }
            }
            now = k;
            if (k == 0)
                break;
            if (mp[k] > need)
            {
                cnt0 += mp[k] - need;
            }
            else
            {
                need += need - mp[k];
                if (need > L)
                    return 0;
            }
            now = k - 1;
        }

        if (now > 0)
        {
            int d = now;
            while (d--)
            {
                need *= 2;
                if (need > L)
                    return 0;
            }
        }
        return cnt0 + mp[0] >= need;
    };
    int l = 0, r = L + 1;
    while (l + 1 < r)
    {
        int mid = l + r >> 1;
        if (check(mid))
            l = mid;
        else
            r = mid;
    }
    cout << max(l, mx) << endl;
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