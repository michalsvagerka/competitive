#include "../l/lib.h"
// #include "../l/mod.h"

class TaskC {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<vector<int>> C(N);
    for (int i = 0; i < N; ++i) {
        int s; cin >> s;
        C[i].resize(s);
        cin >> C[i];
    }

    int a = 0, b = 0;
    vector<int> M;
    for (int i = 0; i < N; ++i) {
        int s = C[i].size();
        for (int j = 0; j < s/2; ++j) {
            a += C[i][j];
            b += C[i][s-1-j];
        }
        if (s%2==1) {
            M.push_back(C[i][s/2]);
        }
    }
    sort(M.begin(),M.end());
    reverse(M.begin(),M.end());
    for (int i = 0; i < M.size(); i+=2) a += M[i];
    for (int i = 1; i < M.size(); i+=2) b += M[i];
    cout << a << ' ' << b << endl;
}
};
