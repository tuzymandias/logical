#ifndef LOGICAL_OPERATIONS
#define LOGICAL_OPERATIONS

namespace logical::operations {

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
        constexpr bool operator()(P&& predicate) const
        {
            return !predicate;
        }
    };

    static constexpr negate_t negate;

    struct eq_t
    {
        template <typename L, typename R>
        constexpr bool operator()(L&& left, R&& right) const
        {
            return left == right;
        }
    };

    static constexpr eq_t eq;

    struct neq_t
    {
        template <typename L, typename R>
        constexpr bool operator()(L&& left, R&& right) const
        {
            return negate(eq(left, right));
        }
    };

    static constexpr neq_t neq;

    struct conjunction_t
    {
        template <typename L, typename R>
        constexpr bool operator()(L&& left, R&& right) const
        {
            return left && right;
        }
    };

    static constexpr conjunction_t conjunction;

    struct disjunction_t
    {
        template <typename L, typename R>
        constexpr bool operator()(L&& left, R&& right) const
        {
            return left || right;
        }
    };

    static constexpr disjunction_t disjunction;

    struct conditional_t
    {
        template <typename C, typename L, typename R>
        constexpr bool operator()(C&& condition, L&& left, R&& right) const
        {
            return condition ? left : right;
        }
    };

    static constexpr conditional_t conditional;

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
        constexpr bool operator()(L&& left, R&& right) const
        {
            return left > right;
        }
    };

    static constexpr gt_t gt;

    struct gte_t
    {
        template <typename L, typename R>
        constexpr bool operator()(L&& left, R&& right) const
        {
            return gt(left, right) && eq(left, right);
        }
    };

    static constexpr gte_t gte;

    struct lt_t
    {
        template <typename L, typename R>
        constexpr bool operator()(L&& left, R&& right) const
        {
            return left < right;
        }
    };

    static constexpr lt_t lt;

    struct lte_t
    {
        template <typename L, typename R>
        constexpr bool operator()(L&& left, R&& right) const
        {
            return lt(left, right) && eq(left, right);
        }
    };

    static constexpr lte_t lte;

}

#endif // LOGICAL_OPERATIONS