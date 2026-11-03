// https://qoj.ac/contest/1913/problem/9038
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
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count()); // rng() 随机数
template <typename K, typename V>
using UMAP = unordered_map<K, V, custom_hash>;
const int INF = 9e18;
const int N = 3e5 + 10;
const int MOD = 998244353;
int n;
int st[N][30];
void init(vector<int> &y)
{
    int len = __lg(n);
    for (int i = 1; i <= n; i++)
        st[i][0] = y[i];

    for (int j = 1; j <= len; j++)
    {
        for (int i = 1; i + (1LL << j) - 1 <= n; i++)
        {
            st[i][j] = max(st[i][j - 1], st[i + (1LL << (j - 1))][j - 1]);
        }
    }
}

int ask(int l, int r)
{
    int len = r - l + 1;
    if (len <= 0)
        return 0;
    int k = __lg(len);
    return max(st[l][k], st[r - (1LL << k) + 1][k]);
}
void _MasTeRW_()
{
    int m;
    cin >> n >> m;
    vector<pii> p(m + 1);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;

        p[i] = {u, v};
    }
    vector<int> y(n + 1);
    vector<int> x(n + 1);
    vector<int> a(n + 1);
    vector<int> pos(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        pos[a[i]] = i;
    }
    for (int i = 1; i <= m; i++)
    {
        int u = pos[p[i].first];
        int v = pos[p[i].second];
        if (u > v)
            swap(u, v);
        x[v] = max(x[v], u);
        y[u] = max(y[u], v);
    }
    init(y);
    vector<pii> res;
    for (int i = 1; i <= n; i++)
    {
        int l = x[i] + 1, r = i - 1;
        int mx = ask(l, r);
        // cout << a[i] << " " << a[x[i]] << " " << a[mx] << endl;
        if (mx > i)
        {
            res.push_back({a[i], a[i - 1]});
        }
    }
    cout << res.size() << endl;
    for (auto &[u, v] : res)
    {
        cout << u << " " << v << endl;
    }
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