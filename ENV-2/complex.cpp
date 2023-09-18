#include "complex.h"



Complex::Complex(double re, double im):re(re), im(im)
{
    abs_value = std::sqrt(std::pow(re, 2) + std::pow(im, 2));
}

Complex Complex::operator+(const Complex& other) const
{
    return Complex(re + other.re, im + other.im);
}

Complex Complex::operator-(const Complex& other) const
{
    return Complex(re - other.re, im - other.im);
}

Complex Complex::operator*(const double num) const
{
    return Complex(re  * num,  im  * num);
}

double Complex::abs()
{
    return abs_value;
}

std::ostream& operator<<(std::ostream& out, const  Complex& clx)
{
    out<<'('<<clx.re<<", "<<clx.im<<"i)";
    return out;
}


void sort_complex(std::vector<Complex> &vec)
{
    int n = vec.size();
    Complex temp;
    bool swapped;

    for (int i = 0; i < n - 1; i++) {
        swapped = false;

        for (int j = 0; j < n - i - 1; j++) {
            if (vec[j].abs() > vec[j + 1].abs()) {
                //std::cout<<"swap";
                temp = vec[j];
                vec[j] = vec[j + 1];
                vec[j + 1] = temp;
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }
    }
}