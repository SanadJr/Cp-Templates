/*
      HLD ( Heavy Light Decomposition )
      Implementation of HLD + Segment Tree + The solution of the basic problem ( CSES-Path Queries )
*/
#include <bits/stdc++.h>
using namespace std;

#define min_nums(n) st.order_of_key(n)
#define value(n) st.find_by_order(n)
#define ll long long
#define ull unsigned long long
#define input(v)        \
      for (auto &x : v) \
      cin >> x
#define output(v)       \
      for (auto &x : v) \
            cout << x << " ";
#define all(v) v.begin(), v.end()
#define x first
#define y second

template <typename T>
class SegTree
{
public:
      struct Node
      {
      public:
            T value;
      };

      int Size;
      Node Default;
      vector<Node> tree;

      SegTree(int n)
      {
            Size = 1;
            while (Size < n)
                  Size *= 2;

            Default.value = 0;
            tree.assign(2 * Size, Default);
      }

      Node operation(Node x, Node y)
      {
            Node New;
            New.value = x.value + y.value;
            return New;
      }
      void set(int idx, T value, int id, int l, int r)
      {
            if (l == r)
            {
                  tree[id].value = value;
                  return;
            }
            int mid = (l + r) / 2;
            if (idx <= mid)
                  set(idx, value, 2 * id, l, mid);
            else
                  set(idx, value, 2 * id + 1, mid + 1, r);

            tree[id] = operation(tree[2 * id], tree[2 * id + 1]);
      }
      void set(int idx, T value)
      {
            set(idx, value, 1, 1, Size);
      }

      Node get(int lx, int rx, int id, int l, int r)
      {
            if (rx < l || r < lx)
                  return Default;
            if (lx <= l && r <= rx)
            {
                  return tree[id];
            }

            int mid = (l + r) / 2;
            Node x = get(lx, rx, 2 * id, l, mid);
            Node y = get(lx, rx, 2 * id + 1, mid + 1, r);
            return operation(x, y);
      }
      T get(int l, int r)
      {
            return get(l, r, 1, 1, Size).value;
      }
};

class HLD
{
public:
      vector<int> par, head, big, pos, dep, Size;
      int nextPos;

      void dfs(int node, const vector<vector<int>> &adj)
      {
            for (auto &child : adj[node])
            {
                  if (child == par[node])
                        continue;
                  par[child] = node;
                  dep[child] = dep[node] + 1;
                  dfs(child, adj);
                  Size[node] += Size[child];
                  if (big[node] == -1 || Size[child] > Size[big[node]])
                        big[node] = child;
            }
      }

      void build(int node, const vector<vector<int>> &adj)
      {
            pos[node] = nextPos++;
            if (big[node] != -1)
            {
                  head[big[node]] = head[node];
                  build(big[node], adj);
            }

            for (auto &child : adj[node])
            {
                  if (child == big[node] || child == par[node])
                        continue;
                  head[child] = child;
                  build(child, adj);
            }
      }
      HLD(int n, const vector<vector<int>> &adj) : par(n + 1), head(n + 1), big(n + 1, -1), pos(n + 1), dep(n + 1), Size(n + 1, 1), nextPos(1)
      {
            dfs(1, adj);
            head[1] = 1;
            build(1, adj);
      }
      vector<pair<int, int>> paths(int u, int v)
      {
            vector<pair<int, int>> res;
            while (true)
            {
                  if (head[u] == head[v])
                  {
                        if (dep[v] < dep[u])
                              swap(u, v);
                        res.push_back({pos[u], pos[v]});
                        return res;
                  }
                  if (dep[head[v]] < dep[head[u]])
                        swap(u, v);
                  res.push_back({pos[head[v]], pos[v]});
                  v = par[head[v]];
            }
      }
};
void solve()
{
      int n, q;
      cin >> n >> q;
      vector<int> a(n);
      input(a);

      vector<vector<int>> adj(n + 1);
      for (int i = 0; i < n - 1; i++)
      {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
      }

      HLD hld(n + 1, adj);
      SegTree<long long> Tree(n + 1);
      for (int i = 0; i < n; i++)
      {
            Tree.set(hld.pos[i + 1], a[i]);
      }

      while (q--)
      {
            int x, a, b;
            cin >> x;
            if (x == 1)
            {
                  cin >> a >> b;
                  Tree.set(hld.pos[a], b);
            }
            else
            {
                  cin >> b;
                  vector<pair<int, int>> Pths = hld.paths(1, b);
                  long long Ans = 0;
                  for (auto &[l, r] : Pths)
                  {
                        Ans += Tree.get(l, r);
                  }
                  cout << Ans << '\n';
            }
      }
}
int main()
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