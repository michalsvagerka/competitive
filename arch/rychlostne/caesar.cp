#include "../l/lib.h"
#include "../l/mod.h"
#include "../l/geo.h"
char C[26];

class ceasar {
public:
    void solve(istream& cin, ostream& cout) {
        Point<ll> a{10, 10};
        Point<ll> b{20, 20};
        Segment<ll> s{a,b};
        Line<ll> l{a,b};
        cout << a.squaredDistance(b) << endl;
        cout << s.squaredLength() << endl;
        for (auto p: vector<pair<ll,ll>>{{15,15},{10,20},{10,0},{20,30}}) {
            cout << l.project(p) << ' ' << l.distance(p) << ' ' << s.distance(p) << endl;
        }
        vector<Segment<ll>> ss{s, Segment<ll>{{0,0},{15,15}}, Segment<ll>{{16,16},{30,30}}, Segment<ll>{{10,0},{0,10}}};
        for (int i = 0; i < ss.size(); ++i) {
            for (int j = 0; j < ss.size(); ++j) {
                cout << ss[i].intersect(ss[j]) << ' ';
            }
            cout << endl;
        }

        Line<ll> l2{{12,0},{12,20}};
        cout << l.intersection(l2) << endl;
        cout << Line<ll>{{0,  0}, {30, 40}}.intersection({{9,  17}, {15, 30}}) << endl;

        Polygon<ll> poly{{0,0},{3,0},{3,4}};
        cout << poly.doubleSignedArea() << endl;
    }
};
