#include "../l/lib.h"

class C2NauuoAndPicturesHardVersion {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<int> A(N); cin >> A;
        for (int&a: A) a -= a==0;
        vector<int> W(N); cin >> W;
        int dec = 0, asc = 0;
        for (int i = 0; i < N; ++i) {
            if (A[i] < 0) dec += W[i]; else asc += W[i];
        }

        for (int i = 0; i < N; ++i) {
            vector2<FF> D(M+1, M+1, 0);
            int dd = (A[i] < 0) ? dec - W[i] : dec;
            int aa = (A[i] > 0) ? asc - W[i] : asc;
            D[0][0] = 1;
            for (int j = 0; j < M; ++j) {
                vector2<FF> E(M+1, M+1, 0);
                for (int k = 0; k <= j; ++k) { // changes of myself
                    for (int l = 0; l+k <= j; ++l) { // changes of dec
                        int m = j-(k+l); // changes of inc
                        FF cur = W[i]+A[i]*k;
                        FF curDec = dd-l;
                        FF curAsc = aa+m;
                        FF curTot = cur + curDec + curAsc;
                        E[k][l+1] += D[k][l] * curDec / curTot;
                        E[k][l] += D[k][l] * curAsc / curTot;
                        E[k + 1][l] += D[k][l] * cur / curTot;
                    }
                }
                swap(E,D);
            }
            FF exp = 0;
            for (int j = 0; j <= M; ++j) {
                FF cur = W[i]+A[i]*j;
                for (int k = 0; k <= M; ++k) {
                    exp += cur * D[j][k];
                }
            }
            cout << exp << '\n';
        }
    }
};
