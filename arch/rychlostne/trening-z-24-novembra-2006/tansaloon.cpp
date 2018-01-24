#include "../l/lib.h"
// #include "../l/mod.h"

class tansaloon {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        while (N) {
            string S; cin >> S;
            vector<bool> in(26, false), out(26, false);
            int ans = 0;
            for (char s : S) {
                int i = s-'A';
                if (in[i]) {
                    in[i] = false;
                    ++N;
                } else if (out[i]) {
                    out[i] = false;
                } else if (N) {
                    in[i] = true;
                    --N;
                } else {
                    out[i] = true;
                    ans++;
                }
            }

            if (ans) {
                cout << ans << " customer(s) walked away.\n";
            } else {
                cout << "All customers tanned successfully.\n";
            }

            cin >> N;
        }
    }
};
