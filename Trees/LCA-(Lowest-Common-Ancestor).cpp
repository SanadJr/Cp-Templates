/*
      Approach to calculate LCA using Binary Lifting
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 10005;
const int Log = 18;
int up[N][Log] = {};
vector<int> adj[N];

int depth[N] = {};
void dfs(int node)
{
      for (auto &child : adj[node])
      {
            depth[child] = depth[node] + 1;
            up[child][0] = node; // The parent of the current node.
            for (int j = 1; j < Log; j++)
            {
                  up[child][j] = up[up[child][j - 1]][j - 1];
            }
            dfs(child);
      }
}

int get_LCA(int a, int b)
{
      if (depth[b] > depth[a])
            swap(a, b);

      int k = depth[a] - depth[b];

      for (int i = Log - 1; i >= 0; i--)
      {
            if (k & (1 << i))
                  a = up[a][i];
      }
      if (a == b)
            return a;

      for (int i = Log - 1; i >= 0; i--)
      {
            if (up[a][i] != up[b][i])
            {
                  a = up[a][i];
                  b = up[b][i];
            }
      }
      a = up[a][0];
      return a;
}