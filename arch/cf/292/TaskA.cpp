#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    string S; cin >> S;
    vector<int> C(8, 0);
    for (char s:S) {
        if (s == '2') C[2]++;
        else if (s == '3') C[3]++;
        else if (s == '4') { C[3]++; C[2]+=2; }
        else if (s == '5') C[5]++;
        else if (s == '6') { C[5]++; C[3]++; }
        else if (s == '7') C[7]++;
        else if (s == '8') { C[7]++; C[2] += 3; }
        else if (s == '9') { C[7]++; C[3] += 2; C[2]++; }
    }

    string A;
    for (int i = 7; i >= 2; --i) {
        for (int k = 0; k < C[i]; ++k) {
            A += char('0' + i);
        }
    }
    cout << A;
}
};
