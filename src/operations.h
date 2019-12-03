#ifndef LOGICAL_OPERATIONS
#define LOGICAL_OPERATIONS

namespace logical {

    /**
     * Conventions:
     * Let op be the name of the operation, then:
     * <op>_t is the type of the operation, it implements the operation
     * <op> is an instantiation of <op>_t
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
     * <op  > - <arity  > / <description        >
     *  gt    -  binary   /  computes a > b
     *  gte   -  binary   /  computes a >= b
     *  lt    -  binary   /  computes a < b
     *  lte   -  binary   /  computes a <= b
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
            return gt_t::evaluate(left, right) && eq_t::evaluate(left, right);
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
            return lt_t::evaluate(left, right) && eq_t::evaluate(left, right);
        }
    };

}

#endif // LOGICAL_OPERATIONS