#include "../l/lib.h"
 #include "../l/mod.h"

class TaskD {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    FieldMod ans = 1;
    set<int> buy, sell, unknown;
    for (int i = 0; i < N; ++i) {
        string s; int p;
        cin >> s >> p;
        if (s == "ADD") {
            if (!buy.empty() && p < *buy.rbegin()) buy.insert(p);
            else if (!sell.empty() && p > *sell.begin()) sell.insert(p);
            else unknown.insert(p);
        } else {
            if (!buy.empty() && p == *buy.rbegin()) {
                buy.erase(p);
                for (int u:unknown) {
                    sell.insert(u);
                }
                unknown.clear();
            }
            else if (!buy.empty() && p < *buy.rbegin()) { cout << "0\n"; return; }
            else if (!sell.empty() && p == *sell.begin()) {
                sell.erase(p);
                for (int u:unknown) {
                    buy.insert(u);
                }
                unknown.clear();
            }
            else if (!sell.empty() && p > *sell.begin()) { cout << "0\n"; return; }
            else {
                for (int u:unknown) {
                    if (u < p) buy.insert(u);
                    else if (u > p) sell.insert(u);
                }
                unknown.clear();
                ans *= 2;
            }
        }
    }
    cout << ans * (unknown.size() + 1) << endl;
}
};
