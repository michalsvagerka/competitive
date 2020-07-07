#include "../../../l/lib.h"
#include "../../../l/mod.h"

class EMedianReplace {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        int N = S.size();
        map<string, FieldMod> D{{"", FieldMod{1}}};

        for (char s: S) {
            map<string, FieldMod> E;
            for (auto d: D) {
                for (char c = '0'; c <= '1'; ++c) {
                    if (s + c == '0' + '1') continue;
                    string newD = d.x;
                    newD.push_back(c);
                    int M = newD.size();
                    if (M >= 2 && newD[M-1] == '1' && newD[M-2] == '0') {
                        newD.pop_back();
                        newD.pop_back();
                        M -= 2;
                    }

                    if (M >= 3 && newD[M-2] == '0' && newD[M-3] == '0') {
                        newD.pop_back();
                        newD.pop_back();
                        M -= 2;
                    }

                    if (M >= 3 && newD[M-1] == '1') {
                        newD.pop_back();
                        M -= 2;
                    }
                    E[newD] += d.y;
                }
            }
            swap(D,E);
        }
        cout << D["1"] + D["11"] + D["110"] + D["1100"] << '\n';
    }
};
