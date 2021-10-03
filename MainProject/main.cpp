#include <algorithm>
#include <execution>
#include <iostream>
#include <numbers>
#include <numeric>
#include <random>
#include <vector>
#include "curve.h"

int main()
{
	constexpr int curveNum = 500;
	std::vector<std::shared_ptr<Curve>> curves(curveNum);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(0, 2);

	auto createRandomCurve = [&]()  {
		const int curveType = distr(gen);
		if (0 == curveType)
		{
			std::shared_ptr<Curve> curvePtr(new Circle());
			curvePtr->fillRandomParams();
			return curvePtr;
		}
		else if (1 == curveType)
		{
			std::shared_ptr<Curve> curvePtr(new Ellipse());
			curvePtr->fillRandomParams();
			return curvePtr;
		}
		else // (2 == curveType)
		{
			std::shared_ptr<Curve> curvePtr(new Helix());
			curvePtr->fillRandomParams();
			return curvePtr;
		}
	};

	std::generate(curves.begin(), curves.end(), createRandomCurve);

	//----------------------------------------------

	auto t = std::numbers::pi / 4;
	std::for_each(curves.begin(), curves.end(), 
		[=](const auto& curvePtr) { curvePtr->printCurve(t); });

	//----------------------------------------------

	std::vector<std::shared_ptr<Circle>> circles;
	std::for_each(curves.begin(), curves.end(),
		[&](const auto curvePtr) { 
			if (auto downCast = std::dynamic_pointer_cast<Circle>(curvePtr))
				circles.push_back(downCast);
		});

	//----------------------------------------------
	
	std::sort(circles.begin(), circles.end(),
		[](const auto& a, const auto& b) { return a->getRadius() < b->getRadius(); });

	// test code
	//std::cout << "\n\n\nTEST\n";
	//std::for_each(circles.begin(), circles.end(),
	//	[=](const auto& curvePtr) { std::cout << curvePtr->getRadius() << "\n"; });

	//----------------------------------------------

	// вариант без параллельных вычислений
	//double sum = std::accumulate(circles.begin(), circles.end(), 0.0,
	//	[](double res, const auto& x) { return res + x->getRadius(); });

	auto sum = std::transform_reduce(std::execution::par, circles.begin(), circles.end(), 0.0,
		[](double a, double b) { return a + b; },
		[](const auto& elem) { return elem->getRadius(); });

	std::cout << "\nTotal of the radii of the circles: " << sum << "\n";
}