#include <iostream>
#include <memory>
#include "Array.h"
#include "Triangle.h"
#include "Square.h"
#include "Octagon.h"

int main()
{
    Array<std::shared_ptr<Figure<double>>> figures;
    std::cout << "=== Shape Creation ===\n";

    std::cout << "\n--- Triangle ---\n";
    auto triangle = std::make_shared<Triangle<double>>();
    std::cin >> *triangle;
    figures.add(triangle);

    std::cout << "\n--- Square ---\n";
    auto square = std::make_shared<Square<double>>();
    std::cin >> *square;
    figures.add(square);

    std::cout << "\n--- Octagon ---\n";
    auto octagon = std::make_shared<Octagon<double>>();
    std::cin >> *octagon;
    figures.add(octagon);

    std::cout << "\n=== Shape Information ===\n";
    for (size_t i = 0; i < figures.size(); ++i)
    {
        std::cout << "Shape " << i + 1 << ": " << *figures[i] << "\n";
        std::cout << "Center: " << figures[i]->center() << "\n";
        std::cout << "Area: " << static_cast<double>(*figures[i]) << "\n";
    }

    double totalArea = 0.0;
    for (size_t i = 0; i < figures.size(); ++i)
        totalArea += static_cast<double>(*figures[i]);

    std::cout << "\nTotal area: " << totalArea << "\n";
    return 0;
}