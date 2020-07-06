#include "../l/lib.h"

class EIncreasingNumbers {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        S = '0' + S;
        int N = S.size();
        int carry = 0;
        for (int i = N-1; i >= 0; --i) {
            int dig = S[i] - '0';
            dig *= 9;
            dig += carry;
            carry = dig / 10;
            S[i] = char('0' + dig%10);
        }
        int digSum = 0;
        for (int i = 0; i < N; ++i) digSum += (S[i] - '0');
        int k = 0;
        while (digSum > 9*k) {
            k++;
            int carry = 9;
            for (int i = N-1; carry; --i) {
                int dig = S[i] - '0';
                digSum -= dig;
                dig += carry;
                carry = dig / 10;
                dig = dig % 10;
                digSum += dig;
                S[i] = char('0' + dig);
            }
        }

        cout << k << endl;
        return;
    }
};
