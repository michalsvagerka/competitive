#include "../../../l/lib.h"
// #include "../l/mod.h"

class tanyapassword {
public:
    map<string, vector<string>> In, Out;

    void buildEulerFrom(string v, vector<string> &cycle_out) {
        while (!Out[v].empty()) {
            cycle_out.push_back(v);
            string u = Out[v].back();
            Out[v].pop_back();
            v = u;
        }
        cycle_out.push_back(v);
    }

    void buildEuler(stringstream &ans, vector<string> &tour) {
        for (string&s: tour) {
            vector<string> EE;
            buildEulerFrom(s, EE);
            EE.pop_back();
            buildEuler(ans, EE);
            ans << s[1];
        }
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<string> S(N); cin >> S;
        if (N == 1) {
            cout << "YES\n" << S[0] << endl;
            return;
        }

        for (int i = 0; i < N; ++i) {
            string A = S[i].substr(0,2);
            string B = S[i].substr(1,2);
            Out[A].push_back(B);
            In[B].push_back(A);
        }

        string BEG, END;
        for (auto&s:Out) {
            int d = s.y.size() - In[s.x].size();
            if (d >= 2) { cout << "NO\n"; return; }
            if (d == 1 && !BEG.empty()) { cout << "NO\n"; return; }
            if (d == 1) BEG = s.x;
        }


        for (auto&s:In) {
            int d = s.y.size() - Out[s.x].size();
            if (d >= 2) { cout << "NO\n"; return; }
            if (d == 1 && !END.empty()) { cout << "NO\n"; return; }
            if (d == 1) END = s.x;
        }

        if (BEG.empty()) BEG = END = Out.begin()->x;

        map<string, vector<string>> Eulers;
        vector<string> orig;
        buildEulerFrom(BEG, orig);

        stringstream Ans;
        Ans << BEG[0];
        buildEuler(Ans, orig);
        string ans = Ans.str();

        if (ans.size() == N+2) {
            cout << "YES\n";
            cout << ans << endl;
        } else {
            cout << "NO\n";
        }

    }
};
