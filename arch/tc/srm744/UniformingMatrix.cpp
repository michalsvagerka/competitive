#include "../l/lib.h"
// #include "../l/mod.h"

class UniformingMatrix {
public:
    string isPossible(vector<string> M) {
        for (char ch = '0'; ch <= '1'; ++ch) {
            auto N = M;
            int chg = 0;
            for (auto &n : N) {
                if (n[0] != ch) {
                    chg++;
                    for (auto &q: n) q ^= 1;
                }
            }

            for (int i = 0; i < N[0].size(); ++i) {
                for (int j = 1; j < N.size(); ++j) {
                    if (N[j][i] != N[0][i]) {
                        return "impossible";
                    }
                }
                chg += N[0][i] == '0';
            }

            cerr << N;
            cerr << chg << endl;
            if (chg % 2 == 0) return "possible";
        }

        return "impossible";
    }

    void solve(istream& cin, ostream& cout) {
        cout << isPossible({"0"}) << endl;
        cout << isPossible({"1101",
                            "0010"}) << endl;
        cout << isPossible({"11111",
                            "11111",
                            "11111",
                            "11111",
                            "11111",
                            "11111",
                            "11111",
                            "11111"}) << endl;
        cout << isPossible({"110",
                    "001",
                    "110"}) << endl;
        cout << isPossible({"01010",
                            "10101",
                            "01010",
                            "01010"}) << endl;
        cout << isPossible({"01011",
                            "10100",
                            "01011",
                            "01011"}) << endl;
        cout << isPossible({"111001",
                            "000110",
                            "000110",
                            "111001",
                            "111001",
                            "000110"}) << endl;
    }
};
