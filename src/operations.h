#ifndef LOGICAL_OPERATIONS
#define LOGICAL_OPERATIONS

namespace logical {

    /**
     * Conventions:
     * Let op be the name of the operation, then:
     * <op>_t is the type of the operation
     * <op>_t::evaluate(...) is a static function that implements the operation
     */

    /**
     * Basic operations:
     * <op         > - <arity  > / <description        >
     *  negate       -  unary    /  negates a predicate
     *  eq           -  binary   /  computes equality
     *  neq          -  binary   /  computes inequality
     *  conjunction  -  binary   /  logical and
     *  disjunction  -  binary   /  logical or
     *  conditional  -  ternary  /  if a then b else c
     */

    struct negate_t
    {
        template <typename P>
        static constexpr bool evaluate(P&& predicate)
        {
            return !predicate;
        }
    };

    struct eq_t
    {
        template <typename L, typename R>
        static constexpr bool evaluate(L&& left, R&& right)
        {
            return left == right;
        }
    };

    struct neq_t
    {
        template <typename L, typename R>
        static constexpr bool evaluate(L&& left, R&& right)
        {
            return negate_t::evaluate(eq_t::evaluate(left, right));
        }
    };

    struct conjunction_t
    {
        template <typename L, typename R>
        static constexpr bool evaluate(L&& left, R&& right)
        {
            return left && right;
        }
    };

    struct disjunction_t
    {
        template <typename L, typename R>
        static constexpr bool evaluate(L&& left, R&& right)
        {
            return left || right;
        }
    };

    struct conditional_t
    {
        template <typename C, typename L, typename R>
        static constexpr bool evaluate(C&& condition, L&& left, R&& right)
        {
            return condition ? left : right;
        }
    };

    /**
     * Mathematic operations:
     * <op                    > - <arity  > / <description               >
     *  gt                      -  binary   /  computes a > b
     *  gte                     -  binary   /  computes a >= b
     *  lt                      -  binary   /  computes a < b
     *  lte                     -  binary   /  computes a <= b
     *  within_closed_interval  -  ternary  /  computes if c is in [a, b]
     *  within_open_interval    -  ternary  /  computes if c is in (a, b)
     */

    struct gt_t
    {
        template <typename L, typename R>
        static constexpr bool evaluate(L&& left, R&& right)
        {
            return left > right;
        }
    };

    struct gte_t
    {
        template <typename L, typename R>
        static constexpr bool evaluate(L&& left, R&& right)
        {
            return gt_t::evaluate(left, right) || eq_t::evaluate(left, right);
        }
    };

    struct lt_t
    {
        template <typename L, typename R>
        static constexpr bool evaluate(L&& left, R&& right)
        {
            return left < right;
        }
    };

    struct lte_t
    {
        template <typename L, typename R>
        static constexpr bool evaluate(L&& left, R&& right)
        {
            return lt_t::evaluate(left, right) || eq_t::evaluate(left, right);
        }
    };

    struct within_closed_interval_t
    {
        template <typename IntervalL, typename IntervalR, typename Value>
        static constexpr bool evaluate(IntervalL&& l, IntervalR&& r, Value&& val)
        {
            return gte_t::evaluate(r, val) && lte_t::evaluate(l, val);
        }
    };

    struct within_open_interval_t
    {
        template <typename IntervalL, typename IntervalR, typename Value>
        static constexpr bool evaluate(IntervalL&& l, IntervalR&& r, Value&& val)
        {
            return gt_t::evaluate(r, val) && lt_t::evaluate(l, val);
        }
    };

}

#endif // LOGICAL_OPERATIONS