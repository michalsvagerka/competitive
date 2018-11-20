#include "../l/lib.h"
// #include "../l/mod.h"

class Stockholm {
public:
    struct Calc {

        ll A, B;
        int ans;
        map<pair<ll,ll>, int> Ans;

        int count(ll x, ll y) {
            auto it = Ans.find({x,y});
            if (it != Ans.end()) return it->y;
            
            if (x == y) return 0;
            if (x > y) swap(x, y);
            if (x == -2 && y == -1) return 1;
            int cur = 1e9;
            vector<ll> C;
            getCand(y, C);
            for (ll c: C) {
                if (c != y) {
                    cur = min(cur, 1 + count(c, x));                        
                }
            }
            
            return Ans[{x,y}] = Ans[{y,x}] = cur;
        }

        void getCand(ll x, vector<ll>&y) {
            y.push_back(x);
            if (x == 1) {
                y.push_back(-1);
                y.push_back(-2);
            } else {
                int b = logceil(x-1);
                if (x == (1LL<<b)-1) {
                    y.push_back(-2);
                } else {
                    ll g = x;
                    while (g&1) g>>=1;
                    g >>=1;
                    y.push_back(g);
                }
                
                if (x == (1LL<<b)) {
                    y.push_back(-1);
                } else {
                    ll g = x;
                    while (!(g&1)) g>>=1;
                    g >>= 1;
                    y.push_back(g);
                }
            }
        }
        
        void calc() {
            Ans.clear();
            
            vector<ll> X, Y;
            getCand(A, X);
            getCand(B, Y);
            ans = 1e9;
            for (ll a:X) for (ll b:Y) {
                ans = min(ans, count(a, b));
            }
        }

        void read(istream& cin) {
            cin >> A >> B;
            ++A; ++B;
        }


        void write(ostream &cout) {
            cout << ans << '\n';
        }
    };


    void solve(istream& cin, ostream& cout) {
        ui T; cin >> T;
        for (int t = 1; t <= T; ++t) {
            Calc c;
            c.read(cin);
            c.calc();
            cout << "Case #" << t << ": ";
            c.write(cout);
        }
    }

};
