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
#define int long long
#define ull unsigned long long
#define input(v) for ( auto &x : v ) cin >> x
#define output(v) for ( auto &x : v ) cout << x << " "; 
#define all(v) v.begin(), v.end()
#define x first
#define y second

vector<int> KMP( string &s )
{
      int n = s.size() ;
      vector<int> pi ( n ) ;
      
      for ( int i = 1, j = 0 ; i < n ; i++ )
      {
            while ( j && s[i] != s[j] )
                  j = pi[j-1] ;
            if ( s[i] == s[j] )
                  j++ ;
            pi[i] = j ;
      }
      return pi ;
}
void solve()
{
      int m ;
      string s, p ;
      int cnt = 1 ;
      while ( cin >> m )
      {
            cin.ignore() ;
            getline( cin, p ) ;
            getline( cin, s ) ;

            int n = s.size() ;
            vector<int> pi = KMP( p ) ;

            vector<int> ans ;
            for ( int i = 0, j = 0 ; i < n ; i++ )
            {
                  while ( j && s[i] != p[j] )
                        j = pi[j-1] ;
                  if ( s[i] == p[j] )
                  {
                        j++ ;
                        if ( j == m )
                        {
                              ans.push_back( i - m + 1 ) ;
                              j = pi[j-1] ;
                        }
                  }
            }
            if ( ans.size() )
            {
                  for ( auto &x : ans )
                        cout << x << '\n' ;
            }
            else
                  cout << '\n' ;
      }
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
//     cout << "\n" ;
   }
}