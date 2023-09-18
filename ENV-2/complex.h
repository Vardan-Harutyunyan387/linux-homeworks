#pragma once
#include <cmath>
#include <iostream>
#include <vector>

class Complex
{
private:
    double re;
    double im;
    double abs_value;
public:
    Complex():re(0), im(0), abs_value(0){};
    Complex(double re, double im = 0);
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const double num) const;
    friend std::ostream& operator<<(std::ostream& out, const  Complex& clx); 
    double abs();
};

void sort_complex(std::vector<Complex> &vec);