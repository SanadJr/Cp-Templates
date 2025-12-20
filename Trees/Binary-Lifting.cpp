/*
      Approach to calculate the k'th ancestor of a tree node
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 50005 ;
const int Log = 18 ;
int up[N][Log] = {};

int depth[N] = {};
int dfs(int node, vector<int> &parent)
{
      if ( node == 0 )
            return 0 ;
      if ( depth[node] != -1 )
            return depth[node];
      return depth[node] = 1 + dfs(parent[node], parent);
}
void TreeAncestor( int n, vector<int> &parent )
{
      memset(depth, -1, sizeof depth);

      for (int i = 0; i < n; i++)
            if ( depth[i] == -1 )
                  depth[i] = dfs(i, parent);

      up[0][0] = 0 ;
      for ( int i = 1 ; i < n ; i++ )
            up[i][0] = parent[i] ;
      
      for ( int j = 1 ; j < Log ; j++ )
      {
            for ( int i = 0 ; i < n ; i++ )
            {
                  up[i][j] = up[up[i][j - 1]][j - 1];
            }
      }
}
int getKthAncestor(int node, int k)
{
      if ( k > depth[node] )
            return -1 ;

      for (int i = Log-1; i >= 0; i--)
      {
            if ( k & (1 << i) )
            {
                  node = up[node][i];
            }
      }
      return node;
}