# Logical - A C++ Boolean Library
Short circuit evaluation is one of my favourite language features in C++. It can considerably boost performance but it can come at a price, namely, readability. 

Let us take a detour and consider the following code:
```C++
struct Item { 
    int quantity;
    double price;
};

double AveragePriceInline(const Item& item_l, const Item& item_r) {
    return (item_l.quantity * item_l.weight + item_r.quantity * item_r.weight) / (item_l.quantity + item_r.quantity);
}

double AveragePriceNamed(const Item& item_l, const Item& item_r) {
    const auto total_price_l = item_l.quantity * item_l.weight;
    const auto total_price_r = item_r.quantity * item_r.weight;
    const auto total_quantity = item_l.quantity + item_r.quantity;
    return (total_weight_l + total_weight_r) / total_quantity;
}
```
In the above example, we have a struct `Item` that holds two fields `quantity` and `price`. We also have two functions `AveragePriceInline` and `AveragePriceNamed`, both of which calculates the average price between two `Item`s. Compare the two functions, both are correct and are equally performant but which one would you prefer? I think people generally would agree that splitting a long expression into smaller named constituents is good style and would thus prefer `AveragePriceNamed`. 

Now lets get back to short circuit evaluation. To put it simply, when it comes to long boolean expressions, you don't have much of an option. If you do what we did in `AveragePriceNamed`, you will actually lose performance. For each named sub-expression, the compiler will have to evaluate them individually, reducing the benefits of short-circuitting. You are left with two choices: either you inline it or you use `lambda`s to split it to smaller expressions. I much prefer the latter, but it comes with a few downsides:

1. Dealing with writing lambdas, not that they are bad, but because of the cognitive overhead of having to context switch from writing expressions to writting functions.
2. Style divergence: lambdas often look out of place; you have to deal with functor semantics.

And thus this library was born. It was written with the intent of emulating the benefits of lambdas in this particular scenario where we want to benefit from short-circuitting, without the aforementioned downsides. 

The `logical` library implements basic logical (conjunction, disjunction, etc) and mathematical comparison operations (less than, equality, etc) in the form of free functions. Instead of evaluating the result directly on function call, each of them returns an object that the operands are bound to. These objects can then be used in traditional logical operations, implicitly converting them to `bool` and causing the evaluation to happen. You can also pass them around as arguments into `logical` functions, likewise no evaluation will happen until absolutely needed. This is akin to lazy evaluation in functional programming.

**Note:** This library is pretty much experimental, please read on before using. There are tests, but the library is not benchmarked. Without compiler optimizations turned on, using this library will incur a performance hit.

# Examples
Test if a value is within the closed interval `[range_l, range_r]` (Note: `logical` already implements a convenience function for this called `within_closed_interval`).
```C++
#include "src/bindings.h"

bool WithinClosedInterval(int range_l, int range_r, int value)
{
    auto more_than_l = logical::gte(value, range_l);
    auto less_than_r = logical::lte(value, range_r);
    return more_than_l && less_than_r;
}
```

Same example as above, utilising partial binding.
```C++
#include "src/bindings.h"

bool WithinClosedInterval(int range_l, int range_r, int value)
{
    auto more_than_l = logical::lt(range_l);
    auto less_than_r = logical::gt(range_r);
    return more_than_l(value) && less_than_r(value);
}
```

# Advantages
1. Performance is identical to inlining expressions (Requires at least -O1 on gcc or -O2 on clang)

# Using Custom Types
1. When using this library on non-primitive types, the respective operators have to be implemented.
    * For any two types `X` and `Y`, for `logical::eq(X, Y)` to be valid, `bool X::operator==(Y)` have to be defined.

# Todo-List
1. Add benchmarks.
2. Add more examples.
3. Extend to include mathematical operations like addition or subtraction. (out of scope)
4. Allow implicit conversion to return type of `evaluation(...)` (out of scope)