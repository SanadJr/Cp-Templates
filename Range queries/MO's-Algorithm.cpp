/*
      MO's Algorithm
      Implementation of "MO" with the solution of the sum of ( freq[num] * num ) on range.
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long
#define ull unsigned long long
#define input(v)      \
    for (auto &x : v) \
    cin >> x
#define output(v)     \
    for (auto &x : v) \
        cout << x << " ";
#define all(v) v.begin(), v.end()
#define x first
#define y second

int SQ;
struct query
{
    int l, r, idx;
    bool operator<(query &other)
    {
        if (l / SQ == other.l / SQ)
            return r < other.r;
        return l / SQ < other.l / SQ;
    }
};
void solve()
{
    int n, q;
    cin >> n;
    cin >> q;
    SQ = sqrt(n) + 1;
    vector<int> a(n);
    input(a);

    vector<int> freq(1e6 + 5);
    vector<query> Q;
    for (int i = 0; i < q; i++)
    {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        Q.push_back({l, r, i});
    }
    sort(all(Q));

    int curr = 0;
    auto add = [&](int i)
    {
        curr -= freq[a[i]] * a[i] ;
        freq[a[i]]++;
        curr += freq[a[i]] * a[i] ;
    };
    auto del = [&](int i)
    {
        curr -= freq[a[i]] * a[i] ;
        freq[a[i]]--;
        curr += freq[a[i]] * a[i] ;
    };
    int l = 0, r = -1;
    vector<int> ans(q);
    for (int i = 0; i < q; i++)
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
        ans[x.idx] = curr;
    }
    for (auto &x : ans)
        cout << x << '\n';
}