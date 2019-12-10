#define LOGICAL_SHORTEN_NAMESPACE
#include "src/bindings.h"

namespace {

    // negate
    static_assert(lgc::negate(false));
    static_assert(!lgc::negate(true));

    // eq
    static_assert(lgc::eq(true, true));
    static_assert(!lgc::eq(true, false));
    static_assert(lgc::eq(9, 9));
    static_assert(!lgc::eq(9, 10));

    // neq
    static_assert(!lgc::neq(true, true));
    static_assert(lgc::neq(true, false));
    static_assert(!lgc::neq(9, 9));
    static_assert(lgc::neq(9, 10));

    // conjunction
    static_assert(lgc::conjunction(true, true));
    static_assert(!lgc::conjunction(true, false));
    static_assert(!lgc::conjunction(false, true));
    static_assert(!lgc::conjunction(false, false));

    // disjunction
    static_assert(lgc::disjunction(true, true));
    static_assert(lgc::disjunction(true, false));
    static_assert(lgc::disjunction(false, true));
    static_assert(!lgc::disjunction(false, false));

    // conditional
    static_assert(lgc::conditional(true, true, false));
    static_assert(!lgc::conditional(true, false, true));
    static_assert(lgc::conditional(false, false, true));
    static_assert(!lgc::conditional(false, true, false));

    // gt
    static_assert(!lgc::gt(8, 9));
    static_assert(!lgc::gt(8, 8));
    static_assert(lgc::gt(9, 8));

    // gte
    static_assert(!lgc::gte(8, 9));
    static_assert(lgc::gte(8, 8));
    static_assert(lgc::gte(9, 8));

    // lt
    static_assert(lgc::lt(8, 9));
    static_assert(!lgc::lt(8, 8));
    static_assert(!lgc::lt(9, 8));

    // lte
    static_assert(lgc::lte(8, 9));
    static_assert(lgc::lte(8, 8));
    static_assert(!lgc::lte(9, 8));

    // within_closed_interval
    static_assert(lgc::within_closed_interval(2, 4, 2));
    static_assert(lgc::within_closed_interval(2, 4, 3));
    static_assert(lgc::within_closed_interval(2, 4, 4));
    static_assert(!lgc::within_closed_interval(2, 4, 5));
    static_assert(!lgc::within_closed_interval(2, 4, 1));

    // within_open_interval
    static_assert(!lgc::within_open_interval(2, 4, 2));
    static_assert(lgc::within_open_interval(2, 4, 3));
    static_assert(!lgc::within_open_interval(2, 4, 4));
    static_assert(!lgc::within_open_interval(2, 4, 5));
    static_assert(!lgc::within_open_interval(2, 4, 1));

}

int main()
{
    return 1;
}