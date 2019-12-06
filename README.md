# Logical - A C++ Boolean Library
Short circuit evaluation is one of my favourite language features in C++. It can considerably boost performance but it can come at a price, namely, readability. 

Consider the following code:
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
In the above example, we have a struct `Item` that holds two fields `quantity` and `price`. We also have two functions `AveragePriceInline` and `AveragePriceNamed`, both of which calculates the average price between two `Item`s. Compare the two functions, both are correct but which one would you prefer? I think people generally would agree that splitting a long expression into smaller named constituents is good style and would thus prefer `AveragePriceNamed`. 

Now lets get back to short circuit evaluation. To put it simply, when it comes to long boolean expressions, you don't have much of an option. Either you inline it or you use `lambda`s to split it to smaller expressions. I much prefer the latter, but it comes with a few downsides:

1. Writing lambdas is cumbersome
2. You have to deal with functor semantics