#include "../l/lib.h"
#include "../l/fenwick.h"

class lasertag {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> X(N), Y(N);
        vector<char> T(N);

        for (int i = 0; i < N; ++i) {
            cin >> X[i] >> Y[i] >> T[i];
        }

        vector<pii> ByX, ByY;
        for (int i = 0; i < N; ++i) {
            ByX.emplace_back(X[i],i);
            ByY.emplace_back(Y[i],i);
        }
        sort(ByX.begin(),ByX.end());
        sort(ByY.begin(),ByY.end());

        for (int i = 0; i < N; ++i) {
            X[ByX[i].y] = i;
            Y[ByY[i].y] = i;
        }

        Fenwick<int> FR(N+1, 0), FRR(N+1, 0), FL(N+1, 0), FLL(N+1, 0);
        for (int i = 0; i < N; ++i) {
            if (T[i] == 'L') {
                FLL.add(Y[i], 1);
            } else {
                FRR.add(Y[i], 1);
            }
        }

        vector<int> S(N, 0);
        for (int i = 0; i < N; ++i) {
            int j = ByX[i].y;
//            cout << j << ' ' << X[j] << ' ' << Y[j] << ' ' << T[j] << endl;
            if (T[j] == 'L') {
                FLL.add(Y[j], -1);
//                cout << FL.range(0, N) << ' ' << FR.range(Y[j], N) << ' ' << FRR.range(0, Y[j]) << endl;
                S[j] += FL.range(0, N);
                S[j] += FR.range(Y[j], N);
                S[j] += FRR.range(0, Y[j]);
                FL.add(Y[j], 1);
            } else {
                FRR.add(Y[j], -1);

//                cout << FRR.range(0, N) << ' ' << FL.range(0, Y[j]) << ' ' << FLL.range(Y[j], N) << endl;
                S[j] += FRR.range(0, N);
                S[j] += FL.range(0, Y[j]);
                S[j] += FLL.range(Y[j], N);
                FR.add(Y[j], 1);
            }
        }

        for (int s : S) cout << s << '\n';

    }
};
