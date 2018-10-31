#include "../l/lib.h"
// #include "../l/mod.h"

class TaskE {
public:
void solve(istream& cin, ostream& cout) {
    int N, K; cin >> N >> K;
    vector<string> A(N+1); cin >> A;
    int turns = 0;
    ll curValue = 0;

    for (int i = N; i >= 0; --i) {
        
        curValue *= K;
        if (A[i] != "?") {
            turns++;
            stringstream S(A[i]);
            int x; S >> x;
            curValue += x;
        }


        if (curValue > 1e12) curValue = 1e12;
        if (curValue < -1e12) curValue = -1e12;
    }

    bool humanTurn = turns%2;

    if (K == 0) {
        cout << (A[0] == "0" || (A[0] == "?" && humanTurn) ? "Yes" : "No") << endl;
    } else if (turns == N+1) {
        cout << (curValue ? "No" : "Yes") << endl;
    } else {
        cout << (N%2 ? "Yes" : "No") << endl;
    }

}
};
