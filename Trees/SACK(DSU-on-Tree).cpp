/*
      SACK ( DSU on tree )
      Implementation of SACK with the solution of ( CF-600E ).
*/
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long

const int N = 2e5 + 5;
vector<int> adj[N];
int Size[N] = {};
int Big[N] = {};
int c[N] = {};
int freq[N] = {};
map<int, int> Ans;
int ans[N];
int n;
void pre(int node, int par)
{
      Size[node] = 1;
      for (auto &child : adj[node])
      {
            if (child != par)
            {
                  pre(child, node);
                  Size[node] += Size[child];
                  if (!Big[node] || Size[child] > Size[Big[node]])
                        Big[node] = child;
            }
      }
}
void update(int node, int d)
{
      freq[c[node]] += d;
      Ans[freq[c[node]]] += c[node];
      if (Ans.find(freq[c[node]] - d) != Ans.end())
      {
            Ans[freq[c[node]] - d] -= c[node];
            if (Ans[freq[c[node]] - d] == 0)
                  Ans.erase(freq[c[node]] - d);
      }
}
void collect(int node, int par, int d)
{
      update(node, d);
      for (auto &child : adj[node])
            if (child != par)
                  collect(child, node, d);
}
void dfs(int node, int par, bool keep)
{
      for (auto &child : adj[node])
      {
            if (child != par && child != Big[node])
                  dfs(child, node, false);
      }

      if (Big[node] != 0)
            dfs(Big[node], node, true);

      update(node, 1);
      for (auto &child : adj[node])
      {
            if (child != par && child != Big[node])
                  collect(child, node, 1);
      }

      auto it = Ans.end();
      it--;
      ans[node] = it->second;

      if (!keep)
            collect(node, par, -1);
}
void solve()
{
      cin >> n;
      for (int i = 1; i <= n; i++)
            cin >> c[i];

      for (int i = 0; i < n - 1; i++)
      {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
      }

      pre(1, 1);
      dfs(1, 1, true);
      for (int i = 1; i <= n; i++)
            cout << ans[i] << " ";
}
signed main()
{

      ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
      #ifndef ONLINE_JUDGE
            freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
      #endif

      int t = 1;
      //    cin >> t;
      while (t--)
      {
            solve();
            cout << "\n";
      }
}