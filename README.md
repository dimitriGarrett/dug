# Dimitri's Universal Goodies (dug)
This is a small collection of utilities that I use in almost every project, so I thought I would put it all together into one easy to use library.

# Example

```

#include <iostream>
#include "dug.h"

void func(int, int);

int main()
{
    int a = 2;
    int b = 3;

    std::cout << "a: " << a << std::endl; // Prints 2
    pack::nth_value<0>(a, b) = b;
    std::cout << "a: " << a << std::endl; // Prints 3

    static_assert(std::is_same_v<pack::nth_type<1, int, char, bool>, char>, "Pretty neat!");
    //static_assert(std::is_same_v<pack::nth_type<1, int>, char>, "This would cause a static_assert to go off!");

    static_assert(typify::get<int>() == "int", "Turn a type into a string!");
    
    static_assert(std::is_same_v<function::traits<decltype(func)>::arg<1>, int>, "Get argument types from functions!");
}

```