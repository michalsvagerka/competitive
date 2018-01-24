#include "../l/lib.h"
#include <cstring>
// #include "../l/mod.h"

constexpr int PLUS = -1;
constexpr int TIMES = -2;
constexpr int VAR = -3;

struct Term {
    ll t;
    Term *l,*r;
    Term(ll t,Term*l=nullptr,Term*r=nullptr) : t(t),l(l),r(r) {}

    inline ui eval(ui x, ui N) {
        if (t==VAR) return x%N;
        else if (t==PLUS) return (ll(l->eval(x,N)) + r->eval(x,N))%N;
        else if (t==TIMES) return  (ll(l->eval(x,N)) * r->eval(x,N))%N;
        else return t%N;
    }
};

ui V[11000000];

class periodic {
public:
    void solve(istream& cin, ostream& cout) {
        ui N; cin >> N;
        while (N) {
            int n; cin >> n;
            vector<string> Z;
            string q; cin >> q;
            while (q != "%") {
                Z.push_back(q);
                cin >> q;
            }
            Z.pop_back();

            stack<Term*> S;
            for (string&z:Z) {
                Term *a,*b;
                switch (z[0]) {
                    case 'x':
                        S.push(new Term{VAR});
                        break;

                    case '+':
                        b = S.top(); S.pop();
                        a = S.top(); S.pop();
                        S.push(new Term{PLUS,a,b});
                        break;

                    case '*':
                        b = S.top(); S.pop();
                        a = S.top(); S.pop();
                        S.push(new Term{TIMES,a,b});
                        break;

                    default: {
                        stringstream ss(z);
                        ll i; ss >> i;
                        S.push(new Term{i});
                        break;
                    }
                }
            }

            Term *t = S.top();
            memset(V, 0, sizeof(ui)*N);
            V[n] = 1;
            for (ui i = 2;; ++i) {
                n = t->eval(n, N);
                if (V[n] != 0) {
                    cout << i-V[n] << '\n';
                    break;
                }
                V[n] = i;
            }

            cin >> N;
        }
    }
};
