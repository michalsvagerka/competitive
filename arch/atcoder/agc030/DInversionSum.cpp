#include "../l/lib.h"
 #include "../l/mod.h"

class DInversionSum {
public:
void solve(istream& cin, ostream& cout) {
    int N, Q; cin >> N >> Q;
    vector<int> A(N); cin >> A;
    vector<pii> X(Q); cin >> X;

    vector2<FieldMod> I(N,N,0);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            I[i][j] = A[i] > A[j];
        }
    }

    FieldMod inv = FieldMod{1} / 2;
    
    for (pii&x:X) {
        int a = x.x-1;
        int b = x.y-1;
        for (int j = 0; j < N; ++j) {
            if (j != a && j != b) {
                FieldMod f = I[j][a] + I[j][b];
                f *= inv;
                I[j][a] = I[j][b] = f;

                FieldMod g = I[a][j] + I[b][j];
                g *= inv;
                I[a][j] = I[b][j] = g;
            }
        }

        FieldMod f = I[a][b] + I[b][a];
        f *= inv;
        I[a][b] = I[b][a] = f;
    }

    FieldMod ans = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = i+1; j < N; ++j) {
            ans += I[i][j];
        }
    }
    cout << ans * FieldMod{2}.pow(Q) << endl;
}
};
