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

        // Allow implicit conversion of closure_t to return type of operation
        template <typename T = return_type_if_callable<Op, Args...>>
        constexpr operator typename T::type() const
        {
            static_assert(closure_callable);
            return std::apply([this](auto... args){ return Op::evaluate(args...); }, args);
        }

        // Allow implicit conversion of closure_t to types that are implicitly convertible from return type of operation
        template <typename T>
        constexpr operator T() const
        {
            return static_cast<return_type_if_callable_t<Op, Args...>>(*this);
        }

        // Allow currying if type is not callable
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