/*
      Approach to calculate the k'th ancestor of a tree node
*/
#include <bits/stdc++.h>
using namespace std;

int ans[50005][18] = {};
int d[50005] = {};
int depth(int node, vector<int> &parent)
{
      if ( node == -1 )
            return -1;
      if ( d[node] != -1 )
            return d[node];
      return d[node] = 1 + depth(parent[node], parent);
}
void TreeAncestor( int n, vector<int> &parent )
{
      memset(ans, -1, sizeof ans);
      memset(d, -1, sizeof d);

      for (int i = 0; i < n; i++)
            if ( d[i] == -1 )
                  d[i] = depth(i, parent);

      for ( int i = 0 ; i < n ; i++ )
            ans[i][0] = parent[i] ;
      
      for ( int j = 1 ; j < 18 ; j++ )
      {
            for ( int i = 0 ; i < n ; i++ )
            {
                  if ( ans[i][j-1] != -1 )
                        ans[i][j] = ans[ans[i][j - 1]][j - 1];
            }
      }
}

int getKthAncestor(int node, int k)
{
      if ( k > d[node] )
            return -1 ;

      for (int i = 17; i >= 0; i--)
      {
            if ( k & (1 << i) )
            {
                  node = ans[node][i];
            }
      }
      return node;
}