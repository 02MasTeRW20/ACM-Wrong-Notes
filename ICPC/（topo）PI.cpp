// https://qoj.ac/contest/4071/problem/20018
// 最烦躁的一道题，这是一道topo题
// 赛时想的过于复杂，想这个如何同级排序，赛后想了想，用上了优先队列，最重要的是这个当中的贪心思路
// 赛时没想到这个贪心的决策，越小越前

#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    vector<int> indeg(n + 1, 0);

    for (int i = 0; i < m; ++i)
    {
        int l, r;
        cin >> l >> r;
        int k = r - l + 1;
        vector<int> q(k);
        for (int j = 0; j < k; ++j)
            cin >> q[j];
        for (int j = 0; j + 1 < k; ++j)
        {
            int u = q[j], v = q[j + 1];
            adj[u].push_back(v);
            ++indeg[v];
        }
    }

    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= n; ++i)
    {
        if (indeg[i] == 0)
            pq.push(i);
    }

    vector<int> order;
    order.reserve(n);
    while (!pq.empty())
    {
        int u = pq.top();
        pq.pop();
        order.push_back(u);
        for (int v : adj[u])
        {
            if (--indeg[v] == 0)
                pq.push(v);
        }
    }

    if ((int)order.size() != n)
    {
        cout << -1 << '\n';
        return;
    }

    vector<int> p(n + 1);
    for (int i = 0; i < n; ++i)
    {
        p[order[i]] = i + 1;
    }
    for (int i = 1; i <= n; ++i)
    {
        cout << p[i] << (i == n ? '\n' : ' ');
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}