#include "../l/lib.h"
// #include "../l/mod.h"

class longjump {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> A(3*N); cin >> A;
    vector<vector<int>> L(N);

    vector<pair<vector<int>, int>> W(N);
    for (int j = 0; j < N; ++j) W[j] = {{}, -j};
    sort(W.begin(),W.end());

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < N; ++j) {
            L[-W[j].y].push_back(A[i*N + j]);
            sort(L[-W[j].y].begin(),L[-W[j].y].end());
            reverse(L[-W[j].y].begin(),L[-W[j].y].end());
        }


        for (int j = 0; j < N; ++j) W[j] = {L[j], -j};
        sort(W.begin(),W.end());
    }

    for (int i = 0; i < N; ++i) {
        cout << -W[N-i-1].y << '\n';
    }
}
};
