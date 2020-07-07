#include "../../../l/lib.h"
#include "../../../l/geo.h"

class DIncenters {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        int L; cin >> L;
        vector<int> P(N); cin >> P;
        vector<Point<double>> Q(N);
        for (int i = 0; i < N; ++i) {
            Q[i] = {cos(2*PI*P[i]/L), sin(2*PI*P[i]/L)};
        }

        Point<double> ex = {0,0};
        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j < N; ++j) {
                double a = sqrt(2 - 2 * cos(2*PI*(P[i]-P[j])/L));
                for (int k = j+1; k < N; ++k) {
                    double b = sqrt(2 - 2 * cos(2*PI*(P[j]-P[k])/L));
                    double c = sqrt(2 - 2 * cos(2*PI*(P[i]-P[k])/L));
                    Point<double> v = (Q[k] * a + Q[i] * b + Q[j] * c) * (1.0 / (a + b + c));
                    ex += v;
                }
            }
        }

        ex *= 6.0 / (N * (N-1) * (N-2));
        cout << setprecision(15) << fixed << ex;
    }
};
