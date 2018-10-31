#include "../l/lib.h"
// #include "../l/mod.h"

class flipvowel {
public:
void solve(istream& cin, ostream& cout) {
    string S;
    cin >> S;
    vector<int> V;
    for (int i = 0; i < S.size(); ++i) {
        switch (S[i]) {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                V.push_back(i);
        }
    }
    
    if (V.empty()) {
        cout << 1 << endl;
    } else if (V[0] != 0) {
        cout << 0 << endl;
    } else if (V.size() == 1) {
        cout << S.size() << endl;
    } else {
        cout << V[(V.size()+1)/2] - V[(V.size()-1)/2] << endl;
    }
}
};
