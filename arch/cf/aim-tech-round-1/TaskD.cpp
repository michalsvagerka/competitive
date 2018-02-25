#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskD {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> P(N); cin >> P;
        vector<double> DP(N), Z(N);

        maxheap<pair<double,int>> Q;
        double prod = 1;
        for (int i = 0; i < N; ++i) {
            DP[i] = P[i]/100.0;

            Z[i] = 1-DP[i];
            prod *= DP[i];
            Q.push({DP[i] * Z[i] / (1-Z[i]),i});
        }

        double exp = N*prod;
        for (int r = N+1; r < 5e6; ++r) {
            auto q = Q.top(); Q.pop();
            Z[q.y] *= (1-DP[q.y]);
            double prd = prod * (1 + q.x);
            exp += r*(prd-prod);
            prod = prd;
            Q.push({DP[q.y] * Z[q.y] / (1-Z[q.y]), q.y});
        }

//        cerr << fixed << setprecision(10) << prod << endl;
//        if (prod < 1 - 1e-11) {
//            exp += 5e6 * (1 - prod);
//        }
        cout << fixed << setprecision(10) << exp << endl;
    }
};
