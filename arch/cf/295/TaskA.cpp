#include "../../../l/lib.h"
 #include "../../../l/mod.h"

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    string S; cin >> S;
    map<char,int> C;
    for (char s:S) {
        C[s]++;
    }

    int hi = 0;
    for (auto c:C) hi = max(hi, c.y);

    int cnt = 0;
    for (auto c:C) cnt += c.y == hi;

    cout << FieldMod{cnt}.pow(N) << '\n';
}
};
