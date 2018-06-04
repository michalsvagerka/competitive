#include "../../../l/lib.h"
#include "../../../l/suffixarray.h"
#include "../../../l/consttree.h"

class wattoandmechanism {
public:
    bool brute(const string&s, const string&t) {
        int d = 0;
        for (int i = 0; i < s.size(); ++i) {
            d += s[i] != t[i];
            if (d >= 2) return false;
        }
        return d==1;
    }

    void solve(istream& cin, ostream& cout) {
        int N,Q; cin >> N >> Q;
        vector<string> S(N), T(Q);
        cin >> S >> T;

        vector<vector<int>> SS(600001);
        vector<vector<int>> TT(600001);
        for (int i = 0; i < N; ++i) SS[S[i].size()].push_back(i);
        for (int i = 0; i < Q; ++i) TT[T[i].size()].push_back(i);
        vector<bool> Ans(Q,false);
        for (int len = 0; len <= 600000; ++len) {
            if (SS[len].empty() || TT[len].empty()) continue;
            if (SS[len].size() <= 10 || TT[len].size() <= 10) {
                for (int &t: TT[len]) {
                    for (int &s: SS[len]) {
                        if (brute(S[s],T[t])) {
                            Ans[t] = true;
                            break;
                        }
                    }
                }
                continue;
            }

            int L = 0;
            vector<int> W(TT[len].size() + SS[len].size(), -1);
            stringstream SSS;
            for (int z:SS[len]) {
                SSS << S[z] << S[z] << '$';
                L++;
            }

            for (int t:TT[len]) {
                SSS << T[t] << T[t] << '#';
                W[L] = t;
                L++;
            }
            SuffixArray<int, true> SA(SSS.str());
            SSS.clear();
            int H = 2*len+1;

            L *= H;
            ConstTree<int,MinQOp<int>> CT(SA.LCP);
            vector<set<int>> J(len);
            for (int i = 0; i < L; ++i) { if (W[SA.S[i]/H] == -1 && SA.S[i]%H < len) {
                    J[SA.S[i]%H].insert(i);
                }
            }

            for (int i = 0; i < L; ++i) {
                if (W[SA.S[i]/H] == -1 || SA.S[i]%H >= len) continue;
                if (Ans[W[SA.S[i]/H]]) continue;
                int l1 = (i == 0 || SA.LCP[i-1] < len) ? i : bsl(0, i-1, [&](int k) { return CT.get(k,i-1) >= len; });
                int h1 = SA.LCP[i] < len ? i : 1+bsh(i, L-1, [&](int k) { return CT.get(i, k) >= len; });

                int l2 = (l1 == 0 || SA.LCP[l1-1] < len-1) ? l1 : bsl(0, l1-1, [&](int k) { return CT.get(k,i-1) >= len-1; });
                int h2 = SA.LCP[h1] < len-1 ? h1 : 1+bsh(h1, L-1, [&](int k) { return CT.get(i, k) >= len-1; });
                int p = SA.S[i]%H;
                if ((l2 != l1 && J[p].lower_bound(l2) != J[p].lower_bound(l1))
                      || (h2 != h1 && J[p].upper_bound(h1) != J[p].upper_bound(h2))) {
                    Ans[W[SA.S[i]/H]] = true;
                }
            }
        }


        for (int i = 0; i < Q; ++i) {
            cout << (Ans[i]?"YES":"NO") << '\n';
        }
    }
};
