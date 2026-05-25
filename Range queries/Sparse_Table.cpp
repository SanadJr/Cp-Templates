#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree<T, null_type, less<T>,
                         rb_tree_tag, tree_order_statistics_node_update>;

template <typename T>
using ordered_multiset = tree<T, null_type, less_equal<T>,
                              rb_tree_tag, tree_order_statistics_node_update>;

#define min_nums(n) st.order_of_key(n)
#define value(n) st.find_by_order(n)
#define ll long long
#define int long long
#define ull unsigned long long
#define input(v)        \
      for (auto &x : v) \
      cin >> x
#define output(v)       \
      for (auto &x : v) \
            cout << x << " ";
#define all(v) v.begin(), v.end()
#define x first
#define y second

class SparseTable
{
private:
      const int N = 500005;
      const int LOG = 22;
      vector<vector<int>> Ans;

      int merge(int x, int y)
      {
            return min(x, y);
      }

public:
      SparseTable()
      {
            Ans.assign(N, vector<int>(LOG, 0));
      }

      void build(vector<int> &nums)
      {
            int n = nums.size();

            for (int i = 0; i < n; i++)
                  Ans[i][0] = nums[i];

            for (int j = 1; j < LOG; j++)
            {
                  for (int i = 0; i + (1 << (j - 1)) < n; i++)
                  {
                        Ans[i][j] = merge(Ans[i][j - 1], Ans[i + (1 << (j - 1))][j - 1]);
                  }
            }
      }

      int Log_query(int l, int r)
      {
            int len = r - l + 1;
            int ans = LLONG_MAX;
            for (int i = LOG - 1; i >= 0; i--)
            {
                  if (len & (1 << i))
                  {
                        ans = merge(ans, Ans[l][i]);
                        l += (1 << i);
                  }
            }
            return ans;
      }

      int One_query(int l, int r)
      {
            /*
                  Works only for idempotent associative operations,
                  where overlapping segments do not affect the result.
                  - Works on ( Minimum, Maximum, Gcd, And, Or, .... ).
                  - Doesn't work on ( Sum, XOR, Product ...... ).
            */
            int len = r - l + 1;
            int k = 31 - __builtin_clz(len);
            int ans = merge(Ans[l][k], Ans[r - (1 << k) + 1][k]);
            return ans;
      }
};