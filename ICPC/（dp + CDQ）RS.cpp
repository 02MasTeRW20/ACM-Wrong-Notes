// https://qoj.ac/contest/4071/problem/20029
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define ll long long
#define lowbit(x) (x & -x)
const int INF = 1e18;
const int N = 2e5 + 10;

int n;
// A[i] = r[i] - y[i]，B[i] = r[i] - b[i]
// dp[i] : 前 i 个位置中，"非红色段"的最小数量
// 最终答案 = n - dp[n]，即最多有多少个位置属于红色段
int A[N], B[N], dp[N];

// 树状数组：维护 B 维的前缀最小值
// tree[x] 存的是 B 值在 (x-lowbit(x), x] 范围内的 dp 最小值
int tree[N];

// M 是离散化后 B 的最大值，也是树状数组的下标上界
int M;

// 用于离散化 B 的辅助数组
vector<int> vals;

void update(int x, int val, vector<int> &modified)
{
    for (; x <= M; x += lowbit(x))
    {
        if (val < tree[x])
        {
            tree[x] = val;
            modified.push_back(x);
        }
    }
}

int query(int x)
{
    int res = INF;
    for (; x > 0; x -= lowbit(x))
        res = min(res, tree[x]);
    return res;
}

void cdq(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    cdq(l, mid);

    vector<int> left_idx, right_idx;

    for (int i = l; i <= mid; i++)
        left_idx.push_back(i);

    for (int i = mid + 1; i <= r; i++)
        right_idx.push_back(i);
    // 按照下标来排序
    sort(left_idx.begin(), left_idx.end(), [](int x, int y)
         { return A[x] < A[y]; });
    sort(right_idx.begin(), right_idx.end(), [](int x, int y)
         { return A[x] < A[y]; });
    // 保证 i >= j
    int p = 0;
    vector<int> modified;
    for (int i : right_idx)
    {
        while (p < left_idx.size() && A[left_idx[p]] <= A[i]) // 保证 A[i] >= A[j]
        {
            
            update(B[left_idx[p]], dp[left_idx[p]], modified);
            // 把 B 当成下标，这样可以保证 B[i] >= B[j]
            p++;
        }

        int mn = query(B[i]);
        // 查询前面最小的 dp
        if (mn < dp[i])
            dp[i] = mn;
    }

    for (int t : modified)
        tree[t] = INF;

    // 相邻转移：跨越中点的那一对
    if (dp[mid] + 1 < dp[mid + 1])
        dp[mid + 1] = dp[mid] + 1;

    cdq(mid + 1, r);
    // 却保每个 dp 都能被更新到
}

void _MasTeRW_()
{
    cin >> n;
    vector<int> r(n + 1), b(n + 1), y(n + 1);

    for (int i = 1; i <= n; i++)
    {
        cin >> r[i] >> y[i] >> b[i];
    }

    for (int i = 0; i < n; i++)
    {
        r[i + 1] += r[i];
        y[i + 1] += y[i];
        b[i + 1] += b[i];
    }

    // 公式推导
    // A[i] >= A[j], B[i] >= B[j], i >= j <----------------> j ~ i 为红色段
    for (int i = 1; i <= n; i++)
    {
        A[i] = r[i] - y[i];
        B[i] = r[i] - b[i];
    }

    // 离散化 B
    vals.clear();
    for (int i = 0; i <= n; i++)
        vals.push_back(B[i]);
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    M = vals.size();
    for (int i = 0; i <= n; i++)
        B[i] = lower_bound(vals.begin(), vals.end(), B[i]) - vals.begin() + 1;

    // 初始化
    for (int i = 1; i <= n; i++)
        dp[i] = INF;
    dp[0] = 0;
    for (int i = 1; i <= M; i++)
        tree[i] = INF;

    cdq(0, n);

    cout << n - dp[n] << endl;
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