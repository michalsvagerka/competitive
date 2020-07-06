#include "../l/lib.h"

constexpr int SCALE = 100;
constexpr int BOUNDARY = 1;

class Thermometers {
public:
    void solve(istream& cin, ostream& cout) {
        int Test; cin >> Test;
        for (int t = 0; t < Test; ++t) {
            ll K; int N; cin >> K >> N;
            vector<ll> X(N); cin >> X;
            vector<ll> T(N); cin >> T;
            K *= SCALE;

            int ans = 2*N;
            for (int i = 0; i < N; ++i) {
                X[i] *= SCALE;
                X.push_back(X[i]+K);
                T.push_back(T[i]);
            }

            for (int i = 0; i < N; ++i) {
                ll firstFrom = X[i]+BOUNDARY, firstTo = X[i+1]-BOUNDARY;
                ll prevFrom = X[i]+BOUNDARY, prevTo = X[i+1]-BOUNDARY;
                int cur = N;
                bool broken = false;
                for (int j = 1; j < N; ++j) {
                    ll curFrom = 2 * X[i+j] - prevTo;
                    ll curTo = 2 * X[i+j] - prevFrom;

                    if (curFrom > X[i+j+1] - BOUNDARY) {
                        // that's too far
                        broken = true;
                        cur++;
                        curFrom = X[i+j];
                        curTo = X[i+j+1];
                    } else {
                        if (curTo > X[i+j+1] - BOUNDARY) {
                            ll extraRight = curTo - (X[i+j+1] - BOUNDARY);
                            curTo -= extraRight;
                            if (!broken) {
                                if (j%2 == 1) firstFrom += extraRight;
                                else firstTo -= extraRight;
                            }
                        }
                    }

                    prevFrom = curFrom;
                    prevTo = curTo;
                }

                // do the last one
                ll lastFrom = 2 * X[i+N] - prevTo - K;
                ll lastTo = 2 * X[i+N] - prevFrom - K;
                bool intersect = (lastFrom >= firstFrom && lastFrom <= firstTo) || (lastTo >= firstFrom && lastTo <= firstTo)
                                 || (firstTo >= lastFrom && firstTo <= lastTo) || (firstTo >= lastFrom && firstTo <= lastTo);
                if (!broken) {
                    if (N % 2 == 0) {
                        // this has the same parity, but is not the same interval
                        if (firstFrom != lastFrom) cur++;
                    } else {
                        // different parity, so it goes against
                        if (!intersect) {
                            cur++;
                        }
                    }
                } else {
                    if (!intersect) {
                        cur++;
                    }
                }

                ans = min(ans, cur);
            }

            cout << "Case #" << t+1 << ": " << ans << endl;
        }
    }
};
