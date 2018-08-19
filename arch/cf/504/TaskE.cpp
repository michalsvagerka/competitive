#include "../l/lib.h"
// #include "../l/mod.h"

class TaskE {
public:



void solve(istream& cin, ostream& cout) {
    int N; cin >> N;

    auto query = [&](int a, int b, int c, int d) {
        cout << "? " << a << ' ' << b << ' ' << c << ' ' << d << endl;
        string s; cin >> s;
        if (s == "BAD") {
            exit(0);
        } else {
            return s == "YES";
        }
    };

    int r = 1, c = 1;
    vector<char> Begin, End;
    for (int i = 0; i < N-1; ++i) {
        if (r != N && query(r+1, c, N, N)) {
            Begin.push_back('D');
            r++;
        } else {
            Begin.push_back('R');
            c++;
        }
    }

    r = N, c = N;
    for (int i = 0; i < N-1; ++i) {
        if (c != 1 && query(1, 1, r, c-1)) {
            End.push_back('R');
            c--;
        } else {
            End.push_back('D');
            r--;
        }
    }

    reverse(End.begin(),End.end());
    cout << "! ";
    for (int i = 0; i < N-1; ++i) cout << Begin[i];
    for (int i = 0; i < N-1; ++i) cout << End[i];
    cout << endl;





}
};
