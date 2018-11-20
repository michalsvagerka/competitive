#include "../l/lib.h"
 #include "../l/mod.h"

class CityLights {
public:
    struct Calc {

        int W, S;
        vector<pii> A, B;
        FieldMod ans;
        map<int, vector<int>> Win;
        vector<int> Coords;
        vector<int> LoSt;
        map<pair<pii,pii>, bool> Obst;
        
        void calc() {
            for (int i = 0; i < W; ++i) {
                Win[A[i].x].push_back(A[i].y);
            }

            for (auto&w:Win) {
                sort(w.y.begin(),w.y.end());
                Coords.push_back(w.x);
            }

            LoSt.assign(Coords.size()+1, 2e9);
            for (pii s:B) {
                if (s.x <= Coords[0]) LoSt[0] = min(LoSt[0], s.y);
                if (s.x >= Coords.back()) LoSt[Coords.size()] = min(LoSt[Coords.size()], s.y);
                for (int i = 0; i < Coords.size()-1; ++i) {
                    if (s.x >= Coords[i] && s.x <= Coords[i+1]) LoSt[i+1] = min(LoSt[i+1], s.y);
                }
            }
            
            for (pii w:A) {
                for (pii x:A) {
                    bool obst = false;
                    for (pii s:B) {
                        if ((s.x >= min(w.x, x.x) && s.x <= max(w.x, x.x)
                        && s.y >= min(w.y, x.y) && s.y <= max(w.y, x.y))) obst = true;
                    }
                    Obst[{w,x}] = obst;
                }
            }
            

//            cerr << Coords << LoSt;

            ans = 0;
            for (int i = 0; i < Coords.size(); ++i) {
                for (int j = i; j < Coords.size(); ++j) {
                    int l = Coords[i], r = Coords[j];
                    int lX = i==0?-1:Coords[i-1];
                    int rX = j==Coords.size()-1?1e9+2:Coords[j+1];

                    int lo = 2e9;
                    for (int k = i+1; k <= j; ++k) lo = min(lo, LoSt[k]);

                    vector<pii> Below;
                    int belowL = 0, belowR = 0;
                    for (int k = i; k <= j; ++k) {
                        for (int w:Win[Coords[k]]) {
                            if (w < lo) {
                                Below.push_back({w, k});
                                if (k == i) belowL++;
                                if (k == j) belowR++;
                            }
                        }
                    }

                    sort(Below.begin(),Below.end());
                    reverse(Below.begin(),Below.end());
                    int below = Below.size();
                    int other = W - below;
                    for (int k = 0; k < Below.size(); ++k) {

                        if (belowL == 0 || belowR == 0)  break;
                        
                        FieldMod l, r, a;
                        if (i == j) {
                            l = 1;
                            r = 1;
                            a = FieldMod{2}.pow(below - 1);
                        } else if (Below[k].y == i) {
                            l = 1;
                            r = FieldMod{2}.pow(belowR) - 1;
                            a = FieldMod{2}.pow(below - belowR - 1);
                        } else if (Below[k].y == j) {
                            l = FieldMod{2}.pow(belowL) - 1;
                            r = 1;
                            a = FieldMod{2}.pow(below - belowL - 1);
                        } else {
                            l = FieldMod{2}.pow(belowL) - 1;
                            r = FieldMod{2}.pow(belowR) - 1;
                            a = FieldMod{2}.pow(below - belowL - belowR - 1);
                        }

                        int off = 0;

                        int z = i;
                        while (z > 0 && LoSt[z] > Below[k].x) {
                            --z;

                            for (int c: Win[Coords[z]]) {
                                bool obst = false;
                                for (int l = k; l < Below.size(); ++l) {
                                    obst |= Obst[{{Coords[Below[l].y], Below[l].x},{Coords[z],c}}];
                                }
                                if (!obst) off++;
                            }
                        }


                        int y = j+1;
                        while (y < Coords.size() && LoSt[y] > Below[k].x) {
                            for (int c: Win[Coords[y]]) {

                                bool obst = false;
                                for (int l = k; l < Below.size(); ++l) {
                                    obst |= Obst[{{Coords[Below[l].y], Below[l].x},{Coords[y],c}}];
                                }
                                if (!obst) off++;
                            }
                            ++y;
                        }

                        cerr << i << ' ' << j << ' ' << Below[k] << ' ' << belowL << ' ' << belowR << ' ' << other << ' ' << off << ' ' << l * r * a * FieldMod{2}.pow(other - off) << endl;
                        ans += l * r * a * FieldMod{2}.pow(other - off);


                        if (Below[k].y == i) --belowL;
                        if (Below[k].y == j) --belowR;

                        --below;
                    }
                }
            }
        }



        void read(istream& cin) {
            cin >> W >> S;
            A.resize(W);
            B.resize(S);
            cin >> A >> B;
        }

        void write(ostream &cout) {
            cout << ans << '\n';
        }
    };


    void solve(istream& cin, ostream& cout) {
        ui T; cin >> T;
        for (int t = 1; t <= T; ++t) {
            Calc c;
            c.read(cin);
            if (t == 4) c.calc();
            cout << "Case #" << t << ": ";
            c.write(cout);
        }
    }

};
