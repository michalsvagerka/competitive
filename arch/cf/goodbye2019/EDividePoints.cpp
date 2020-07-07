#include "../../../l/lib.h"

class EDividePoints {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<pii> A(N); cin >> A;

        while (true) {
            vector<int> Odd, Even;
            for (int i = 0; i < N; ++i) {
                if ((A[i].x+A[i].y)%2 == 0) {
                    Even.push_back(i+1);
                } else {
                    Odd.push_back(i+1);
                }
            }

            if (!Odd.empty() && !Even.empty()) {
                cout << Odd.size() << '\n';
                cout << Odd;
                return;
            }

            if (Even.empty()) {
                for (int i = 0; i < N; ++i) {
                    A[i].x--;
                }
            }

            Odd.clear(); Even.clear();
            for (int i = 0; i < N; ++i) {
                if (A[i].x%2==0) {
                    Even.push_back(i+1);
                } else {
                    Odd.push_back(i+1);
                }
            }

            if (!Odd.empty() && !Even.empty()) {
                cout << Odd.size() << '\n';
                cout << Odd;
                return;
            }

            if (Even.empty()) {
                for (int i = 0; i < N; ++i) {
                    A[i].x--;
                    A[i].y--;
                }
            }

            for (int i = 0; i < N; ++i) {
                A[i].x /= 2;
                A[i].y /= 2;
            }
        }
//        vector2<ll> D(N, N, 0);
//        for (int i = 0; i < N; ++i) {
//            for (int j = 0; j < N; ++j) {
//                D[i][j] = A[i].squaredDistance(A[j]);
//            }
//        }


    }
};
