#pragma once

#ifdef TESTCURVELIB_EXPORTS
#define TESTCURVELIB_API __declspec(dllexport)
#else
#define TESTCURVELIB_API __declspec(dllimport)
#endif

struct TESTCURVELIB_API Point3D
{
	double x;
	double y;
	double z;
};

class TESTCURVELIB_API Curve {
public:
	virtual ~Curve() {}

	virtual void fillRandomParams() = 0;

	virtual Point3D getPoint3D(const double t) const = 0;
	virtual Point3D getFirstDerivative(const double t) const = 0;

	virtual void printCurve(const double t) const = 0;

protected:
	Curve() = default;
	Curve(const Curve&) = delete;
	Curve& operator=(const Curve&) = delete;
	Curve(Curve&&) = delete;
	Curve& operator=(Curve&&) = delete;
};

class TESTCURVELIB_API Circle : public Curve {
public:
	Circle(const double R);
	Circle();
	~Circle() override;

	void fillRandomParams() override;

	Point3D getPoint3D(const double t) const override;
	Point3D getFirstDerivative(const double t) const override;

	void printCurve(const double t) const override;

	double getRadius() const { return radius; }
	void setRadius(double r) { radius = r; }

private:
	double radius;
};

class TESTCURVELIB_API Ellipse : public Curve {
public:
	Ellipse(const double R1, const double R2);
	Ellipse();
	~Ellipse() override;

	void fillRandomParams() override;

	Point3D getPoint3D(const double t) const override;
	Point3D getFirstDerivative(const double t) const override;

	void printCurve(const double t) const override;

	double getRadiusX() const { return radiusX; }
	void setRadiusX(double r) { radiusX = r; }
	double getRadiusY() const { return radiusY; }
	void setRadiusY(double r) { radiusY = r; }

private:
	double radiusX;
	double radiusY;
};


class TESTCURVELIB_API Helix : public Curve {
public:
	Helix(const double R, const double zstep);
	Helix();
	~Helix() override;

	void fillRandomParams() override;

	Point3D getPoint3D(const double t) const override;
	Point3D getFirstDerivative(const double t) const override;

	void printCurve(const double t) const override;

	double getRadius() const { return radius; }
	void setRadius(double r) { radius = r; }
	double getStep() const { return step; }
	void setStep(double s) { step = s; }

private:
	double radius;
	double step;
};
