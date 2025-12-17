/*
      Second approach to find the diameter using "dfs" twice.
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> adj[200005] ;
int diameter = 0, far = 0 ;
void dfs(int node, int par, int depth)
{
      if (depth > diameter)
      {
            diameter = depth;
            far = node;
      }
      for (auto &x : adj[node])
      {
            if (x != par)
            {
                  dfs(x, node, depth + 1);
            }
      }
}
void solve()
{
      int n;
      cin >> n;
      while (--n)
      {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
      }
      dfs(1, -1, 0);
      int node = far;

      dfs(node, -1, 0);
      cout << diameter;
}