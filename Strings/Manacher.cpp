#include <bits/stdc++.h>
using namespace std ;

struct Manacher
{
      int n ;
      string s ;
      string t ;
      vector<int> ans ;
      Manacher( string &s )
      {
            this->s = s ;
            Build() ;
      }
      string convert( string s )
      {
            string t ;
            for ( auto &x : s )
            {
                  t += '#' ;
                  t += x ;
            }
            t += '#' ;
            return t ;
      }
      void Build()
      {
            t = convert( s ) ;
            n = t.size() ;
            t = "$" + t + "^" ;
            vector<int> p ( n + 2 ) ;
            int l = 0, r = 1 ;
            for ( int i = 1 ; i <= n ; i++ )
            {
                  if ( i <= r )
                        p[i] = min( r - i, p[ l + ( r -  i ) ] ) ;
      
                  while ( t[i-p[i]] == t[i+p[i]] )
                        p[i]++ ;
      
                  if ( i + p[i] > r )
                        l = i - p[i], r = i + p[i] ;
            }
            t = t.substr( 1, t.size() - 2 ) ;
            ans = vector<int>( p.begin() + 1, p.end() - 1 ) ;
      }
      int longest( int i )
      {
            return ans[i] - 1 ;
      }
      int Longest_Length()
      {
            int Max = 1 ;
            for ( int i = 0 ; i < t.size() ; i++ )
            {
                  Max = max( Max, longest( i ) ) ;
            }
            return Max ;
      }
      string Longest_Plaindrome()
      {
            int length = Longest_Length() ;
            for ( int i = 0 ; i < n ; i++ )
            {
                  if ( length == longest( i ) )
                  {
                        string curr = t.substr( i - ans[i] + 1 , ans[i] * 2 - 1 ) ;
                        string res ;
                        for ( char &c : curr )
                              if ( c != '#' )
                                    res += c ;
                        return res ;
                  }
            }
            return "" ;
      }
} ;
