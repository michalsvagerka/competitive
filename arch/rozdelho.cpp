#include "../l/lib.h"
// #include "../l/mod.h"

#define Q(p,q,r)for(int i=0;i<b;++i){cout<<p;}cout<<q;for(int i=0;i<b;++i){cout<<r;}cout<<endl;

class rozdelho {
public:
    void solve(istream& cin, ostream& cout) {
		int A=$,B=$;
		if (B&1) {
			int b = (B-5)/2;
			Q('A',"AAAAA",'A')
			Q('B',"BBBCC",'C')
			Q('B',"EBCCD",'C')
			Q('E',"EBCDD",'D')
			Q('E',"EEEDD",'D')
		} else {
			int b = (B-6)/2;
			Q('A',"AAAAAA",'A')
			Q('B',"BBBBCC",'C')
			Q('B',"EBCCCD",'C')
			Q('E',"EBCDDD",'D')
			Q('E',"EEEEDD",'D')
		}
		for (int i = 5; i < A; ++i) {
			for (int j = 0; j < B; ++j) {
				cout << (char)('A'+i);
			}
			cout << endl;
		}

	}
};

/*

 AAAAA
 BBBCC
 EBCCD
 EBCDD
 EEEDD

 */


/*

 AAAAAA
 BBBBCC
 EBCCCD
 EBCDDD
 EEEEDD

 */