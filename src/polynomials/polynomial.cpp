#include <ecnt/polynomials/polynomial.hpp>
#include <stdexcept>
#include <ecnt/polynomials/algorithms.hpp>

namespace ecnt {
    template<typename F>
    Polynomial<F>::Polynomial(size_t n) : coefficients(n + 1, F{0}) {
    };

    template<typename F>
    Polynomial<F>::Polynomial(std::vector<F> coef) : coefficients(std::move(coef)) {
        if (coefficients.empty()) coefficients.push_back(F{0});
    }

    template<typename F>
    Polynomial<F>::Polynomial(F c) : coefficients{c} {
    }

    template<typename F>
    F Polynomial<F>::evaluate(F x) const {
        F res{F{0}};

        for (size_t i = degree() + 1; i-- > 0;)
            res = res * x + (*this)[i];

        return res;
    }

    template<typename F>
    size_t Polynomial<F>::degree() const {
        size_t n{coefficients.size() - 1};
        while (n > 0 && coefficients[n] == F{0}) n--;
        return n;
    }

    template<typename F>
    bool Polynomial<F>::operator==(const Polynomial &rhs) const {
        size_t pn{degree()}, qn{rhs.degree()};
        if (pn != qn) return false;
        for (size_t i{0}; i <= qn; i++) {
            if ((*this)[i] != rhs[i]) return false;
        }
        return true;
    }

    template<typename F>
    Polynomial<F> Polynomial<F>::operator+(const Polynomial &rhs) const {
        auto pn{degree()}, qn{rhs.degree()};
        size_t rn{max(qn, pn)};
        Polynomial<F> R(rn);
        for (size_t i{0}; i <= rn; i++) {
            R[i] = (i <= pn ? (*this)[i] : F{0}) + (i <= qn ? rhs[i] : F{0});
        }
        return R;
    }

    template<typename F>
    Polynomial<F> Polynomial<F>::operator-(const Polynomial &rhs) const {
        auto pn{degree()}, qn{rhs.degree()};
        size_t rn{max(pn, qn)};
        Polynomial<F> R(rn);
        for (size_t i{0}; i <= rn; i++) {
            R[i] = (i <= pn ? (*this)[i] : F{0}) - (i <= qn ? rhs[i] : F{0});
        }
        return R;
    }

    template<typename F>
    Polynomial<F> Polynomial<F>::operator*(const Polynomial &rhs) const {
        auto pn{degree()}, qn{rhs.degree()};
        size_t rn{qn + pn};
        Polynomial<F> R(rn);
        for (size_t i{0}; i <= pn; i++) {
            for (size_t j{0}; j <= qn; j++) R[i + j] = R[i + j] + (*this)[i] * rhs[j];
        }
        return R;
    }

    template<typename F>
    Polynomial<F> Polynomial<F>::operator*(F s) const {
        size_t pn{degree()};

        Polynomial<F> R(*this);

        for (size_t i{0}; i <= pn; i++) R[i] = (*this)[i] * s;

        return R;
    }

    template<typename F>
    Polynomial<F> Polynomial<F>::operator/(const Polynomial &rhs) const {
        size_t pn{degree()}, dn{rhs.degree()};
        if (rhs == Polynomial(dn)) throw std::domain_error("Polynomial division by zero");
        size_t qn{pn >= dn ? pn - dn : 0};
        Polynomial R(*this), Q(qn);
        F inv_lead_d(F{1} / rhs[dn]);
        for (size_t i{pn}; i >= dn; --i) {
            if (R[i] == F{0}) continue;
            Q[i - dn] = R[i] * inv_lead_d;
            F mul{-Q[i - dn]};
            for (size_t j{0}; j <= dn; j++) R[j + i - dn] = R[j + i - dn] + mul * rhs[j];
        }
        return Q;
    }

    template<typename F>
    Polynomial<F> Polynomial<F>::operator%(const Polynomial &rhs) const {
        size_t pn{degree()}, dn{rhs.degree()};
        if (rhs == Polynomial(dn)) throw std::domain_error("Polynomial division by zero polynomial");
        Polynomial R(*this);
        F inv_lead_d(F{1} / rhs[dn]);
        for (size_t i{pn}; i >= dn; --i) {
            if (R[i] == F{0}) continue;
            F mul{-(R[i] * inv_lead_d)};
            for (size_t j{0}; j <= dn; j++) R[j + i - dn] = R[j + i - dn] + mul * rhs[j];
        }
        return R;
    }

    template<typename F>
    Polynomial<F> Polynomial<F>::operator^(long long e) const {
        if (e < 0) throw std::domain_error("Negative Exponent Not Allowed")
        return algorithms::power(*this, e);
    }

    template<typename F>
    F Polynomial<F>::operator[](size_t i) const {
        size_t n{degree()};
        return i <= n ? coefficients[i] : F{0};
    }

    template<typename F>
    F &Polynomial<F>::operator[](size_t i) {
        return coefficients[i];
    }
}
