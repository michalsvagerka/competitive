#include "../l/lib.h"

class modularq {
public:
    ll cnt(ll r, ll c) {
        if (r == -1 || c == -1) return 0LL;
        r++; c++;
        if (r > c) swap(r,c);
        ll x = r - r%3;
        ll y = c-x; y -= y%3;
        ll cnt = 4*x/3 + x*x + y*r;
        if (c%3==2) cnt += r;
        if (r%3==2) cnt += x+1;
        return cnt;
    }
    
    void solve(istream& cin, ostream& cout) {
        int R1, R2;
        int C1, C2;
        cin >> R1 >> R2 >> C1 >> C2;
        ll a = cnt(R2, C2);
        ll b = cnt(R2, C1-1);
        ll c = cnt(R1-1, C2);
        ll d = cnt(R1-1,C1-1);
        cout << a - b - c + d << endl;
    }
};
