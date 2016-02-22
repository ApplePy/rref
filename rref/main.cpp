//
//  main.cpp
//  rref
//
//  Created by Darryl Murray on 2016-02-21.
//  Copyright © 2016 Darryl Murray. All rights reserved.
//

#include <iostream>
#include "rational.h"
#include <vector>
#include <sstream>

using namespace std;

void print_matrix(vector<vector<Rational>>& matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j] << "   ";
        }
        cout << endl;
    }
}

void rref_helper(vector<Rational>& firstRow, vector<Rational>& secondRow, int col) {
    if (firstRow.size() != secondRow.size()) {
        throw std::string("wtf.");
    }
    
    for (int i = 0; i < firstRow.size(); i++) {
        secondRow[i] += firstRow[i] * -secondRow[col]/firstRow[col];
    }
}

vector<vector<Rational>> rref(vector<vector<Rational>>& input) {
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input.size(); j++) {
            if (i == j) continue;
            else {
                rref_helper(input[i], input[j], i);
                cout << "i: " << i << " j: " << j << endl;
                print_matrix(input);
                cout << endl;
            }
        }
    }
    
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input.size(); j++) {
            input[i][j] *= Rational(input[i][i].getDenominator(),input[i][i].getNumerator());
        }
    }
    
    return input;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    vector<vector<Rational>> matrix;
    
    string input;
    while (true) {
        vector<Rational> row;
        getline(cin, input);
        
        if (input.length() == 0)
            break;
        
        stringstream processing;
        long long numerator(0), denominator(0);
        bool numeratorSet = false;
        for (int i = 0; i < input.length(); i++) {
            if (input[i] == '/') {
                processing >> numerator;
                auto temp = stringstream();
                
                // Clean out stream
                processing.str( std::string() );
                processing.clear();
                
                numeratorSet = true;
            }
            else if (input[i] == ' ') {
                if (numeratorSet)
                    processing >> denominator;
                else
                    processing >> numerator;
                auto temp = stringstream();
                
                // Clean out stream
                processing.str( std::string() );
                processing.clear();
                
                if (denominator == 0) denominator = 1;
                row.push_back(Rational(numerator, denominator));
                numerator = 0;
                denominator = 0;
                numeratorSet = false;
            }
            else {
                processing << input[i];
                //cout << processing.str() << endl;
            }
        }
        
        if (numeratorSet)
            processing >> denominator;
        else
            processing >> numerator;
        auto temp = stringstream();
        
        // Clean out stream
        processing.str( std::string() );
        processing.clear();
        
        if (denominator == 0) denominator = 1;
        row.push_back(Rational(numerator, denominator));
        numerator = 0;
        denominator = 0;
        numeratorSet = false;
        
        matrix.push_back(row);
    }
    
    rref(matrix);
    
    print_matrix(matrix);
    
    
    return 0;
}
