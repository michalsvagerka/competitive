#include "../l/lib.h"
#include "../l/random.h"

int balls, colors, signs, sizes, upper;


static constexpr int soup = -1;
static constexpr int mish = -2;

struct ball {
    int color; int sign; int size;
    bool operator==(const ball&o) const { return color  == o.color && sign == o.sign && size == o.size; }
    bool operator<(const ball&o) const { return (color * signs + sign) * sizes + size < (o.color * signs + o.sign) * sizes + o.size; }
};
struct potion {
    int color; int sign;

    bool operator==(const potion&o) const { return color  == o.color && sign == o.sign; }
    bool operator<(const potion&o) const { return (color * signs + sign) < (o.color * signs + o.sign); }
};


struct chemical : vector<ball> {
    chemical() : vector<ball>(balls) {}
    chemical inverse() const {
        chemical r = *this;
        for (ball&b:r) b.sign = signs - b.sign - 1;
        return r;
    }
};

ostream&operator<<(ostream&o, const potion&p) {
    if (p.color == soup) o << 'O';
    else o << "RGBYCM"[p.color] << "+-*/"[p.sign];
    return o;
}

ostream&operator<<(ostream&o, const ball&b) {
    if (b.size == 0) o << "RGBYCM"[b.color] << "+-*/"[b.sign];
    else o << "rgbycm"[b.color] << "+-*/"[b.sign];
    return o;
}

class alch {
public:
    vector<chemical> pieces;

    potion mix(const chemical& a, const chemical& b) {
        potion p{soup,-1};
        for (const ball &c: a) {
            for (const ball &d: b) {
                if (c.color == d.color && c.sign == d.sign && c.size != d.size) {
                    if (p.color == soup) {
                        p = {c.color, c.sign};
                    } else {
                        p.color = mish;
                    }
                }
            }
        }
        return p;
    }

    void generate(int ballId, int colorId, chemical &cur) {
        if (colorId == colors) {
            if (ballId == balls) {
                pieces.push_back(cur);
            }
            return;
        }

        generate(ballId, colorId+1, cur);
        for (int sign = 0; sign < signs; ++sign) {
            for (int size = 0; size < sizes; ++size) {
                cur[ballId] = {colorId, sign, size};
                generate(ballId+1, colorId+1, cur);
            }
        }
    }


    void solve(istream& cin, ostream& cout) {
        cin >> balls >> colors >> signs >> sizes >> upper;
        chemical ch;
        generate(0, 0, ch);
        cout << pieces.size() << endl;

        random_int rand(1,100);
        random_int chem(0,pieces.size()-1);
        set<chemical> solution;
        int bestSize = 0;
        int bestSoups = 0;
        for (int i = 0; i < 100000; ++i) {
            if (solution.size() < upper && (solution.empty() || rand(rng) < 90)) {
                chemical add = pieces[chem(rng)];
                bool ok = true;
                for (const chemical&ch: solution) {
                    if (ch == add || mix(ch, add).color == mish) {
                        ok = false;
                        break;
                    }
                }

                if (ok) {
                    solution.insert(add);
                    solution.insert(add.inverse());

                    map<potion,int> outcomes;
                    for (const chemical&ch1: solution) {
                        for (const chemical&ch2: solution) {
                            if (ch1!=ch2) {
                                outcomes[mix(ch1,ch2)]++;
                            }
                        }
                    }

                    if (solution.size() > bestSize || (solution.size() == bestSize && outcomes[{soup,-1}] < bestSoups)) {
                        bestSize = solution.size();
                        bestSoups = outcomes[{soup,-1}];
                        cout << "Found solution of size: " << solution.size() << ',' << outcomes[{soup,-1}]/2 << '\n';
                        for (const chemical &ch: solution) {
                            cout << ch;
                        }
                        cout << endl;


                        cout << "Outcomes\n";
                        for (auto&outcome: outcomes) {
                            cout << outcome.first << ' ' << outcome.second/2 << endl;
                        }
                        cout << endl;
                    }
                }
            } else {
                while (true) {
                    chemical ch = pieces[chem(rng)];
                    if (solution.erase(ch)) {
                        solution.erase(ch.inverse());
                        break;
                    }
                }
            }
        }
    }
};
