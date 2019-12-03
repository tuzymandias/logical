#ifndef LOGICAL_CLOSURE
#define LOGICAL_CLOSURE

#include <tuple>

namespace logical {

    template <typename Op, typename... Args>
    struct closure_t
    {
        constexpr closure_t(Args&&... args)
            : args{ std::forward<Args>(args)... }
        {}

        constexpr operator bool() const
        {
            return std::apply([this](auto... args){ return Op::evaluate(args...); }, args);
        }

        std::tuple<Args...> args;
    };

}

#endif // LOGICAL_CLOSURE