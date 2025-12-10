#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define x first
#define y second

vector<vector<int>> adj(10005); // Adjacency list.
pair<ll, int> Diameter(int node, int par)
{
      ll Diam = 0 ;
      ll MaxHeights[] = { 0, 0, 0 } ; // To keep the best 2 Heights.
      for (auto const &v : adj[node])
            if (par != v)
            {
                  pair<ll, int> p = Diameter(v, node);

                  Diam = max(Diam, p.x);
                  MaxHeights[0] = p.y + 1;
                  sort(MaxHeights, MaxHeights + 3);
            }
      Diam = max(Diam, MaxHeights[1] + MaxHeights[2]);
      return make_pair(Diam, MaxHeights[2]);
}