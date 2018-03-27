#include "../l/lib.h"
// #include "../l/mod.h"

class boltgoyf {
public:
    void solve(istream& cin, ostream& cout) {
        int K; cin >> K;
        string S;
        set<string> Z{"artifact", "creature", "enchantment", "instant", "land", "planeswalker", "sorcery", "tribal"};
        set<string> Q{"instant"};
        while (cin >> S) {
            if (Z.find(S) != Z.end()) Q.insert(S);
        }

        if (Q.size() < 3) {
            cout << "ANO\n";
        } else {
            cout << "NIE\n";
        }
    }
};
