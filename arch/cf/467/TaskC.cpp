#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskC {
public:
    int N;

    string shift(string S, int Q) {
        string T(N, ' ');
        for (int i = 0; i < Q; ++i) T[i] = S[N-1-i];
        for (int i = 0; i < N-Q; ++i) T[i+Q] = S[i];
        return T;
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        string A,B; cin >> A >> B;

        string C=A,D=B;
        sort(C.begin(),C.end());
        sort(D.begin(),D.end());
        if (C!=D) {
            cout << "-1\n";
            return;
        }

        vector<int> Q;
        for (int i = 0; i < N; ++i) {
            int p = -1;
            for (int r = 0; r < N-i; ++r) {
                if (A[r] == B[i]) { p = r; break; }
            }

            Q.push_back(N-(p+1));
            Q.push_back(1);
            Q.push_back(N);
            A = shift(A, N-(p+1));
            A = shift(A, 1);
            A = shift(A, N);
        }

        cout << Q.size() << endl;
        cout << Q;
    }
};
