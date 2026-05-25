#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long
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
      // Returns the change without save it!
      int change(int idx, int val) 
      {
            int res ;

            if ( idx == 0 ) 
            {
                  if ( n == 1 )
                        res = val % mod ;
                  else
                  {
                        int suf = get(1, n-1 ) ;
                        res  = ( val + suf * pw[1] ) % mod ;
                  }
            }
            else if ( idx == n-1 ) 
            {
                  if ( n == 1 )
                        res = val % mod ;
                  else
                  {
                        int pre = get(0, n-2);
                        res  = ( pre + val * pw[n-1] ) % mod ;
                  }
            }
            else 
            {
                  int pre = get( 0, idx - 1 ) ;
                  int suf = get(idx + 1, n - 1 ) ;
                  int len = n - idx;

                  res = ( pre + ( val * pw[idx] ) % mod + ( suf * pw[idx+1] ) % mod ) % mod ;
            }
            return res;
      }
      
} ;
const int Mod = 1e9 + 7, Mod2 = 1e9 + 9 ;
const int Base = rand( 28, 1e9 ), Base2 = rand( 29, 1e9 ) ;
