#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define x first
#define y second

vector<vector<pair<int, ll>>> adj(10005); // Adjacency list of pair of { node, cost }.
pair<ll, int> Diameter(int node, int par)
{
      ll Ans = 0 ;
      ll MaxCosts[] = { 0, 0, 0 } ; // To keep the best 2 Costs.
      for (auto const &[v, cost] : adj[node])
            if (par != v)
            {
                  pair<ll, int> p = Diameter(v, node);

                  Ans = max(Ans, p.x);
                  MaxCosts[0] = p.y + cost;
                  sort(MaxCosts, MaxCosts + 3);
            }
      Ans = max(Ans, MaxCosts[1] + MaxCosts[2]);
      return make_pair(Ans, MaxCosts[2]);
}