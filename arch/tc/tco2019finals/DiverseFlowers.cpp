#include "../l/lib.h"

class DiverseFlowers {
public:
    vector <string> solve(string S, int K) {
        int b = 0, g = 0, r = 0, R = 0, G = 0, B = 0;
        int N = S.size();
        for (char s : S) {
            switch (s) {
                case 'b': b++; break;
                case 'B': B++; break;
                case 'r': r++; break;
                case 'R': R++; break;
                case 'g': g++; break;
                case 'G': G++; break;
            }
        }

        vector<string> Pairs, Triples;
        int rG = min(r, G); r -= rG; G -= rG;
        int Rg = min(R, g); R -= Rg; g -= Rg;
        for (int i = 0; i < rG; ++i) Pairs.push_back("rG");
        for (int i = 0; i < Rg; ++i) Pairs.push_back("Rg");
        int RGb = min(R, min(G, b)), rgB = min(r, min(g, B));
        R -= RGb; G -= RGb; b -= RGb; g -= rgB; r -= rgB; B -= rgB;
        for (int i = 0; i < rgB; ++i) Triples.push_back("rgB");
        for (int i = 0; i < RGb; ++i) Triples.push_back("RGb");
        
        while (!Pairs.empty() && b+B != 0) {
            string P = Pairs.back();
            Pairs.pop_back();
            if (b != 0) {
                P += 'b';
                --b;
            } else {
                P += 'B';
                --B;
            }
            Triples.push_back(P);
        }
        

        string Rest;
        for (int i = 0; i < b; ++i) Rest += 'b';
        for (int i = 0; i < B; ++i) Rest += 'B';
        for (int i = 0; i < g; ++i) Rest += 'g';
        for (int i = 0; i < G; ++i) Rest += 'G';
        for (int i = 0; i < r; ++i) Rest += 'r';
        for (int i = 0; i < R; ++i) Rest += 'R';
        for (string p: Pairs) Rest += p;
        
        vector<string> Ans;
        while (!Triples.empty()) {
            string X = Triples.back();
            Triples.pop_back();
            while (X.size() < K && (!Rest.empty() || !Triples.empty())) {
                if (!Rest.empty()) {
                    X += Rest.back(); Rest.pop_back(); 
                } else {
                    Rest += Triples.back();
                    Triples.pop_back();
                }
            }
            if (X.size() == K) {
                Ans.push_back(X);
            }
        }
        
        return Ans;
    }

    void solve(istream& cin, ostream& cout) {
        cout << solve("BBgbr", 3) << endl;
        cout << solve("BBgbrGBBB", 3) << endl;
        cout << solve("RGBrgb", 4) << endl;
        cout << solve("RGBrgbRGBrgbRGBrgbRG", 5) << endl;
        cout << solve("rrrrrbbbbbbgR", 4) << endl;
        cout << solve("gbgBgBgBbGGGBGGgbGBbGgGBBBBGGBGBbgBGBbbgGBBG", 3) << endl;
        cout << solve("RRgBrRRrgBRRBRgRRGBrRRgbRRRgBR", 5) << endl;
        cout << solve("RRgBrRRrgBRRBRgRRGBrRRgbRRRgBR", 30) << endl;
    }
};
