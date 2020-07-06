#include "../l/lib.h"

class RankingStudents {
public:
    string rankingPossible(int n, vector <int> f, vector <int> a, vector <int> b) {
        int M = a.size();
        vector<vector<int>> e(n);
        vector<int> C(n, 1);
        vector<vector<int>> F(n);
        for (int i = 0; i < n; ++i) {
            F[f[i]].push_back(i);
        }
        for (int i = 0; i < M; ++i) {
            e[b[i]].push_back(a[i]);
            C[a[i]]++;
        }

        vector<int> Q;
        for (int i = 0; i < n; ++i) {
            for (int j: F[n-1-i]) {
                if (--C[j] == 0) {
                    Q.push_back(j);
                }
            }

            if (Q.empty()) return "Impossible";
            int q = Q.back();
            Q.pop_back();
            for (int r: e[q]) {
                if (--C[r] == 0) {
                    Q.push_back(r);
                }
            }
        }

        return "Possible";
    }
    void solve(istream& cin, ostream& cout) {
        cout << rankingPossible(3,{0, 1, 2},{0, 1},{2, 2}) << endl;
        cout << rankingPossible(3,{2, 2, 2},{0, 1, 2},{1, 2, 0}) << endl;
        cout << rankingPossible(4,{1, 1, 1, 3},{1},{3}) << endl;
        cout << rankingPossible(6,{5, 5, 5, 1, 5, 4},{0, 2, 4},{1, 3, 5}) << endl;
    }
};
