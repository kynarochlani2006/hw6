#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
      int currIndex = 4;
      int len = k.length();
      int base = 36;
      unsigned long long w[5] = {0, 0, 0, 0, 0};

      for(int i = len; i > 0 && currIndex >= 0; i -= 6){
        unsigned long long chunktotal = 0;
        unsigned long long s = 1;

        int startofchunk = i - 6;
        if(startofchunk < 0){
          startofchunk = 0;
        }

        for(int j = i - 1; j >= startofchunk; j--){
          HASH_INDEX_T number;

          if(std::isdigit(k[j])){
            number = letterDigitToNumber(k[j]);
          } else {
            number = letterDigitToNumber(k[j]);
          }

          chunktotal += number*s;
          s = s * base;
        }
        w[currIndex] = chunktotal;
        currIndex--;
      }
      
      unsigned long long finalResult = 0;
      for(int i = 0; i < 5; i++){
        finalResult += w[i] * rValues[i];
      }

      return finalResult;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it

      if(std::isdigit(letter) == true){
        return letter - '0' + 26;
      } else {
        letter = std::tolower(letter);
        return letter - 'a';
      }

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
