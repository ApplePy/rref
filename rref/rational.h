//
//  rational.h
//  rras
//
//  Created by Darryl Murray on 2016-02-21.
//  Copyright © 2016 Darryl Murray. All rights reserved.
//

#ifndef rational_h
#define rational_h

#include <string>
#include <sstream>
#include <cmath>

class Rational {
public:
    //Constructors
    Rational (long long num, long long den) {
        numerator = num;
        denominator = den;
        rationalize();
    }
    
    // Getters/Setters
    long long getNumerator() {
        return numerator;
    }
    long long getDenominator() {
        return denominator;
    }
    
    void setNumerator(long long input) {
        numerator = input;
        rationalize();
    }
    void setDenominator(long long input) {
        denominator = input;
        rationalize();
    }
    
    // Arithmetic Operators
    Rational operator-() {
        return Rational(-numerator, denominator);
    }
    Rational operator+(const Rational& other) {
        long long newNumerator = numerator + other.numerator;
        long long newDenominator = denominator + other.denominator;
        return Rational(newNumerator, newDenominator);
    }
    Rational operator+(const long long& other) {
        long long newNumerator = numerator + other;
        return Rational(newNumerator, denominator);
    }
    Rational operator-(const Rational& other) {
        long long newNumerator = numerator - other.numerator;
        long long newDenominator = denominator - other.denominator;
        return Rational(newNumerator, newDenominator);
    }
    Rational operator-(const long long& other) {
        long long newNumerator = numerator - other;
        return Rational(newNumerator, denominator);
    }
    Rational operator*(const Rational& other) {
        long long newNumerator = numerator * other.numerator;
        long long newDenominator = denominator * other.denominator;
        return Rational(newNumerator, newDenominator);
    }
    Rational operator*(const long long& other) {
        long long newNumerator = numerator * other;
        long long newDenominator = denominator;
        return Rational(newNumerator, newDenominator);
    }
    Rational operator/(const Rational& other) {
        long long newNumerator = numerator * other.denominator;
        long long newDenominator = denominator * other.numerator;
        return Rational(newNumerator, newDenominator);
    }
    Rational operator/(const long long& other) {
        long long newDenominator = denominator * other;
        return Rational(numerator, newDenominator);
    }
    template <class T>
    void operator+=(const T& other) {
        Rational result = *this + other;
        numerator = result.numerator;
        denominator = result.denominator;
    }
    template <class T>
    void operator-=(const T& other) {
        Rational result = *this - other;
        numerator = result.numerator;
        denominator = result.denominator;
    }
    template <class T>
    void operator*=(const T& other) {
        Rational result = *this * other;
        numerator = result.numerator;
        denominator = result.denominator;
    }
    template <class T>
    void operator/=(const T& other) {
        Rational result = *this / other;
        numerator = result.numerator;
        denominator = result.denominator;
    }
    
    //Conversion Operators
    operator std::string() {
        std::stringstream numStringStream = std::stringstream();
        numStringStream << numerator;
        std::string numString = numStringStream.str();
        
        // Clean out stream
        numStringStream.str( std::string() );
        numStringStream.clear();
        
        numStringStream << denominator;
        std::string denString = numStringStream.str();
        return std::string(numString + "/" + denString);
    }
    operator const char*() {
        return operator std::string().c_str();
    }
    std::string getString() {
        return operator std::string();
    }
    
protected:
    long long numerator;
    long long denominator;
    
    void rationalize() {
        
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
        
        int gcd = 1;
        
        for(int i=1;i<=abs(numerator)&&i<=abs(denominator);i++){
            if(numerator%i==0 && denominator%i == 0 ){
                gcd=i;
            }
        }
        numerator /= gcd;
        denominator /= gcd;
        
        if (numerator == 0)
            denominator = 1;
    }
};

#endif /* rational_h */
