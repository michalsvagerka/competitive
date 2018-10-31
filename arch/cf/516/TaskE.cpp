#include "../l/lib.h"
// #include "../l/mod.h"

class TaskE {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> A(N);
    cin >> A;
    for (int&a:A) --a;

    vector<string> Q(N, string(N, '.'));
    int j = 0, empty = -1;
    for (int i = 0; i < N; ++i) {
        if (A[i] != i && A[i] != -1) {
            vector<int> Cycle{i};
            for (int k = A[i]; k != i; k = A[k]) Cycle.push_back(k);
            Cycle.push_back(i);
            int W = Cycle.size()-1;
            if (empty == -1) {
                for (int k = 1; k < W; ++k) {
                    bool left = Cycle[k] < Cycle[k+1];
                    Q[j][Cycle[k]] = "\\/"[left];
                    Q[j][Cycle[k+1]] = "\\/"[left];
                    j++;
                }

                empty = Cycle[0];

            } else {
                Q[j][empty] = '/';
                for (int k = 1; k < W; ++k) {
                    bool left = Cycle[k-1] < Cycle[k];
                    Q[j][Cycle[k-1]] = "\\/"[left];
                    Q[j][Cycle[k]] = "\\/"[left];
                    j++;
                }

                Q[j][Cycle[W-1]] = '\\';
                Q[j][empty] = '\\';
                j++;
            }


            for (int c:Cycle) A[c] = -1;
        }
    }

    cout << N - (empty!=-1) << endl;
    for (string s:Q) cout << s << '\n';

}
};
