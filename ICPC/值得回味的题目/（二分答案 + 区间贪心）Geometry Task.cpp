// https://qoj.ac/contest/1913/problem/9043
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
const int INF = 4e18;
const int N = 2e5 + 10;
const int MOD = 998244353;

void _MasTeRW_()
{
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1), c(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    for (int i = 1; i <= n; i++)
        cin >> c[i];
    sort(all(c));
    int k = (n + 1) / 2;
    auto check = [&](int t) -> int
    {
        int cnt = 0;
        vector<int> suf(n + 1);
        vector<int> pre(n + 1);
        for (int i = 1; i <= n; i++)
        {
            if (a[i] != 0)
            {
                if (a[i] > 0)
                {
                    int g;
                    if (t - b[i] <= 0)
                        g = (t - b[i]) / a[i];
                    else
                        g = (t - b[i] + a[i] - 1) / a[i];
                    int j = lower_bound(all(c), g) - c.begin();
                    if (j <= n)
                        suf[j]++;
                }
                else
                {
                    int g;
                    if (t - b[i] < 0)
                    {
                        g = -(t - b[i]) / (-a[i]);
                    }
                    else
                    {
                        g = -((t - b[i] + (-a[i]) - 1) / (-a[i]));
                    }
                    int j = upper_bound(all(c), g) - c.begin() - 1;
                    if (j >= 1)
                        pre[j]++;
                }
            }
            else
            {
                if (b[i] >= t)
                    cnt++;
            }
        }
        int pret = 1, suft = n;
        for (int i = 1; i <= n; i++)
        {
            while (pre[i] > 0)
            {
                if (i >= pret)
                {
                    pret++;
                    cnt++;
                }
                pre[i]--;
            }
        }
        for (int i = n; i >= 1; i--)
        {
            while (suf[i] > 0)
            {
                if (i <= suft)
                {
                    suft--;
                    cnt++;
                }
                suf[i]--;
            }
        }
        return cnt >= k;
    };
    int l = -INF, r = INF;
    while (l + 1 < r)
    {
        int mid = l + r >> 1;
        if (check(mid))
        {
            l = mid;
        }
        else
        {
            r = mid;
        }
    }
    cout << l << endl;
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