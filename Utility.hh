#ifndef GUARD_UTILITY_REGEX
#define GUARD_UTILITY_REGEX

#include <iterator>
#include <iostream>
#include <cstdlib>
#include <utility>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

namespace utility {

   template<typename T> std::string to_string(const T& n) {
      std::ostringstream stm;
      stm << n;
      return stm.str();
   }

   // 2-4   -> <2, 4>
   std::pair<int, int> interval(std::string s) {
      // tokenize the string
      int i = s.length() - 1;
      unsigned power = 0;
      int toInt = 0;
      int fromInt = 0;

      while(s.at(i) != '-') {
         toInt += (s.at(i--) - 48) * pow(10, power++);
      }
      power = 0;
      --i;
      while(i != -1) {
         fromInt += (s.at(i--) - 48) * pow(10, power++);
      }
      return std::make_pair(fromInt, toInt);
   }
   // a-d -> [a, b, c, d]  | A-Z  -> [A, B, C, ..., Z]
   std::vector<char> regexChar(std::string s) {
      std::vector<char> tmp;
      int head = s.at(0);
      int tail = s.at(2);

      while(head != tail) {
         tmp.push_back(head++);
      }
      tmp.push_back(head);
      return tmp;
   }
   // 1-4 -> [1,2,3,4]   34-101  -> [34,35,36,...,100,101]
   std::vector<int> regexInt(std::string s) {
      // generate the number from (fromInt) to (toInt)
      std::vector<int> tmp;
      std::pair<int , int> intval(interval(s));
      for(int i = intval.first; i <= intval.second; ++i) {
         tmp.push_back(i);
      }
      return tmp;
   }

   bool checkIfInterval(std::string s) {
      std::pair<int, int> intval(interval(s));
      std::string fromInt = to_string(intval.first);
      std::string toInt = to_string(intval.second);
      std::string::const_iterator fromIt = fromInt.begin();
      std::string::const_iterator toIt = toInt.begin();

      while(fromIt != fromInt.end() && std::isdigit(*fromIt)) ++fromIt;
      while(toIt != toInt.end() && std::isdigit(*toIt)) ++toIt;
      return (!fromInt.empty() && fromIt == fromInt.end()) &&
             (!toInt.empty() && toIt == toInt.end());

   }
} //namespace utility

#endif