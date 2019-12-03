#ifndef LOGICAL_BINDINGS
#define LOGICAL_BINDINGS

#include "operations.h"
#include "closure.h"

#define BIND_IMPL(op) \
template <typename... Args> \
constexpr auto bind_##op(Args&&... args) \
{ \
    return bind<op##_t>(std::forward<Args>(args)...); \
}

namespace logical {

    template <typename Op, typename... Args>
    constexpr closure_t<Op, Args...> bind(Args&&... args)
    {
        return { std::forward<Args>(args)... };
    }

    BIND_IMPL(eq)
    BIND_IMPL(negate)
    BIND_IMPL(neq)
    BIND_IMPL(conjunction)
    BIND_IMPL(disjunction)
    BIND_IMPL(conditional)

    BIND_IMPL(gt)
    BIND_IMPL(gte)
    BIND_IMPL(lt)
    BIND_IMPL(lte)

    static_assert(bind_eq(true, true));
    static_assert(bind_lt(10, 100u));
    static_assert(bind_eq(bind_negate(false), true));    
}

#undef BIND_IMPL

#endif // LOGICA_BINDINGS