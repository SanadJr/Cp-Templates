#include <bits/stdc++.h>
using namespace std;

struct CentroidDecomposition
{
      int n;
      int centroid_root = -1;

      vector<vector<int>> adj;
      vector<int> Size, parent, level ;
      vector<bool> removed;


      int dfs_size( int node, int par )
      {
            Size[node] = 1;
            for (int child : adj[node])
            {
                  if ( child == par || removed[child] )
                        continue;
                  Size[node] += dfs_size( child, node ) ;
            }
            return Size[node] ;
      }

      int dfs_centroid(int node, int par, int total)
      {
            for (int child : adj[node])
            {
                  if (child == par || removed[child])
                        continue;
                  if (Size[child] > total / 2)
                        return dfs_centroid(child, node, total);
            }
            return node;
      }

      void build_cd(int entry, int p, int depth)
      {
            int total = dfs_size(entry, -1);
            int c = dfs_centroid(entry, -1, total);

            parent[c] = p;
            level[c] = depth;
            removed[c] = true;

            if (p == -1)
                  centroid_root = c;

            for (int v : adj[c])
            {
                  if (!removed[v])
                        build_cd(v, c, depth + 1);
            }
      }

      CentroidDecomposition(int n, const vector<vector<int>> &graph, int root = 1) : n(n), adj(graph)
      {
            Size.resize(n + 5);
            parent.assign(n + 5, -1);
            level.resize(n + 5);
            removed.assign(n + 5, false);
            centroid_root = -1;
            build(root);
      }


      void build(int root = 1)
      {
            Size.assign(n + 5, 0);
            parent.assign(n + 5, -1);
            level.assign(n + 5, 0);
            removed.assign(n + 5, false);
            centroid_root = -1;

            build_cd(root, -1, 0);
      }

      vector<vector<int>> get_CentroidTree()
      {
            vector<vector<int>> new_graph(n + 5);
            for (int i = 1; i <= n; i++)
            {
                  if (parent[i] != -1)
                  {
                        new_graph[i].push_back(parent[i]);
                        new_graph[parent[i]].push_back(i);
                  }
            }
            return new_graph;
      }
};
