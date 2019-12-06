# Logical - A C++ Boolean Library
Short circuit evaluation is one of my favourite language features in C++. It can considerably boost performance but it can come at a price, namely, readability. Every programmer understands what each of these mean in the blink of an eye:

Expression  | Meaning
------------|------------------
`x < y`     | `x` less than `y`
`x > y`     | `x` greater than `y`
`x == y`    | `x` equals `y`
`x != y`    | `x` not equals `y`
`x ? y : z` | if `x` then `y` else `z`

But what about these?

Expression         | Meaning
-------------------|------------------
`x < y || x > z`   | `x` is in the interval `[y, z]`
`x >= y && x <= z` | `x` is in the interval `[y, z]`
`x ? y : true`     | `x` implies `y`
`x == y`    | `x` equals `y`
`x != y`    | `x` not equals `y`
`x ? y : z` | if `x` then `y` else `z`
