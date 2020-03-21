#include "../l/lib.h"

class RaceCondition {
public:
    string minimize(vector <int> gates) {
        int N = gates.size();
        if (count(gates.begin(),gates.end(),0) == N) {
            return "";
        } else {
            for (int i = 0; i < N; ++i) {
                if (gates[i] == 1) {
                    string S; 
                    S += char('a' + i);
                    for (int j = 0; j < N; ++j) {
                        if (i != j) {
                            for (int k = 0; k < gates[j]; ++k) {
                                S += char('a' + j);
                                S += char('A' + j);
                            }
                        }
                    }
                    S += char('A' + i);
                    return S;
                }
            }
            
            int lo = 0;
            while (gates[lo] == 0) lo++;
            int hi = N-1;
            while (gates[hi] == 0) hi--;

            string S;
            if (lo == hi) {
                for (int j = 0; j < gates[lo]; ++j) {
                    S += char('a' + lo);
                    S += char('A' + lo);
                }
                return S;
            }
            
            S += char('a' + lo);
            for (int i = 0; i < N; ++i) {
                if (i != lo) {
                    for (int j = 0; j < gates[i] - (i==hi); ++j) {
                        S += char('a' + i);
                        S += char('A' + i);
                    }
                }
            }
            S += char('A' + lo);
            S += char('a' + hi);
            for (int j = 0; j < gates[lo]-1; ++j) {
                S += char('a' + lo);
                S += char('A' + lo);
            }
            S += char('A' + hi);
            return S;
        }
    }

    void solve(istream& cin, ostream& cout) {
        cout << minimize({7}) << endl;
        cout << minimize({1,1,1,0,1}) << endl;
        cout << minimize({2,2,2}) << endl;
        cout << minimize({3,0,1}) << endl;
    }
};
