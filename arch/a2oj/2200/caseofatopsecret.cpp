#include "../../../l/lib.h"
// #include "../l/mod.h"

class caseofatopsecret {
public:
    void solve(istream& cin, ostream& cout) {
        int N,M; cin >> N >> M;
        vector<pii> Y(N);
        for (int i = 0; i < N; ++i) {
            cin >> Y[i].x;
            Y[i].y = i;
        }
        sort(Y.begin(),Y.end());
        vector<int> X(N), T(N), R(N);
        for (int i = 0; i < N; ++i) {
            X[i] = Y[i].x;
            T[i] = Y[i].y+1;
            R[Y[i].y] = i;
        }

        for (int i = 0; i < M; ++i) {
            int A, L; cin >> A >> L;
            A = R[A-1];
            int P = X[A];

            while (true) {
                int prevA = A;
                int prevL = L;

                auto it = prev(upper_bound(X.begin(), X.end(), P + L));
                L = L - (*it - P);
                P = *it;
                A = distance(X.begin(), it);

                it = lower_bound(X.begin(), X.end(), P - L);
                L = L - (P - *it);
                P = *it;
                A = distance(X.begin(), it);

                if (prevA == A) {
                    if (L == prevL) {
                        cout << T[A] << '\n';
                        break;
                    } else if (2*L >= prevL) {
                        L %= (prevL - L);
                    }
                }

                prevA = A;
                prevL = L;
            }
        }
    }
};
