#include "../l/lib.h"
// #include "../l/mod.h"

class SixteenQueens {
public:
    vector <int> addQueens(vector <int> row, vector <int> col, int add) {
        vector<int> R(50, false), C(50, false), AD(100, false), DD(100, false);
        for (int i = 0; i < row.size(); ++i) {
            R[row[i]] = C[col[i]] = AD[row[i] + col[i]] = DD[row[i] + 49 - col[i]] = true;
        }

        vector<int> Ans;
        for (int r = 0; r < 50; ++r) {
            for (int c = 0; c < 50; ++c) {
                if (add && !R[r] && !C[c] && !AD[r+c] && !DD[r+49-c]) {
                    AD[r+c] = DD[r+49-c] = C[c] = R[r] = true;
                    Ans.push_back(r);
                    Ans.push_back(c);
                    --add;
                }
            }
        }
        return Ans;
    }

    void solve(istream& cin, ostream& cout) {
        cout << addQueens({3}, {5}, 1) << endl;
        cout << addQueens({0}, {1}, 1) << endl;
        cout << addQueens({0}, {1}, 3) << endl;
        cout << addQueens({14, 19}, {3, 47}, 0) << endl;
        cout << addQueens({}, {}, 2) << endl;
        cout << addQueens({1,2,3}, {7,2,19}, 1) << endl;
    }
};
