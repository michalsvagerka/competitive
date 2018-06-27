#include "../../../l/lib.h"
#include "../../../l/mod.h"

class TaskC {
public:
void solve(istream& cin, ostream& cout) {
    string S; cin >> S;
    int N; cin >> N;
    vector<string> Q(N);
    for (int i = 0; i < N; ++i) {
        cin >> Q[N-1-i];
    }

    vector<pair<FieldMod,FieldMod>> W(10);
    for (int i = 0; i < 10; ++i) W[i] = {i, 10};

    for (string&q:Q) {
        int d = q[0]-'0';
        FieldMod p = 1;
        FieldMod c = 0;
        for (int i = 3; i < q.size(); ++i) {
            c *= W[q[i]-'0'].y;
            c += W[q[i]-'0'].x;
            p *= W[q[i]-'0'].y;
        }
        W[d] = {c, p};
    }

    FieldMod p = 1;
    FieldMod c = 0;
    for (int i = 0; i < S.size(); ++i) {
        c *= W[S[i]-'0'].y;
        c += W[S[i]-'0'].x;
    }
    cout << c << endl;
}
};
