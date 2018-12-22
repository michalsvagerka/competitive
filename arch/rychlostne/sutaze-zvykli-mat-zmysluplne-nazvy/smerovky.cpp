#include "../l/lib.h"
// #include "../l/mod.h"

class smerovky {
public:
void solve(istream& cin, ostream& cout) {
    int T; cin >> T;
    for (int i = 0; i < T; ++i) {
        ll PA, TB, PB; cin >> PA >> TB >> PB;

        ll t=0,nt=1,s=1,ns=0,r=PA,nr=PB;
        while(nr!=0){ ll q=r/nr;t-=q*nt;r-=q*nr;s-=q*ns;swap(t,nt);swap(r,nr);swap(s,ns); }
        if (TB%r != 0) {
            cout << "-1\n";
        } else {
            cout << (((-s*TB/r)%PB+PB)%PB)*PA << '\n';
        }
    }
}
};
