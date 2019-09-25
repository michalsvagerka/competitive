#include "../l/lib.h"
#include "../l/mod.h"
typedef Field<998244353> FF;


class C1NauuoAndPicturesEasyVersion {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M;
        cin >> N >> M;
        vector<int> A(N);
        cin >> A;
        for (int &a: A) a -= a == 0;
        vector<int> W(N);
        cin >> W;
        int dec = 0, asc = 0;
        for (int i = 0; i < N; ++i) {
            if (A[i] < 0) dec += W[i]; else asc += W[i];
        }

        FF dieProbability = 0;

        {
            vector<FF> D(M + 1, 0);
            D[0] = 1;
            for (int j = 0; j < M; ++j) {
                vector<FF> E(M + 1, 0);
                for (int k = 0; k <= j; ++k) {
                    FF curDec = dec - k;
                    FF curAsc = asc + (j - k);
                    FF curTot = curDec + curAsc;
                    FF d = D[k] / curTot;
                    if (curDec != 0) {
                        dieProbability += d;
                        E[k + 1] += d * (curDec - 1);
                    }
                    E[k] += d * curAsc;
                }
                swap(E, D);
            }
        }

        FF good;
        {
            vector2<FF> D(M+1, M+1, 0);
            for (int i = 0; i <= M; ++i) D[M][i] = 1;

            for (int i = M-1; i >= 0; --i) {
                for (int j = 0; j <= i; ++j) {
                    FF curAsc = asc + j;
                    FF curDec = dec + j-i;
                    FF curTot = curAsc + curDec;
                    D[i][j] += (D[i+1][j+1] * (curAsc + 1) + D[i+1][j] * curDec) / curTot;
                }
            }
            good = D[0][0];
        }

        for (int i = 0; i < N; ++i) {
            if (A[i] < 0) {
                cout << W[i] * (FF{1} - dieProbability) << '\n';
            } else {
                cout << W[i] * good << '\n';
            }
        }
    }
};
