/*
      SACK ( DSU on tree )
      Implementation of SACK with the solution of ( CF-600E ).
*/
#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
 
template < typename T >
using ordered_set = tree < T, null_type, less < T >,
rb_tree_tag, tree_order_statistics_node_update >;
 
template < typename T >
using ordered_multiset = tree < T, null_type, less_equal < T >,
rb_tree_tag, tree_order_statistics_node_update >;
 
#define min_nums(n) st.order_of_key(n)
#define value(n) st.find_by_order(n)
#define ll long long
#define ull unsigned long long
#define input(v) for ( auto &x : v ) cin >> x
#define output(v) for ( auto &x : v ) cout << x << " "; 
#define all(v) v.begin(), v.end()
#define x first
#define y second
#define int long long

const int N = 2e5 + 5 ;
vector<int> adj [ N ] ;
int Size[ N ] = {} ;
int Big[ N ] = {} ;
int c[ N ] = {} ;
int freq[N] = {} ;
int sum[N], Max = INT_MIN ;
int ans[N] ;
int n ;
void pre ( int node, int par )
{
    Size[node] = 1 ;
    for ( auto &child : adj[ node ] )
    {
        if ( child != par )
        {
            pre ( child, node ) ;
            Size[node] += Size[child] ;
            if ( !Big[node] || Size[child] > Size[Big[node]] )
                Big[node] = child ;
        }
    }
}
void update ( int node, int d )
{
    if ( freq[c[node]] + d > Max || ( freq[c[node]] == Max && sum[freq[c[node]]] == c[node] ) )
        Max = freq[c[node]] + d ;

    sum[freq[c[node]]] -= c[node] ;
    freq[c[node]] += d ;
    sum[freq[c[node]]] += c[node] ;
}
void collect ( int node, int par, int d )
{
    update( node, d ) ;
    for ( auto &child : adj[node] )
        if ( child != par )
            collect( child, node, d ) ;
}
void dfs ( int node, int par, bool keep )
{
    for ( auto &child : adj[node] )
    {
        if ( child != par && child != Big[node] )
            dfs( child, node, false ) ;
    }

    if ( Big[node] != 0 )
        dfs( Big[node], node, true ) ;

    update( node, 1 ) ;
    for ( auto &child : adj[node] )
    {
        if ( child != par && child != Big[node] )
            collect( child, node, 1 ) ;
    }

    ans[node] = sum[Max] ;
    
    if ( !keep )
        collect( node, par, -1 ) ;
}
void solve()
{
    cin >> n ;
    for ( int i = 1 ; i <= n ; i++ )
        cin >> c[i] ;

    for ( int i = 0 ; i < n - 1 ; i++ )
    {
        int u, v ;
        cin >> u >> v ;
        adj[u].push_back( v ) ;
        adj[v].push_back( u ) ;
    }

    
    pre( 1, 1 ) ;
    dfs( 1, 1, true ) ;
    for ( int i = 1 ; i <= n ; i++ )
        cout << ans[i] << " " ;

}
signed main ()
{

    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
    #endif

   int t=1;
//    cin >> t;
   while(t--)
   {
    solve();
    cout << "\n" ;
   }
}