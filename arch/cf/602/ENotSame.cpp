#include "../l/lib.h"

class ENotSame {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        vector<vector<int>> J(N+1);
        for (int i = 0; i < N; ++i) {
            J[A[i]].push_back(i);
        }
        vector<string> S(N+1, string(N, '0'));
        vector<pair<int, vector<int>>> G;
        vector<int> GG;
        for (int i = 0; i <= N; ++i) {
            GG.push_back(i);
        }
        G.push_back({GG.size(), GG});

        for (int k = N; k >= 1; --k) {
            for (int j: J[k]) {
                sort(G.begin(),G.end());
                reverse(G.begin(),G.end());
                auto gg = G[0];
                vector<pair<int, vector<int>>> NewG;
                if (k < gg.x) {
                    for (int i = 0; i < k; ++i) {
                        S[gg.y[i]][j] = '1';
                    }
                    NewG.push_back({k, vector<int>(gg.y.begin(),gg.y.begin()+k)});
                    NewG.push_back({gg.x-k, vector<int>(gg.y.begin()+k,gg.y.end())});
                } else {
                    NewG.push_back({1, vector<int>(gg.y.begin(),gg.y.begin()+1)});
                    NewG.push_back({gg.x-1, vector<int>(gg.y.begin()+1,gg.y.end())});
                    for (int i = 1; i < gg.x; ++i) {
                        S[gg.y[i]][j] = '1';
                    }
                    int left = k - (gg.x-1);
                    for (int w = 1; w < G.size(); ++w) {
                        for (int i = 0; i < min(G[w].x,left); ++i) {
                            S[G[w].y[i]][j] = '1';
                        }
                        left -= min(G[w].x,left);
                    }
                }
                for (int w = 1; w < G.size(); ++w) NewG.push_back(G[w]);
                swap(G, NewG);
            }
        }

        vector<string> T;
        for (string s: S) {
            if (count(s.begin(),s.end(),'0') < N) {
                T.push_back(s);
            }
        }

        cout << T.size() << endl;
        for (string t: T) cout << t << '\n';
    }
};
