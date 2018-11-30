#include "../l/lib.h"
#include "../l/mod.h"

auto F = FieldMod::fact(3e6);
auto I = FieldMod::invfact(3e6);

class ESightseeingPlan {
public:
    
    FieldMod ways(int a, int b) {
        return F[a+b+2] * I[a+1] * I[b+1] - 1;
    }
    
    void solve(istream& cin, ostream& cout) {
        vector<int> X(6), Y(6); cin >> X >> Y;

        FieldMod tot = 0;
        vector<int> X1{X[0], X[1]+1}, Y1{Y[0],Y[1]+1}, X2{X[5],X[4]-1}, Y2{Y[5],Y[4]-1};
        for (int a = 0; a < 2; ++a) {
            for (int b = 0; b < 2; ++b) {
                for (int c = 0; c < 2; ++c) {
                    for (int d = 0; d < 2; ++d) {
                        int neg = a^b^c^d;
                        FieldMod cur = 0;
                        for (int s = X[2]; s <= X[3]; ++s) {
                            int t1 = Y[2]-1, t2 = Y[2];
                            cur -= FieldMod{s-X[2]} * ways(s-X1[a], t1-Y1[b]) * ways(X2[c]-s, Y2[d]-t2);
                            t1 = Y[3], t2 = Y[3]+1;
                            cur += (Y[3]-Y[2]+1+s-X[2]) * ways(s-X1[a], t1-Y1[b]) * ways(X2[c]-s, Y2[d]-t2);
                        }

                        for (int t = Y[2]; t <= Y[3]; ++t) {
                            int s1 = X[2]-1, s2 = X[2];
                            cur -= FieldMod{t-Y[2]} * ways(s1-X1[a], t-Y1[b]) * ways(X2[c]-s2, Y2[d]-t);
                            s1 = X[3], s2 = X[3]+1;
                            cur += (X[3]-X[2]+1+t-Y[2]) * ways(s1-X1[a], t-Y1[b]) * ways(X2[c]-s2, Y2[d]-t);
                        }

                        if (neg) tot -= cur; else tot += cur;
                    }
                }
            }
        }
//        for (int s = X[2]; s <= X[3]; ++s) {
//            for (int t = Y[2]; t <= Y[3]; ++t) {
//                FieldMod x = ways(s - X[0], t - Y[0]) - ways(s - X[1]-1, t - Y[0]) -
//                           ways(s - X[0], t - Y[1]-1) + ways(s - X[1]-1, t - Y[1]-1);
//                FieldMod y = ways(X[5] - s, Y[5] - t) - ways(X[4]-1 - s, Y[5] - t) -
//                           ways(X[5] - s, Y[4]-1 - t) + ways(X[4]-1 - s, Y[4]-1 - t);
//                tot += x * y;
//            }
//        }

        cout << tot << '\n';
    }
};
