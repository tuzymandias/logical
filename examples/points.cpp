#include <iostream>

#include "src/bindings.h"

namespace geom {

    struct Point 
    {
        int x;
        int y;
    };

    struct Square
    {
        Point origin;
        int width;
        int height;
    };

    constexpr bool WithinSquare1(const Square& square, const Point& point)
    {
        using namespace logical;
        const auto within_width  = conjunction(gte(point.x, square.origin.x), lte(point.x, square.origin.x + square.width));
        const auto within_height = conjunction(gte(point.y, square.origin.y), lte(point.y, square.origin.y + square.height));
        const auto within_square = conjunction(within_height, within_width);
        return within_square;
    }

    constexpr bool WithinSquare2(const Square& square, const Point& point)
    {
        return point.x >= square.origin.x && point.x <= square.origin.x + square.width &&
               point.y >= square.origin.y && point.y <= square.origin.y + square.width;
    }

    constexpr bool WithinSquare3(const Square& square, const Point& point)
    {
        const auto within_width = point.x >= square.origin.x && point.x <= square.origin.x + square.width;
        const auto within_height = point.y >= square.origin.y && point.y <= square.origin.y + square.width;
        const auto within_square = within_width && within_height;
        return within_square;
    }

    constexpr bool WithinSquare4(const Square& square, const Point& point)
    {
        const auto within_width = [&]{ return point.x >= square.origin.x && point.x <= square.origin.x + square.width; };
        const auto within_height = [&]{ return point.y >= square.origin.y && point.y <= square.origin.y + square.width; };
        const auto within_square = [&]{ return within_width() && within_height(); };
        return within_square();
    }
}

constexpr auto origin = geom::Point{ 0, 0 };
constexpr auto square = geom::Square{ { -2, -2 }, 4, 4 };

static_assert(geom::WithinSquare1(square, origin));
static_assert(geom::WithinSquare2(square, origin));
static_assert(geom::WithinSquare3(square, origin));
static_assert(geom::WithinSquare4(square, origin));

int main()
{
    constexpr auto point_3_3 = geom::Point{ 3, 3 };
    std::cout << "Point(3, 3) is within Square((-2, -2), 4, 4): " << std::boolalpha << geom::WithinSquare1(square, point_3_3) << "\n";
    std::cout << "Point(3, 3) is within Square((-2, -2), 4, 4): " << std::boolalpha << geom::WithinSquare2(square, point_3_3) << "\n";
    std::cout << "Point(3, 3) is within Square((-2, -2), 4, 4): " << std::boolalpha << geom::WithinSquare3(square, point_3_3) << "\n";
    std::cout << "Point(3, 3) is within Square((-2, -2), 4, 4): " << std::boolalpha << geom::WithinSquare4(square, point_3_3) << "\n";

    std::cout << "Point(0, 0) is within Square((-2, -2), 4, 4): " << std::boolalpha << geom::WithinSquare1(square, origin) << "\n";
    std::cout << "Point(0, 0) is within Square((-2, -2), 4, 4): " << std::boolalpha << geom::WithinSquare2(square, origin) << "\n";
    std::cout << "Point(0, 0) is within Square((-2, -2), 4, 4): " << std::boolalpha << geom::WithinSquare3(square, origin) << "\n";
    std::cout << "Point(0, 0) is within Square((-2, -2), 4, 4): " << std::boolalpha << geom::WithinSquare4(square, origin) << "\n";

    constexpr auto point_n3_n3 = geom::Point{ -3, -3 };
    std::cout << "Point(-3, -3) is within Square((-2, -2), 4, 4): " << std::boolalpha << geom::WithinSquare1(square, point_n3_n3) << "\n";
    std::cout << "Point(-3, -3) is within Square((-2, -2), 4, 4): " << std::boolalpha << geom::WithinSquare2(square, point_n3_n3) << "\n";
    std::cout << "Point(-3, -3) is within Square((-2, -2), 4, 4): " << std::boolalpha << geom::WithinSquare3(square, point_n3_n3) << "\n";
    std::cout << "Point(-3, -3) is within Square((-2, -2), 4, 4): " << std::boolalpha << geom::WithinSquare4(square, point_n3_n3) << "\n";

    
    return 1;
}