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
const int INF = 1e18;
const int N = 2e5 + 10;
const int MOD = 998244353;
using ull = unsigned long long;

void _MasTeRW_()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    int sum = 0;
    for (int i = 1; i <= n; i++)
        cin >> a[i], sum += a[i];

    auto check = [&](int x) -> bool
    {
        int q = (x - n) / (n - 1);
        int r = (x - n) % (n - 1);
        int C = (q + 1) / 2; // 每首歌最多可以作为关键歌曲的数量
        int G = 0;           // 总共歌曲对白卡的需求
        int S = 0;           // 总共歌曲成为关键歌曲可以省掉的白卡总数
        int F = 0;           // 后面 r 个元素中不需要白卡的歌曲个数
        int E = 0;           // 前面的牌变成关键牌之后对后面 r 个元素所省掉的白卡个数
        for (int i = 1; i <= n; i++)
        {
            int h = max(0LL, q + 1 - a[i]); // 每首歌的白卡数
            G += h;
            S += min(C, h); // 每首歌可以省去的白卡数
            F += (a[i] > q + 1);
            E += (a[i] <= q + 1 && h + 1 <= C);
        }
        int R = max(0LL, r - F);       // 后面 r 个元素需要的白卡数量
        int B = min(q, S + min(R, E)); // 关键牌后省的白卡数量
        int need = G + R - B;
        return need <= k;
    };
    int l = n, r = sum + k + 1;
    while (l + 1 < r)
    {
        int mid = l + r >> 1;
        if (check(mid))
            l = mid;
        else
            r = mid;
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