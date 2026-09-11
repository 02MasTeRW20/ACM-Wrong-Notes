// https://codeforces.com/contest/2260/problem/E
// 这道题最难想的是 01 和 00 11 的数量关系
// 找到 00 11 拆掉一个之后会导致 01 10 各多一个
// 还有第二难想的就是这个二分，太畜生了，说句实话，如果告诉我是二分，我说不准真的能写的出来
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

int get(int A, int B, int C)
{
    int l = -1, r = 1e9;
    while (l + 1 < r)
    {
        int mid = (r + l) >> 1;
        if (C + max(0LL, A - mid) + max(0LL, B - mid) <= mid)
        {
            r = mid;
        }
        else
        {
            l = mid;
        }
    }
    return r;
}

void _MasTeRW_()
{
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    vector<int> pre1(n + 1);
    vector<int> prec(n + 1);
    for (int i = 0; i < n; i++)
    {
        pre1[i + 1] = pre1[i] + (s[i] - '0');
    }
    for (int i = 0; i < n - 1; i++)
    {
        prec[i + 1] = prec[i] + (s[i] != s[i + 1]);
    }

    while (q--)
    {
        int l, r;
        cin >> l >> r;
        int len = r - l + 1;
        int C = prec[r - 1] - prec[l - 1];
        int c1 = pre1[r] - pre1[l - 1];
        if (s[l - 1] != s[r - 1])
            C++;
        int B = c1 - C / 2;
        int A = len - c1 - C / 2;
        int t = get(A, B, C / 2);
        cout << 4 * t - len << endl;
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