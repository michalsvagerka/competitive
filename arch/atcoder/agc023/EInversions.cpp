#include "../l/lib.h"
#include "../l/mod.h"
#include "../l/fenwick.h"

class EInversions {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        vector<pii> C(N);
        for (int i = 0; i < N; ++i) C[i] = {A[i], i};
        sort(C.begin(),C.end());

        vector<FieldMod> NiceProd(N+1, 1);
        for (int i = 0; i < N; ++i) {
            NiceProd[i+1] = ((NiceProd[i] == 0) ? 1 : NiceProd[i]) * (C[i].x - (i+1)) / (C[i].x - i);
        }

        vector<int> PrevZero(N, 0), NextZero(N, 0);
        for (int i = 1; i < N; ++i) PrevZero[i] = (NiceProd[i] == 0) ? i : PrevZero[i-1];
        for (int i = 0; i < N; ++i) NextZero[PrevZero[i]] = i;
        for (int i = 1; i < N; ++i) NextZero[i] = max(NextZero[i], NextZero[i-1]);

        FieldMod ans = 0;
        Fenwick<FieldMod> Fen(N, 0);
        for (int k = N-1; k >= 0; --k) {
            ans += Fen.range(C[k].y, N-1) * (C[k].x - (k+1)) / NiceProd[k+1] / 2;
            Fen.add(C[k].y, NiceProd[k] / (C[k].x - k));
            if (PrevZero[k] == k) {
                for (int l = k; l <= NextZero[k]; ++l) Fen.set(C[l].y, 0);
            }
        }

        for (int k = 0; k < N; ++k) {
            ans += Fen.range(C[k].y, N-1) * NiceProd[k] / (C[k].x - k) / 2;
            Fen.add(C[k].y, (FieldMod{k+1} - FieldMod{C[k].x}) / NiceProd[k+1]);
            if (k == NextZero[k]) {
                for (int l = PrevZero[k]; l <= NextZero[k]; ++l) Fen.set(C[l].y, 0);
            }
        }

        for (int i = 0; i < N; ++i) {
            ans += Fen.range(C[i].y+1, N-1);
            Fen.add(C[i].y, 1);
        }

        for (int i = 0; i < N; ++i) ans *= C[i].x - i;
        cout << ans << '\n';
    }
};
