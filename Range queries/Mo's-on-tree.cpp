/*
      MO's Algorithm on Tree
      Implementation of "MoTree" with the solution of the number of distinct colors on a path.
*/
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long
#define ull unsigned long long
#define input(v) for ( auto &x : v ) cin >> x
#define output(v) for ( auto &x : v ) cout << x << " "; 
#define all(v) v.begin(), v.end()
#define x first
#define y second

const int SQ = 500 ;
struct query
{
      int l, r, Lca, idx;
      pair<int,int> topair() const 
      {
            return { l / SQ, ( ( l / SQ ) & 1 ) ? -r : +r } ;
      }
      bool operator<( const query &other)
      {
            pair<int,int> F = this->topair() ;
            pair<int,int> S = other.topair() ;
            return F < S ;
      }
};
template< typename T >
struct MoTree
{
      int n ;
      int log ;
      vector<vector<int>> par, adj ;
      vector<int> a, s, e, depth, res, freq ;
      vector<int> occ ;
      vector<query> Q ;

      void dfs ( int node, int Dpar, int &cnt )
      {
            res.push_back( node ) ;
            s[node] = cnt++ ;
            for ( auto &child : adj[node] )
            {
                  if ( Dpar == child )
                        continue ;
                  depth[child] = depth[node] + 1 ;
                  par[child][0] = node ; 
                  for ( int j = 1 ; j < log ; j++ )
                        par[child][j] = par[par[child][j - 1]][j - 1] ;
                  dfs( child, node, cnt ) ;
            }
            e[node] = cnt++ ;
            res.push_back( node ) ;
      }
      MoTree( int n, vector<vector<int>> &Adj, vector<int> &c, int root = 1 )
      {
            this->n = n ;
            log = log2( n ) + 5  ;
            par.resize( n + 5, vector<int>( log ) ) ;
            depth.resize( n + 5 ) ;
            s.resize( n + 5 ) ;
            e.resize( n + 5 ) ;
            a = c ;
            CoComp( a ) ;
            adj = Adj ;
            int cnt = 0 ;
            dfs( root, 0, cnt ) ;
      }

      
      void CoComp ( vector<int> &a )
      {
            map<int,bool> mp ;
            map<int,int> p ;

            for ( int i = 1 ; i <= n ; i++ )    
                  mp[a[i]] = true ;

            int idx = 1 ;
            for ( auto &[x,_] : mp )
                  p[x] = idx++ ;
            for ( int i = 1 ; i <= n ; i++ )
                  a[i] = p[a[i]] ;
      }

      int GetLca(int a, int b)
      {
            if (depth[b] > depth[a])
                  swap(a, b);

            int k = depth[a] - depth[b];

            for ( int i = log - 1 ; i >= 0 ; i-- )
                  if (k & (1 << i))
                        a = par[a][i] ;

            if (a == b)
                  return a;

            for ( int i = log - 1 ; i >= 0 ; i-- )
            {
                  if (par[a][i] != par[b][i])
                  {
                        a = par[a][i];
                        b = par[b][i];
                  }
            }
            a = par[a][0];
            return a;
      }
      void ReadQueries( int m )
      {
            int u, v ;
            for ( int i = 0 ; i < m ; i++ )
            {
                  cin >> u >> v ;
                  if ( s[u] > s[v] )
                        swap( u, v ) ;

                  int Lca = GetLca( u, v ) ;
                  if ( Lca == u )
                        Q.push_back( { s[u], s[v], -1, i } ) ;
                  else
                        Q.push_back( { e[u], s[v], Lca, i } ) ;
            }
            sort( all( Q ) );
      }

      int curr = 0 ;
      vector<int> AnswerQueries( int m )
      {
            freq.resize( *max_element( all( a ) ) + 5 ) ;
            occ.resize( n + 5 ) ;

            auto add = [&]( int i )
            {
                  if ( occ[res[i]] )
                  {
                        freq[a[res[i]]]-- ;
                        if ( freq[a[res[i]]] == 0 )
                              curr-- ;
                  }
                  else
                  {
                        freq[a[res[i]]]++ ;
                        if ( freq[a[res[i]]] == 1 )
                              curr++ ;
                  }

                  occ[res[i]] ^= 1 ;
            } ;

            auto del = [&]( int i )
            {
                  if ( occ[res[i]] )
                  {
                        freq[a[res[i]]]-- ;
                        if ( freq[a[res[i]]] == 0 )
                              curr-- ;
                  }
                  else
                  {
                        freq[a[res[i]]]++ ;
                        if ( freq[a[res[i]]] == 1 )
                              curr++ ;
                  }

                  occ[res[i]] ^= 1 ;
            } ;

            vector<int> ans( m ) ;
            int l = 0, r = -1 ;
            for ( int i = 0 ; i < m ; i++ )
            {
                  query x = Q[i];
                  while (r < x.r)
                        add(++r);
                  while (l > x.l)
                        add(--l);
                  while (r > x.r)
                        del(r--);
                  while (l < x.l)
                        del(l++);
                  
                  bool Lca = 0 ;
                  if ( x.Lca != -1 && freq[a[x.Lca]] == 0 )
                        Lca = true ;

                  ans[x.idx] = curr + Lca ;
            }
            return ans ;
      }
} ;


void solve()
{
      int n, m ;
      cin >> n >> m ;
      vector<int> a ( n + 1 ) ;
      for ( int i = 1 ; i <= n ; i++ )
            cin >> a[i] ;
      vector<vector<int>> adj ( n+1 ) ;

      for ( int i = 0 ; i < n-1 ; i++ )
      {
            int u, v ;
            cin >> u >> v ;
            adj[u].push_back( v ) ;
            adj[v].push_back( u ) ;
      }
      
      MoTree<int> Tree( n, adj, a ) ;
      Tree.ReadQueries( m ) ;
      vector<int> ans = Tree.AnswerQueries( m ) ;
      
      for (auto &x : ans)
            cout << x << '\n';
}