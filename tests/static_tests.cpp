#include "src/bindings.h"

namespace {

    // negate
    static_assert(logical::bind_negate(false));
    static_assert(!logical::bind_negate(true));

    // eq
    static_assert(logical::bind_eq(true, true));
    static_assert(!logical::bind_eq(true, false));
    static_assert(logical::bind_eq(9, 9));
    static_assert(!logical::bind_eq(9, 10));

    // neq
    static_assert(!logical::bind_neq(true, true));
    static_assert(logical::bind_neq(true, false));
    static_assert(!logical::bind_neq(9, 9));
    static_assert(logical::bind_neq(9, 10));

    // conjunction
    static_assert(logical::bind_conjunction(true, true));
    static_assert(!logical::bind_conjunction(true, false));
    static_assert(!logical::bind_conjunction(false, true));
    static_assert(!logical::bind_conjunction(false, false));

    // disjunction
    static_assert(logical::bind_disjunction(true, true));
    static_assert(logical::bind_disjunction(true, false));
    static_assert(logical::bind_disjunction(false, true));
    static_assert(!logical::bind_disjunction(false, false));

    // conditional
    static_assert(logical::bind_conditional(true, true, false));
    static_assert(!logical::bind_conditional(true, false, true));
    static_assert(logical::bind_conditional(false, false, true));
    static_assert(!logical::bind_conditional(false, true, false));

    // gt
    static_assert(!logical::bind_gt(8, 9));
    static_assert(!logical::bind_gt(8, 8));
    static_assert(logical::bind_gt(9, 8));

    // gte
    static_assert(!logical::bind_gte(8, 9));
    static_assert(logical::bind_gte(8, 8));
    static_assert(logical::bind_gte(9, 8));

    // lt
    static_assert(logical::bind_lt(8, 9));
    static_assert(!logical::bind_lt(8, 8));
    static_assert(!logical::bind_lt(9, 8));

    // lte
    static_assert(logical::bind_lte(8, 9));
    static_assert(logical::bind_lte(8, 8));
    static_assert(!logical::bind_lte(9, 8));

    // within_closed_interval
    static_assert(logical::bind_within_closed_interval(2, 4, 2));
    static_assert(logical::bind_within_closed_interval(2, 4, 3));
    static_assert(logical::bind_within_closed_interval(2, 4, 4));
    static_assert(!logical::bind_within_closed_interval(2, 4, 5));
    static_assert(!logical::bind_within_closed_interval(2, 4, 1));

    // within_open_interval
    static_assert(!logical::bind_within_open_interval(2, 4, 2));
    static_assert(logical::bind_within_open_interval(2, 4, 3));
    static_assert(!logical::bind_within_open_interval(2, 4, 4));
    static_assert(!logical::bind_within_open_interval(2, 4, 5));
    static_assert(!logical::bind_within_open_interval(2, 4, 1));

}

int main()
{
    return 1;
}