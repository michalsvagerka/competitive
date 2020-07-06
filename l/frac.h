
class Fraction {
    friend ostream& operator<<(ostream& os, const Fraction& f);
public:
    Fraction(ll u = 0, ll v = 1) : u(u), v(v) { norm(); }
    bool operator==(const Fraction & o) const { return u == o.u && v == o.v; }
    bool operator!=(const Fraction & o) const { return u != o.u || v != o.v; }
    bool operator<(const Fraction &o) const { return u*o.v < o.u*v; }
    bool operator<=(const Fraction &o) const { return u*o.v <= o.u*v; }
    bool operator>(const Fraction &o) const { return u*o.v > o.u*v; }
    bool operator>=(const Fraction &o) const { return u*o.v >= o.u*v; }
    Fraction operator-(const Fraction& o) { return Fraction(-u, v); }
    Fraction& operator+=(const Fraction& o) { u = u * o.v + v * o.u; v *= o.v; return norm(); }
    Fraction& operator-=(const Fraction& o) { u = u * o.v - v * o.u; v *= o.v; return norm(); }
    Fraction& operator/=(const Fraction& o) { u = u * o.v; v = o.u * v; return norm(); }
    Fraction& operator*=(const Fraction& o) { u *= o.u; v *= o.v; return norm(); }
    Fraction operator+(const Fraction& o) const { Fraction f(*this); return f += o; }
    Fraction operator-(const Fraction& o) const { Fraction f(*this); return f -= o; }
    Fraction operator*(const Fraction& o) const { Fraction f(*this); return f *= o; }
    Fraction operator/(const Fraction& o) const { Fraction f(*this); return f /= o; }

    Fraction& norm() {
        ll g = gcd(abs(u),abs(v));
        u /= g;
        v /= g;
        if (v < 0) {
            u = -u;
            v = -v;
        }
        if (v == 0 && u < 0) {
            u = -u;
        }
        return *this;
    }

    ll u,v;
};


ostream& operator<<(ostream& os, const Fraction& f) {
    os << f.u << '/' << f.v;
    return os;
}