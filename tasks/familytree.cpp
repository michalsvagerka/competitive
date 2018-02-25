#include "../l/lib.h"
// #include "../l/mod.h"

class familytree {
public:
    struct Person {
        bool hasGender;
        bool gender;
        set<Person*> kids;
        set<Person*> parents;
        Person() : hasGender{false}, gender{false} {};
    };

    map<string, Person*> T;
    set<Person*> V;

    bool checkPath(Person* P) {
        if (V.count(P)) return false;
        V.insert(P);

        for (auto p: P->parents) {
            if (!checkPath(p)) return false;
        }

        V.erase(P);
        return true;
    }


    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        for (int i = 0; i < N; ++i) {
            string A, B; cin >> A >> B;
            auto it = T.find(A);
            Person *P1 = it != T.end() ? it->y : T[A] = new Person;
            if (B == "f") {
                if (P1->hasGender && P1->gender) {
                    cout << i << endl;
                    return;
                }
                P1->hasGender = true;
                P1->gender = false;
            } else if (B == "m") {
                if (P1->hasGender && !P1->gender) {
                    cout << i << endl;
                    return;
                }
                P1->hasGender = true;
                P1->gender = true;
            } else {
                it = T.find(B);
                Person *P2 = it != T.end() ? it->y : T[B] = new Person;
                P1->parents.insert(P2);
                P2->kids.insert(P1);
                if (P1 == P2 || P1->parents.size() > 2) {
                    cout << i << endl;
                    return;
                }
            }

            bool genderChanged;
            do {
                genderChanged = false;
                for (auto p : T) {
                    auto P = p.y;
                    if (P->parents.size() == 2) {
                        auto P1 = *P->parents.begin();
                        auto P2 = *next(P->parents.begin());
                        if (P1->hasGender && P2->hasGender && P1->gender == P2->gender) {
                            cout << i << endl;
                            return;
                        } else if (P1->hasGender && !P2->hasGender) {
                            P2->hasGender = true;
                            P2->gender = !P1->gender;
                            genderChanged = true;
                        } else if (P2->hasGender && !P1->hasGender) {
                            P1->hasGender = true;
                            P1->gender = !P2->gender;
                            genderChanged = true;
                        }
                    }
                }
            } while (genderChanged);

            for (auto p : T) {
                if (!checkPath(p.y)) {
                    cout << i << endl;
                    return;
                }
            }


        }

        cout << "-1\n";
    }
};
