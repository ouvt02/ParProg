#pragma once
#include <cmath>

class Complex
{
    public:
        double image = 0.0;
        double real = 0.0;

        Complex() { }

        Complex(double r, double img)
        {
            this -> image = img;
            this -> real = r;
        }

        Complex operator+(Complex other)
        {
            return Complex(this -> real + other.real, this -> image + other.image);
        }

        Complex operator-(Complex other)
        {
            return Complex(this -> real - other.real, this -> image - other.image);
        }

        Complex operator*(Complex other)
        {
            return Complex(this -> real * other.real - this -> image * other.image, 
                            this -> image * other.real + this -> real * other.image);
        }

        double abs()
        {
            return sqrt(this -> real * this -> real + this -> image * this -> image);
        }

        Complex operator/(Complex other)
        {
            double denominator = other.abs();
            return Complex((this -> real * other.real + this -> image * other.image)/denominator, 
                            (other.real * this -> image - this -> real * other.image)/denominator);
        }

        static Complex e_in_pow(Complex power)
        {
            double phi = power.image;
            return Complex(exp(power.real) * cos(phi), exp(power.real) * sin(phi));
        }

};