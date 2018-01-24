#include "../l/lib.h"
#include "../l/primes.h"
#include "../l/random.h"

int M;
vector<int> V(26);

struct Term { virtual int eval() = 0; virtual void write(ostream&os) = 0; };
struct Val : public Term { Val(int v) : x(v){}; int x; int eval() {return x%M;} void write(ostream&os) { os << x; } };
struct Var : public Term { Var(char c) : i(c-'a'){}; int i; int eval() {return V[i];} void write(ostream&os) { os << char('a'+i); }};
struct Sub : public Term { Sub(Term*a,Term*b) : a(a),b(b){}; Term*a,*b; int eval() {return (M+a->eval()-b->eval())%M;}
    void write(ostream&os) { os << '('; a->write(os); os << '-'; b->write(os); os << ')'; } };
struct Add : public Term { Add(Term*a,Term*b) : a(a),b(b){}; Term*a,*b; int eval() {return (a->eval()+b->eval())%M;}
    void write(ostream&os) { os << '('; a->write(os); os << '+'; b->write(os); os << ')'; }};
struct Mul : public Term { Mul(Term*a,Term*b) : a(a),b(b){}; Term*a,*b; int eval() {return ((ll)a->eval()*b->eval())%M;}
    void write(ostream&os) { a->write(os); os << '*'; b->write(os); }};
struct Exp : public Term { Exp(Term*a,int b) : a(a),b(b){}; Term*a;int b; int eval() {
        int c=a->eval(),r=1;
        for (int i = 0; i < b; ++i) r=((ll)r*c)%M;
        return r;
    }
    void write(ostream&os) { a->write(os); os << '^' << b; }
};

class mikrovnost {
public:
    int readNum(const string &s, int &i) {
        while (s[i] == ' ') ++i;
        int n = 0;
        while (i<s.size() && s[i] >= '0' && s[i] <= '9') {
            n = 10*n + s[i++] - '0';
        }
        return n;
    }


    Term *readPoly(const string &s, int &i) {
        //cerr << "readPoly " << i << endl;
        Term *t = readTerm(s,i);
        while (i<s.size()) {
            switch (s[i++]) {
                case ' ': break;
                case '-':
                    t = new Sub(t, readTerm(s,i));
                    break;
                case '+':
                    t = new Add(t, readTerm(s,i));
                    break;
                case ')':
                    return t;
            }
        }
        return t;
    }

    Term *readTerm(const string &s, int &i) {
        //cerr << "readTerm " << i << endl;
        stack<Term*> T;
        Term *cur; int n;
        bool done = false;
        while (i<s.size()&&!done) {
            switch (s[i++]) {
                case ' ':
                    break;
                case '-':
                case '+':
                case ')':
                    --i;
                    done = true;
                    break;
                case '(':
                    T.push(readPoly(s, i));
                    break;
                case '^':
                    cur = T.top(); T.pop();
                    T.push(new Exp(cur,readNum(s,i)));
                    break;
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    n = readNum(s,--i);
                    T.push(new Val(n));
                    break;
                default:
                    T.push(new Var(s[i-1]));
                    break;
            }
        }

        while(T.size() > 1) {
            Term*a=T.top();T.pop();
            Term*b=T.top();T.pop();
            T.push(new Mul(b,a));
        }
        return T.top();
    }

    void solve(istream& cin, ostream& cout) {
        LargePrimes LP;
        random_int RI(0,LP.size()-1), RV(0,1000);
        while (true) {
            string K; getline(cin, K);
            if (K == ".") return;
            int z=0;
            Term *k = readPoly(K,z);

            while (true) {
                string B; getline(cin, B);
                if (B == ".") break;
                z = 0;
                Term *b = readPoly(B,z);

                bool ok = true;
                for (int i = 0; ok && i < 200; ++i) {
                    M = LP[RI(rng)];
                    for (int v = 0; v < 26; ++v) V[v] = RV(rng);
                    int ke=k->eval();
                    int be= b->eval();
                    //if(ke!=be) cout << ke << ' ' << be << ' ' << M << ' ' << V;
                    ok &= ke==be;
                }
                cout << (ok?"yes":"no") << '\n';
            }

            cout << ".\n";
        }
    }
};
