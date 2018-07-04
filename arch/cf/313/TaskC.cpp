#include "../../../l/lib.h"
 #include "../../../l/mod.h"

class TaskC {
public:
void solve(istream& cin, ostream& cout) {
    int H, W, N; cin >> H >> W >> N;
    vector<pii> X(N); cin >> X;
    X.push_back({H,W});
    sort(X.begin(),X.end());
    auto F = FieldMod::fact(H+W);
    auto I = FieldMod::invfact(H+W);
    vector<FieldMod> Valid(N+1);
    for (int i = 0; i < N+1; ++i) {
        int a = X[i].x-1;
        int b = X[i].y-1;
        Valid[i] = F[a+b] * I[a] * I[b];
        for (int j = 0; j < i; ++j) {
            int c = X[j].x-1;
            int d = X[j].y-1;
            if (c <= a && d <= b) {
                Valid[i] -= F[a+b-c-d] * I[a-c] * I[b-d] * Valid[j];
            }
        }
    }

    cout << Valid[N];
}
};
