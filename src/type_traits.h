#ifndef LOGICAL_TYPE_TRAITS
#define LOGICAL_TYPE_TRAITS

#include <type_traits>

namespace logical
{
    template <typename Op, typename... Args>
    class is_callable
    {
    private:
        template <typename C> static std::true_type  test(decltype(&C::template evaluate<Args...>));
        template <typename C> static std::false_type test(...);

    public:
        static constexpr bool value = std::is_same_v<decltype(test<Op>(0)), std::true_type>;
    };

    template <typename Op, typename... Args>
    static constexpr bool is_callable_v = is_callable<Op, Args...>::value;
}

#endif // LOGICAL_TYPE_TRAITS