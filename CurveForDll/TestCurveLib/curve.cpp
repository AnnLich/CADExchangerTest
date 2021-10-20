#include <random>
#include <chrono>
#include <iostream>
#include "curve.h"

double randomValue()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distr(0, 500);
    return distr(gen);
}


Circle::Circle(const double R) : radius{ R }
{
}

Circle::Circle()
{
    radius = 1.0;
}

Circle::~Circle()
{
}

void Circle::fillRandomParams()
{
    radius = randomValue();
}

Point3D Circle::getPoint3D(const double t) const
{
    return Point3D{ radius * std::cos(t), radius * std::sin(t), 0.0 };
}

Point3D Circle::getFirstDerivative(const double t) const
{
    return Point3D{ radius * (-std::sin(t)), radius * std::cos(t), 0.0 };
}

void Circle::printCurve(const double t) const
{
    const auto point = getPoint3D(t);
    const auto derivative = getFirstDerivative(t);

    std::cout << "The Curve is the Circle:\n"
        << "C(t) = {" << point.x << ", " << point.y << "}\n"
        << "C'(t) = {" << derivative.x << ", " << derivative.y << "}\n\n";
}


Ellipse::Ellipse(const double R1, const double R2) : radiusX{ R1 }, radiusY{ R2 }
{
}

Ellipse::Ellipse()
{
    radiusX = 1.0;
    radiusY = 1.0;
}

Ellipse::~Ellipse()
{
}

void Ellipse::fillRandomParams()
{
    radiusX = randomValue();
    radiusY = randomValue();
}

Point3D Ellipse::getPoint3D(const double t) const
{
    return Point3D{ radiusX * std::cos(t), radiusY * std::sin(t), 0.0 };
}

Point3D Ellipse::getFirstDerivative(const double t) const
{
    return Point3D{ radiusX * (-std::sin(t)), radiusY * std::cos(t), 0.0 };
}

void Ellipse::printCurve(const double t) const
{
    const auto point = getPoint3D(t);
    const auto derivative = getFirstDerivative(t);

    std::cout << "The Curve is the Ellipse:\n"
        << "C(t) = {" << point.x << ", " << point.y << "}\n"
        << "C'(t) = {" << derivative.x << ", " << derivative.y << "}\n\n";
}

Helix::Helix(const double R, const double zstep) : radius{ R }, step{ zstep }
{
}

Helix::Helix()
{
    radius = 1.0;
    step = 1.0;
}

Helix::~Helix()
{
}

void Helix::fillRandomParams()
{
    radius = randomValue();
    step = randomValue();
}

Point3D Helix::getPoint3D(const double t) const
{
    return Point3D{ radius * std::cos(t), radius * std::sin(t), step * t / (2 * std::numbers::pi) };
}

Point3D Helix::getFirstDerivative(const double t) const
{
    return Point3D{ radius * (-std::sin(t)), radius * std::cos(t), step / (2 * std::numbers::pi)  };
}

void Helix::printCurve(const double t) const
{
    const auto point = getPoint3D(t);
    const auto derivative = getFirstDerivative(t);

    std::cout << "The Curve is the Helix:\n"
        << "C(t) = {" << point.x << ", " << point.y << ", " << point.z << "}\n"
        << "C'(t) = {" << derivative.x << ", " << derivative.y << ", " << point.z << "}\n\n";
}
