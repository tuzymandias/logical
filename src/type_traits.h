#ifndef LOGICAL_TYPE_TRAITS
#define LOGICAL_TYPE_TRAITS

#include <type_traits>

namespace logical
{
    /**
     * is_callable: 
     * a type trait to test if 'Op::evaluate(...)' can be called using the variadic template parameters as arguments
     */
    template <typename Op, typename... Args>
    class is_callable
    {
    private:
        template <typename C> static constexpr bool test(decltype(&C::template evaluate<Args...>)) { return true; };
        template <typename C> static constexpr bool test(...) { return false; };

    public:
        static constexpr bool value = test<Op>(0);
    };

    template <typename Op, typename... Args>
    static constexpr bool is_callable_v = is_callable<Op, Args...>::value;

    /**
     * return_type_if_callable:
     * a type trait that provides the return type of 'Op::evaluate(Args...)' if the function exists
     */
    template <bool Enabled, typename Op, typename... Args>
    struct return_type_if_callable_h
    {};

    template <typename Op, typename... Args>
    struct return_type_if_callable_h<true, Op, Args...>
    {
        using type = std::invoke_result_t<decltype(Op::template evaluate<Args...>), Args...>;
    };

    template <typename Op, typename... Args>
    struct return_type_if_callable : return_type_if_callable_h<is_callable_v<Op, Args...>, Op, Args...>
    {};

    template <typename Op, typename... Args>
    using return_type_if_callable_t = typename return_type_if_callable<Op, Args...>::type;
}

#endif // LOGICAL_TYPE_TRAITS