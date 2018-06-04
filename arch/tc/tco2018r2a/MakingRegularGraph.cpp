#include "../../../l/lib.h"
// #include "../l/mod.h"

class MakingRegularGraph {
public:

    vector<vector<int>> E;
    vector<int> D;
    vector<set<int>> W;

    bool ispossible() {
        if (W[0].size() == 0 && W[1].size() == 0) {
            return true;
        }

        if (W[0].size() <= 2 && W[1].size() == 0) {
            return false;
        }

        if (W[0].size() == 0 && W[1].size() == 2) {
            int a = *W[1].begin();
            int b = *next(W[1].begin());
            if (E[a][0] == b) return false;
            else return true;
        }

        return true;
    }


    vector <int> addEdges(int n, vector <int> x, vector <int> y) {
        E.resize(n); D = vector<int>(n, 0);
        for (int i = 0; i < x.size(); ++i) {
            E[x[i]].push_back(y[i]);
            E[y[i]].push_back(x[i]);
            D[x[i]]++;
            D[y[i]]++;
        }

        W.resize(3);
        for (int i = 0; i < n; ++i) {
            W[D[i]].insert(i);
        }

        vector<int> ans;
        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                if (D[i] < 2 && D[j] < 2) {
                    if (D[i] == 0 || E[i][0] != j) {
                        E[i].push_back(j);
                        E[j].push_back(i);
                        W[D[i]].erase(i);
                        W[D[j]].erase(j);
                        D[i]++;
                        D[j]++;
                        W[D[i]].insert(i);
                        W[D[j]].insert(j);

                        if (ispossible()) {
                            ans.push_back(i);
                            ans.push_back(j);
                        } else {
                            E[i].pop_back();
                            E[j].pop_back();
                            W[D[i]].erase(i);
                            W[D[j]].erase(j);
                            D[i]--;
                            D[j]--;
                            W[D[i]].insert(i);
                            W[D[j]].insert(j);
                        }
                    }
                }
            }
        }

        if (!ispossible()) {
            ans.clear();
            ans.push_back(-1);
        }

        return ans;
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        int M; cin >> M;
        vector<int> X(M), Y(M); cin >> X >> Y;
        cout << addEdges(N, X, Y) << '\n';
    }
};
