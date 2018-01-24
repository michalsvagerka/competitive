#include "../l/lib.h"
// #include "../l/mod.h"

class access {
public:
    ui readIp(istream&cin) {
        ui a,b,c,d; char e;
        cin >> a >> e >> b >> e >> c >> e >> d;
        return a<<24 | b<<16 | c<<8 | d;
    }

    ui mask(ui bits) {
        return bits ? ~((1u<<(32-bits))-1) : 0;
    }

    map<puu, pair<ui,bool>> rules;

    void solve(istream& cin, ostream& cout) {
        ui N; cin >> N;
        for (ui i = 0; i < N; ++i) {
            string S,T; cin >> S >> T;
            ui ip = readIp(cin);
            ui bits = 32;
            if (cin.peek() == '/') {
                char e;
                cin >> e >> bits;
            }
            ip &= mask(bits);
            if (rules.find({ip,bits}) == rules.end()) {
                rules[{ip,bits}] = {i,S=="allow"};
            }
        }

        ui M; cin >> M;
        for (ui i = 0; i < M; ++i) {
            ui ip = readIp(cin);
            pair<ui,bool> R(N, true);
            for (ui b = 0; b <= 32; ++b) {
                auto it = rules.find({ip & mask(b), b});
                if (it != rules.end()) {
                    R = min(R, it->y);
                }
            }
            cout << "DA"[R.y];
        }
        cout << endl;
    }
};
