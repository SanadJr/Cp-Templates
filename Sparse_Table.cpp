/*
      Sparse Table ( RMQ : Range Minimum Query ) --- Static
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 50005 ;
const int Log = 18 ;
vector<vector<int>> Ans( N, vector<int>( 18 ) ) ;
// Ans [ i ][ j ] indicates the Answer from i to i + 2^j - 1

int operation( int x, int y )
{
      return min( x, y ) ;
}
void SparseTable( vector<int> &a ) // O ( n * log( n ) ) 
{
      int n = a.size() ;

      for ( int i = 0 ; i < n ; i++ )
            Ans[i][0] = a[i] ;

      for ( int j = 1 ; j < Log ; j++ )
      {
            for ( int i = 0 ; i + ( 1 << (j-1) ) < n ; i++ )
            {
                  Ans[i][j] = operation( Ans[i][j-1], Ans[i+(1<<(j-1))][j-1] ) ;
            }
      }
}

int Query( int l, int r ) // O ( Log( n ) )
{
      int Len = r - l + 1 ;
      int res = INT_MAX ;
      for ( int j = Log-1 ; j >= 0 ; j-- )
      {
            if ( Len & ( 1 << j ) )
            {
                  res = operation( res, Ans[l][j] ) ;
            }
            l += ( 1 << j ) ;
      }
      return res ;
}

int SpecialQuery( int l, int r ) // O ( 1 )
{
      /*
            Works only for idempotent associative operations,
            where overlapping segments do not affect the result.
            - Works on ( Minimum, Maximum, Gcd, And, Or, .... ).
            - Doesn't works on ( Sum, XOR, Product ...... ).
      */

      int Len = r - l + 1 ;
      int k = 31 - __builtin_clz( Len ) ; // K indicates the log of Len, You can also use a precalculate method for logs.
      int res = operation( Ans[l][k], Ans[r-(1<<k)+1][k] ) ;
      return res ;
}