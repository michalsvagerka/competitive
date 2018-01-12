#include "../l/lib.h"
// #include "../l/mod.h"

vector<double> f{0.1088,0.0181,0.0358,0.0379,0.0939,
                 0.0020,0.0021,0.0251,0.0579,0.0219,
                 0.0399,0.0441,0.0361,0.0599,0.0939,
                 0.0303,0.0000,0.0474,0.0617,0.0576,
                 0.0313,0.0463,0.0000,0.0000,0.0270,0.0300};

class vigenere {
public:
    double apply(vector<string> &S, int i, int l, int p) {
        int r = 0;
        vector<ui> F(26, 0);
        ui ch = 0;
        for (auto &s: S) {
            for (auto &c:s) {
                if ('A' <= c && c <= 'Z') {
                    if (r == i) {
                        c = char('A' + (c-'A'+p)%26);
                        F[c-'A']++;
                        ch++;
                    }
                    r = (r+1)%l;
                }
            }
        }

        double error = 0;
        for (int c = 0; c < 26; ++c) {
            double e = ch*f[c]-F[c];
            error += e*e;
        }
        return error;
    }

    void solve(istream& cin, ostream& cout) {
//        double ff = 0;
//        for (int i = 0; i < 26; ++i) {
//            ff += f[i];
//        }
//        cout << ff << endl;

        vector<string> S;
        while (true) {
            string s;
            getline(cin, s);
            S.push_back(s);
            if (cin.eof()) break;
        }


        double best = 1e100;
        vector<string> ans;
        for (int l = 1; l <= 12; ++l) {
            vector<string> T = S;
            pair<double,int> B{1e100,-1};
            for (int i = 0; i < l; ++i) {
                for (int j = 0; j < 26; ++j) {
                    vector<string> U = T;
                    B = min(B, {apply(U, i, l, j), j});
                }
                apply(T, i, l, B.y);
            }
            double score = apply(T, 0, 1, 0);
            if (score < best) {
                best = score;
                ans = T;
            }
        }

        for (auto s:ans) {
            cout << s << endl;
        }
    }
};
