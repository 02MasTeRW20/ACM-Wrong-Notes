// https://qoj.ac/contest/4121/problem/20294
// 这更像是Manacher的模版题，但是这个多了一个二分
// 这个 st 之前开 vector 发现 TL，改成静态就过了。。。。
// 后续发现是这个 log2 函数太慢了，只要换成 __lg 就可以过。。。。
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
const int N = 1e6 + 10;
const int MOD = 998244353;
int st[N][21];

void init(const string &s)
{
    int n = s.size();
    int len = __lg(n);

    for (int i = 0; i < n; i++)
        st[i][0] = (1 << (s[i] - 'a'));

    for (int j = 1; j <= len; j++)
    {
        for (int i = 0; i + (1 << j) <= n; i++)
        {
            st[i][j] = st[i][j - 1] | st[i + (1 << (j - 1))][j - 1];
        }
    }
}

int ask(int l, int r)
{
    int len = r - l + 1;
    int k = __lg(len);
    return __builtin_popcount(st[l][k] | st[r - (1 << k) + 1][k]);
}
void _MasTeRW_()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    init(s);
    string p;
    p.reserve(2 * n + 3);
    p += '@';
    for (int i = 0; i < n; i++)
    {
        p += '#';
        p += s[i];
    }
    p += "#$";
    // cout << p << endl;
    int c = 0, r = 0;
    int len = p.size();
    vector<int> d(len);
    int res = 0;
    for (int i = 1; i < len - 1; i++)
    {
        if (i < r)
            d[i] = min(r - i, d[2 * c - i]);
        while (p[i + d[i] + 1] == p[i - d[i] - 1])
            d[i]++;
        if (d[i] + i > r)
        {
            r = d[i] + i;
            c = i;
        }
        if (i % 2 == 0)
        {
            int di = d[i];
            int k = (i - 2) / 2;
            int l = 0, r = di + 1;
            while (l + 1 < r)
            {
                int mid = l + r >> 1;
                int sR = mid / 2;
                int L = k - sR, R = k + sR;
                if (ask(L, R) <= 2)
                    l = mid;
                else
                    r = mid;
            }
            res += (l + 1) / 2;
        }
        else
        {
            int di = d[i];
            if (di < 2)
                continue;
            int k = (i - 1) / 2;
            int l = 1, r = di + 1;
            while (l + 1 < r)
            {
                int mid = l + r >> 1;
                int sR = mid / 2;
                int L = k - sR, R = k + sR - 1;

                if (ask(L, R) <= 2)
                    l = mid;
                else
                    r = mid;
            }
            res += l / 2;
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