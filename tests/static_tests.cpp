#include "src/bindings.h"

namespace {

    // negate
    static_assert(logical::negate(false));
    static_assert(!logical::negate(true));

    // eq
    static_assert(logical::eq(true, true));
    static_assert(!logical::eq(true, false));
    static_assert(logical::eq(9, 9));
    static_assert(!logical::eq(9, 10));

    // neq
    static_assert(!logical::neq(true, true));
    static_assert(logical::neq(true, false));
    static_assert(!logical::neq(9, 9));
    static_assert(logical::neq(9, 10));

    // conjunction
    static_assert(logical::conjunction(true, true));
    static_assert(!logical::conjunction(true, false));
    static_assert(!logical::conjunction(false, true));
    static_assert(!logical::conjunction(false, false));

    // disjunction
    static_assert(logical::disjunction(true, true));
    static_assert(logical::disjunction(true, false));
    static_assert(logical::disjunction(false, true));
    static_assert(!logical::disjunction(false, false));

    // conditional
    static_assert(logical::conditional(true, true, false));
    static_assert(!logical::conditional(true, false, true));
    static_assert(logical::conditional(false, false, true));
    static_assert(!logical::conditional(false, true, false));

    // gt
    static_assert(!logical::gt(8, 9));
    static_assert(!logical::gt(8, 8));
    static_assert(logical::gt(9, 8));

    // gte
    static_assert(!logical::gte(8, 9));
    static_assert(logical::gte(8, 8));
    static_assert(logical::gte(9, 8));

    // lt
    static_assert(logical::lt(8, 9));
    static_assert(!logical::lt(8, 8));
    static_assert(!logical::lt(9, 8));

    // lte
    static_assert(logical::lte(8, 9));
    static_assert(logical::lte(8, 8));
    static_assert(!logical::lte(9, 8));

    // within_closed_interval
    static_assert(logical::within_closed_interval(2, 4, 2));
    static_assert(logical::within_closed_interval(2, 4, 3));
    static_assert(logical::within_closed_interval(2, 4, 4));
    static_assert(!logical::within_closed_interval(2, 4, 5));
    static_assert(!logical::within_closed_interval(2, 4, 1));

    // within_open_interval
    static_assert(!logical::within_open_interval(2, 4, 2));
    static_assert(logical::within_open_interval(2, 4, 3));
    static_assert(!logical::within_open_interval(2, 4, 4));
    static_assert(!logical::within_open_interval(2, 4, 5));
    static_assert(!logical::within_open_interval(2, 4, 1));

}

int main()
{
    return 1;
}