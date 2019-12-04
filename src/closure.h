#ifndef LOGICAL_CLOSURE
#define LOGICAL_CLOSURE

#include <tuple>

#include "type_traits.h"

namespace logical {

    template <typename Op, typename... Args>
    struct closure_t
    {
    private:
        static constexpr bool closure_callable = is_callable_v<Op, Args...>;

        template <typename... AdditionalArgs>
        using enable_composition = std::enable_if_t<!closure_callable, closure_t<Op, Args..., AdditionalArgs...>>;

    public:
        constexpr closure_t(Args&&... args)
            : args{ std::forward_as_tuple(std::forward<Args>(args)...) }
        {}

        constexpr operator bool() const
        {
            // FIXME: Convert this static_assert to template SFINAE
            static_assert(closure_callable);
            return std::apply([this](auto... args){ return Op::evaluate(args...); }, args);
        }

        template <typename... AdditionalArgs>
        constexpr auto operator()(AdditionalArgs&&... additional_args) const
            -> enable_composition<AdditionalArgs...>
        {
            return std::apply(
                [this](auto&&... args) { return enable_composition<AdditionalArgs...>{ std::forward<decltype(args)>(args)... }; },
                std::tuple_cat(args, std::forward_as_tuple(std::forward<AdditionalArgs>(additional_args)...))
            );
        }

        std::tuple<Args...> args;
    };
    
}

#endif // LOGICAL_CLOSURE