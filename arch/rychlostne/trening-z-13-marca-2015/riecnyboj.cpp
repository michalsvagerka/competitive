#include "../l/lib.h"
#include "../l/avl.h"

class riecnyboj {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        avl<ll,ll> T;
        ll res = 0;
        ll l = 0;
        for (int i = 0; i < N; ++i) {
            ll a; cin >> a;
            res += a*(a-1)/2;
            T.insert(l, a);
            l += a;
        }
        cout << res << '\n';

        int K; cin >> K;
        for (int k = 0; k < K; ++k) {
            int t,i; cin >> t >> i; --i;
            if (t == 1) {
                auto m = T.select(i);
                if (i == 0) {
                    auto n = T.select(i+1);
                    res += n->v * m->v;
                    m->v += n->v;
                    T.remove(n->k);
                } else if (i == T.size()-1) {
                    auto n = T.select(i-1);
                    res += n->v * m->v;
                    n->v += m->v;
                    T.remove(m->k);
                } else {
                    auto n = T.select(i-1), o = T.select(i+1);
                    ll a = m->v / 2;
                    ll b = m->v - a;
                    res -= a * b;
                    res += a * n->v + b * o->v;
                    n->v += a;
                    o->v += b;
                    o->k -= b;
                    T.remove(m->k);
                }
            } else {
                auto m = T.select(i);
                ll a = m->v / 2;
                ll b = m->v - a;
                res -= a * b;
                m->v = a;
                T.insert(m->k + a,b);
            }

            //T.foreach([&](int k,int v){cout << k << ':' << v << ' ';});
            //cout << endl;

            cout << res << '\n';
        }
    }
};
