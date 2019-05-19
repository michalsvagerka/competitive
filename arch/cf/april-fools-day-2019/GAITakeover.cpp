#include "../l/lib.h"

class GAITakeover {
public:
    void solve(istream& cin, ostream& cout) {
        cout << "R\nR\nS\nS\nP\nP\nR" << endl;
        vector<string> S(7); cin >> S;

        map<char,char> A;
        if (S[1] == "player") {
            A['R'] = 'R';
        } else if (S[2] == "player") {
            A['R'] = 'S';
        } else {
            A['R'] = 'P';
        }


        if (S[3] == "player") {
            A['S'] = 'S';
        } else if (S[4] == "player") {
            A['S'] = 'P';
        } else {
            A['S'] = 'R';
        }


        if (S[5] == "player") {
            A['P'] = 'P';
        } else if (S[6] == "player") {
            A['P'] = 'R';
        } else {
            A['P'] = 'S';
        }
        
        char last = 'P';
        for (int i = 0; i < 13; ++i) {
            last = A[last];
            cout << last << endl;
        }
    }
};
