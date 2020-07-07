#include "../../../l/lib.h"
#include "../../../l/random.h"

class TrianglePath {
public:
    vector <int> construct(int N, int Xmax, int Ymax, vector <int> Xprefix, vector <int> Yprefix, int seed) {
        auto X = Xprefix;
        auto Y = Yprefix;
        auto state = seed;
        while (X.size() < N) {
            state = (state * 1103515245LL + 12345) % (1LL<<31);
            ll xnew = state % (Xmax+1);
            state = (state * 1103515245LL + 12345) % (1LL<<31);
            ll ynew = state % (Ymax + 1);
            if (ynew * Xmax <= (Xmax - xnew) * Ymax) {
                X.push_back(xnew);
                Y.push_back(ynew);
            }
        }

        while (true) {
            vector<int> P;
            P.push_back(random_int{0, N-1}(rng));
            vector<bool> Used(N, false);
            Used[P[0]] = true;
            ll tot = 0;
            for (int i = 1; i < N; ++i) {
                ll dist = 1e18;
                int b = -1;
                for (int j = 0; j < N; ++j) {
                    if (!Used[j]) {
                        ll a = ll(X[P[i-1]]-X[j]) * (X[P[i-1]]-X[j]) + ll(Y[P[i-1]]-Y[j]) * (Y[P[i-1]]-Y[j]);
                        if (a < dist) {
                            dist = a;
                            b = j;
                        }
                    }
                }
                P.push_back(b);
                Used[b] = true;
                tot += dist;
            }
            
            
            if (tot <= 1LL*Xmax*Xmax + 1LL*Ymax*Ymax)
            return P;
        }
        

        return {};
    }

    void solve(istream& cin, ostream& cout) {
        cout << construct(3,40,30,{0, 40, 0},{0, 0, 30},47) << endl;
        cout << construct(5,7,7,{5, 2, 4, 1, 3},{1, 4, 2, 5, 3},47) << endl;
        cout << construct(3,54321,12345,{47, 47, 47},{47, 47, 47},47474747) << endl;
        cout << construct(10,12,14,{4, 7},{7, 4},1) << endl;
    }
};
