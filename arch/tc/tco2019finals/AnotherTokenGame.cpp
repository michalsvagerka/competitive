#include "../l/lib.h"
#include <regex>

class AnotherTokenGame {
public:
    int getSmallest(string s) {
        int N = s.size();
        if (count(s.begin(),s.end(),'L') == 0) {
            return 0;
        }

        s = "." + s + ".";

        regex reg("LL+");
        sregex_token_iterator iter(s.begin(),s.end(),reg,-1);
        sregex_token_iterator end;
        int ans = -2;
        for (; iter != end; ++iter) {
            ans += 2;

            string t = *iter;
            int c = count(t.begin(),t.end(),'L');
            int d = t.size();
            ans += c;
            ans -= 2*c+1 == d;
        }



//        bool isTwo = false;
//        string T = ".";
//        vector<string> SS;
//        for (int i = 0; i < N; ++i) {
//            if (s[i] == 'L') {
//                if (i != 0 && s[i-1] == 'L') {
//                    isTwo = true;
//                } else if (i == N-1) {
//                    T += 'L';
//                }
//            } else {
//                if (i != 0 && s[i-1] == 'L') {
//                    if (isTwo) {
//                        isTwo = false;
//                        SS.push_back(T);
//                        T = ".";
//                    } else {
//                        T += "L.";
//                    }
//                } else {
//                    T += '.';
//                }
//            }
//        }
//
//        if (isTwo) {
//            SS.push_back(T);
//            T = "";
//        }
//        SS.push_back(T + ".");
//        int cnt = 2*(SS.size()-1);
//        for (int i = 0; i < SS.size(); ++i) {
//            int c = count(SS[i].begin(),SS[i].end(),'L');
//            int d = SS[i].size();
//            cnt += c;
//            cnt -= 2*c+1 == d;
//        }

        return min((int)count(s.begin(),s.end(),'.'),ans);
    }

    void solve(istream& cin, ostream& cout) {
        cout << getSmallest(".....") << endl;
        cout << getSmallest("..L.....") << endl;
        cout << getSmallest("LL....L..L.") << endl;
        cout << getSmallest(".L.L.") << endl;
        cout << getSmallest(".L.LL.") << endl;
        cout << getSmallest("L.L") << endl;
        cout << getSmallest("L.L..LL.........") << endl;
        cout << getSmallest("....L....L...") << endl;
        cout << getSmallest(".L.L.L........L...LL....LLL.......L......L..L.L.....LL............LL..L.L..LL.LL") << endl;
        cout << getSmallest("L.L...LL.") << endl;
        cout << getSmallest("L.") << endl;
        cout << getSmallest("L.L.LL........") << endl;
    }
};
