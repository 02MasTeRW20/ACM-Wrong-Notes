// https://qoj.ac/contest/4071/problem/20027

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
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

const int N = 5e5 + 10;
int ch[26][N];
int cnt[N];
int depth[N];
int fval[N];
int ans = 0;
int pos = 0;

void insert(string &s)
{
    int u = 0;
    int d = 1;
    for (auto &x : s)
    {
        char k = x - 'a';
        if (!ch[k][u])
            ch[k][u] = ++pos;
        u = ch[k][u];
        cnt[u]++;

        if (cnt[u] > depth[d])
        {
            depth[d] = cnt[u];
            if (fval[cnt[u]] < d)
            {
                int old = fval[cnt[u]];
                ans -= (old ^ cnt[u]);
                ans += (d ^ cnt[u]);
                fval[cnt[u]] = d;
            }
        }
        d++;
    }
}

void _MasTeRW_()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        int j = i + 1;
        ans += (0 ^ j);
        insert(s);
        cout << ans << endl;
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    while (T--)
        _MasTeRW_();
    return 0;
}