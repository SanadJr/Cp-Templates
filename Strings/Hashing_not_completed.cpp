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

mt19937 rng( chrono::steady_clock::now().time_since_epoch().count() ) ;
int rand( int l, int r )
{
      return uniform_int_distribution<int>( l, r )( rng ) ;
}

struct shash
{
      int base, inv, mod, n ;

      vector<int> pw{1}, invpw{1}, pref{0} ; 

      shash(){} ;
      shash( const string &s, int m, int b )
      {
            base = b ;
            mod = m ;
            n = s.size() ;

            inv = 1 ;
            int curr = base ;
            int e = mod - 2 ;
            while ( e )
            {
                  if ( e & 1 ) inv = ( inv * curr ) % mod ;
                  curr = ( curr * curr ) % mod ;
                  e >>= 1 ;
            }

            for ( int i = 0 ; i < n ; i++ )
            {
                  pw.push_back( ( pw.back() * base ) % mod ) ;
                  invpw.push_back( ( invpw.back() * inv ) % mod ) ;
                  pref.push_back( ( pref.back() + ( s[i] - 'a' + 1 ) * pw[i] ) % mod ) ;
            }
      } 

      int get( int l, int r )
      {
            if ( l == 0 )
                  return pref[r+1] ;
            return ( ( ( ( pref[r+1] - pref[l] + mod ) % mod ) * invpw[l] ) % mod ) ;
      }
} ;
void solve()
{
      // cin >> n ;
      string s, m ;
      cin >> s ;
      int n = s.size() ;
      m = s ;
      reverse( all( m ) ) ;

      const int Mod1 = 1e9 + 7, Mod2 = 1e9 + 9 ;
      const int Base1 = rand( 28, 1e9 ), Base2 = rand( 28, 1e9 ) ;
      
      shash HashS1 ( s, Mod1, Base1 ) ;
      shash HashS2 ( s, Mod2, Base2 ) ;
      shash HashM1 ( m, Mod1, Base1 ) ;
      shash HashM2 ( m, Mod2, Base2 ) ;

      int pos = 0 ;
      int ans = 1 ;
      for ( int i = 0 ; i < n-1 ; i++ )
            if ( s[i] == s[i+1] )
            {
                  pos = i ;
                  ans = 2 ;
            }
      
      for ( int i = 1 ; i < n-1 ; i++ )
      {
            int l = 1, r = min( i, n - i - 1 ), res = 0 ;
            while ( l <= r )
            {
                  int mid = ( l + r ) / 2 ;
                  if ( ( HashS1.get( i-mid, i-1 ) == HashM1.get( n-i-mid-1 , n - i - 2 ) ) && ( HashS2.get( i-mid, i-1 ) == HashM2.get( n-i-mid-1 , n - i - 2 ) ) )
                        res = mid, l = mid + 1 ;
                  else
                        r = mid - 1 ;
            }
            if ( res * 2 + 1 > ans )
                  pos = i - res ;
            ans = max( ans, res * 2 + 1 ) ;
      }

      for ( int i = 1 ; i < n-2 ; i++ )
      {
            if ( s[i] != s[i+1] )
                  continue ;
            int l = 1, r = min( i, n - i ), res = 0 ;
            while ( l <= r )
            {
                  int mid = ( l + r ) / 2 ;
                  if ( ( HashS1.get( i-mid, i-1 ) == HashM1.get( n-i-mid-2 , n - i - 3 ) ) && ( HashS2.get( i-mid, i-1 ) == HashM2.get( n-i-mid-2 , n - i - 3 ) ) )
                        res = mid, l = mid + 1 ;
                  else
                        r = mid - 1 ;
            }
            if ( res * 2 + 2 > ans )
                  pos = i - res ;
            ans = max( ans, res * 2 + 2 ) ;
      }
      
      cout << s.substr( pos, ans ) ;

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