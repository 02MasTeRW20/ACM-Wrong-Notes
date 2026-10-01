// https://codeforces.com/contest/2269/problem/E
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
const int N = 3e5 + 10;
const int MOD = 998244353;
int n;
int a[N];
int st[N][20];
int cnt[N];
int pre[N];
int s[N];
int M;
int ok = 0;
void init()
{
    int len = __lg(n);
    for (int i = 1; i <= n; i++)
        st[i][0] = i;

    for (int j = 1; j <= len; j++)
    {
        for (int i = 1; i + (1LL << j) - 1 <= n; i++)
        {
            int x = st[i][j - 1];
            int y = st[i + (1LL << (j - 1))][j - 1];
            if (a[x] > a[y])
            {
                st[i][j] = x;
            }
            else
            {
                st[i][j] = y;
            }
        }
    }
}
int get(int l, int r)
{
    int len = __lg(r - l + 1);
    int x = st[l][len];
    int y = st[r - (1LL << len) + 1][len];
    if (a[x] > a[y])
        return x;
    else
        return y;
}
void divide(int l, int r)
{
    if (l > r)
        return;
    if (l == r)
    {
        cnt[pre[l] & M]++;
        return;
    }
    int mid = get(l, r);
    if (mid - l < r - mid)
    {
        divide(l, mid - 1);
        for (int i = l; i <= mid - 1; i++)
            cnt[pre[i] & M]--;
        divide(mid + 1, r);
        if ((a[mid] & M) != M)
        {
            for (int i = l; i <= mid; i++)
                cnt[pre[i] & M]++;
            return;
        }
        for (int i = mid - 1; i >= l - 1; i--)
        {
            if (cnt[(pre[i] & M) ^ M])
                ok = 1;
            if (i == mid - 1)
                cnt[pre[mid] & M]++;
        }
        for (int i = l; i <= mid - 1; i++)
            cnt[pre[i] & M]++;
    }
    else
    {
        divide(mid + 1, r);
        for (int i = mid + 1; i <= r; i++)
            cnt[pre[i] & M]--;
        divide(l, mid - 1);
        if ((a[mid] & M) != M)
        {
            for (int i = mid; i <= r; i++)
                cnt[pre[i] & M]++;
            return;
        }
        cnt[pre[mid - 1] & M]--;
        cnt[pre[l - 1] & M]++;

        for (int i = mid; i <= r; i++)
        {
            if (cnt[(pre[i] & M) ^ M])
                ok = 1;
            if (i == mid)
                cnt[pre[mid - 1] & M]++;
        }

        cnt[pre[l - 1] & M]--;
        for (int i = mid; i <= r; i++)
            cnt[pre[i] & M]++;
    }
}
void _MasTeRW_()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    init();
    for (int i = 1; i <= n; i++)
    {
        pre[i] = pre[i - 1] ^ a[i];
    }
    M = 0;
    for (int i = 17; i >= 0; i--)
    {
        M |= (1LL << i);
        ok = 0;
        divide(1, n);
        for (int i = 1; i <= n; i++)
        {
            cnt[pre[i] & M]--;
        }
        if (!ok)
            M ^= (1LL << i);
    }
    cout << M << endl;
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