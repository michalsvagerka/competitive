#include "../l/lib.h"
// #include "../l/mod.h"

class pawukon {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N; --N;
        vector<vector<string>> S{
                {},
                {"Luang"},
                {"Menga", "Pepet"},
                {"Pasah", "Beteng", "Kajeng"},
                {"Sri", "Laba", "Jaya", "Menala"},
                {"Paing", "Pon", "Wage", "Keliwon", "Umanis"},
                {"Tungleh", "Aryang", "Urukung", "Paniron", "Was", "Maulu"},
                {"Redite", "Soma", "Anggara", "Buda", "Wraspati", "Sukra", "Saniscara"},
                {"Sri", "Indra", "Guru", "Yama", "Ludra", "Brahma", "Kala", "Uma"},
                {"Dangu", "Jangur", "Gigis", "Nohan", "Ogan", "Erangan", "Urungan", "Tulus", "Dadi"},
                {"Sri", "Pati", "Raja", "Manuh", "Duka", "Manusa", "Raksasa", "Suka", "Dewa", "Pandita"}
        };

        vector<vector<int>> Urip{
            {5, 2, 8, 6, 4, 7, 10, 3, 9, 1},
            {5, 4, 3, 7, 8, 6, 9},
            {9, 7, 4, 8, 5}
        };

        vector<string> Ans(11);
        Ans[3] = S[3][N%3];
        Ans[5] = S[5][N%5];
        Ans[6] = S[6][N%6];
        Ans[7] = S[7][N%7];
        Ans[4] = S[4][(N-(N>=71)-(N>=72))%4];
        Ans[8] = S[8][(N-(N>=71)-(N>=72))%8];
        Ans[9] = S[9][(N-(N>=1)-(N>=2)-(N>=3))%9];

        int urip = Urip[1][N%7] + Urip[2][N%5] + 1;
        if (urip > 10) urip -= 10;
        for (int i = 0; i < 10; ++i) {
                if (Urip[0][i] == urip) Ans[10] = S[10][i];
        }

        if (urip%2==0) {
                Ans[2] = S[2][1];
                Ans[1] = S[1][0];
        } else {
                Ans[2] = S[2][0];
        }

        for (int i = 1; i <= 10; ++i) {
                cout << Ans[i] << "-\n"[i==10];
        }


    }
};
