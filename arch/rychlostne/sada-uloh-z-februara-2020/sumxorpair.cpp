#include "../l/lib.h"
#include "../l/mod.h"
#include "../l/random.h"

class sumxorpair {
public:
    map<vector<int>, pair<int, FieldMod>> C;

    pair<int, FieldMod> solve(vector<int> A, int b) {
        auto it = C.find(A);
        if (it != C.end()) return it->y;

        if (b == -1) {
            FieldMod ways = 1;
            for (int i = 3; i < A.size(); i += 2) {
                ways *= i;
            }
            return {0, ways};
        }
        vector<int> LO, HI;
        for (int a: A) if (a < (1<<b)) LO.push_back(a); else HI.push_back(a^1<<b);
        if (LO.size() > HI.size()) swap(LO, HI);
        pair<int, FieldMod> ans{100000, 0};
        if (LO.size() % 2 == 1) {
            for (int i = 0; i < LO.size(); ++i) {
                HI.push_back(LO[i]);
                swap(LO[i], LO.back());
                LO.pop_back();
                auto x = solve(LO, b-1);
                auto y = solve(HI, b-1);
                if (x.x + y.x == ans.x) {
                    ans.y += x.y * y.y;
                } else if (x.x + y.x < ans.x) {
                    ans = {x.x+y.x, x.y*y.y};
                }
                LO.push_back(HI.back());
                swap(LO[i], LO.back());
                HI.pop_back();
            }
            ans.x += 1<<b;
        } else {
            auto x = solve(LO, b-1);
            auto y = solve(HI, b-1);
            ans = {x.x+y.x, x.y*y.y};
        }
        return C[A] = ans;
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        cout << solve(A, 9) << '\n';
    }
};
