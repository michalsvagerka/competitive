#include "../../../l/lib.h"
// #include "../l/mod.h"

class ncpc12i {
public:
    vector<string> W,T;
    vector<int> ass, C, sol;
    vector<bool> used;
    vector<int> unass;


    int test(int t) {
        if (t == T.size()) {
            sol = ass;
            for (int ua: unass) {
                string S = T[ua];
                for (char &s:S) s = char(sol[s-'a']+'a');
//                cerr << "Unassigned " << T[ua] << ' ' << S << endl;
                if (find(W.begin(),W.end(),S) != W.end()) return 0;
            }

//            for (int i = 0; i < T.size(); ++i) {
//                for (char w: T[i]) cerr << char(sol[w-'a']+'a');
//                cerr << " \n"[i == T.size()-1];
//            }

            return 1;
        }

        vector<int> cur;
        bool hasAssign = false;
        bool hasNonAssigned = false;
        for (char w:T[t]) {
            if (ass[w-'a'] == -1) cur.push_back(w-'a');
            hasAssign |= (!--C[w-'a'] && ass[w-'a'] == -1);
            hasNonAssigned |= ass[w-'a']==-1;
        }

//        cerr << "Has assign " << T[t] << ' ' << hasAssign << endl;
//        cerr << ass << used << cur;
        int ans = 0;
        unass.push_back(t);
        if (!hasAssign) ans += test(t+1);
        unass.pop_back();
        if (ans > 1) return ans;

        for (string &w: W) {
            if (w.size() == T[t].size()) {
                bool ok = true;
                for (int i = 0; i < w.size(); ++i) {
                    char v = T[t][i] - 'a';
                    char z = w[i] - 'a';
                    if (ass[v] != -1 && ass[v] != z) ok = false;
                    else if (ass[v] == -1 && used[z]) ok = false;
                    else if (ass[v] == -1 && !used[z]) {
                        ass[v] = z;
                        used[z] = true;
                    }
                }

//                cerr << "Trying " << T[t] << '=' << w << ' ' << ok << endl;
//                cerr << ass << used;

                if (ok) ans += test(t+1);
                if (ans > 1) return ans;

                for (int c:cur) {
                    if (ass[c] != -1) {
                        used[ass[c]] = false;
                        ass[c] = -1;
                    }
                }
//                cerr << ass << used;
            }
        }

        for (char w:T[t]) ++C[w-'a'];
        return ans;
    }


    void solve(istream& cin, ostream& cout) {
        W = {"be", "our", "rum", "will", "dead", "hook", "ship", "blood", "sable", "avenge", "parrot", "captain"};

        vector<string> TTT;
        string t; while (cin >> t) {
            TTT.push_back(t);
            if (find(T.begin(),T.end(),t) == T.end()) T.push_back(t);
        }
        set<char> Z;
        C = vector<int>(26, 0);
        for (string w:T) for (char c:w) Z.insert(c), C[c-'a']++;
        if (Z.size() > 20) {
            cout << "Impossible\n";
            return;
        }

        ass = vector<int>(26, -1);
        used = vector<bool>(26, false);

        int times = test(0);
        if (times == 1) {
            for (int i = 0; i < TTT.size(); ++i) {
                for (char w: TTT[i]) cout << char(sol[w-'a']+'a');
                cout << " \n"[i == TTT.size()-1];
            }
        } else {
            cout << "Impossible\n";
        }
    }
};
