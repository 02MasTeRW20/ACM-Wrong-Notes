// https://qoj.ac/contest/4071/problem/20016
// 最难想到的是这个要考虑到将来，这个是根据队友理解所得的代码
// queue占据内存过多
// 加上了更快速度的UMAP

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define ll long long
#define fl float
#define dl double
#define pii pair<int, int>
#define lowbit(x) (x & -x)
const int N = 2e5 + 10;
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

void _MasTeRW_()
{
    int n;
    cin >> n;
    UMAP<int, queue<char>> a;
    vector<pair<char, int>> ss;
    for (int i = 0; i < n; i++)
    {
        char op;
        int x;
        cin >> op >> x;
        ss.push_back({op, x});
        a[x].push(op);
    }
    string ans;
    stack<int> sk;
    for (int i = 0; i < n; i++)
    {
        auto [op, x] =
            ss[i];
        a[x].pop();
        if (op == '+')
        {
            ans += '+';
            sk.push(x);
        }
        else
            ans += '?';
        while (sk.size() && (!(a[sk.top()].size()) || a[sk.top()].front() != 'T'))
        {
            ans += '-';
            sk.pop();
        }
    }
    cout << ans << endl;
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