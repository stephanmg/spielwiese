#include <iostream>
#include <regex>
#include <string>

int main() {
// if (@strings = ($string =~ /\s*\Q$section\E\s?\{\s?(?:pt3dclear\(\)|(?=pt3dadd\([^(]*))(?=\)?.)(.*?)\}/sg)) {$
 const std::regex pattern("axon(W*pt(?:3|4)daddN*)*");
   std::string text = "XXaxonWWWpt3daddNNNWWWpt3daddNNNdendWWWpt3daddNNNWWWpt3daddNNNaxonWWWpt3daddNNNWWWpt4daddNNN"; // replace with real whitespace... and pattern match
   const std::sregex_token_iterator end;
   for (std::sregex_token_iterator i(text.cbegin(), text.cend(), pattern, 0); i != end; ++i) { // emulates perls global match operator /g
      std::cout << *i << std::endl;
      //  print "$1, $2, $3 \n" if m/\s*pt3dadd\(\s*([-+]?\d+\.\d+)\s*,\s*([-+]?\d+\.\d+)\s*,\s*([-+]?\d+\.\d+).*/;$
      const std::regex pattern2("(pt)(?:3|4)(dadd)");
      std::string text2 = *i;

      // single string, emulate perls groups $1, ... $n
      for (std::sregex_token_iterator j(text2.cbegin(), text2.cend(), pattern2, 0); j != end; ++j) { 
         std::cout << *j << std::endl;
      }

      for (std::sregex_token_iterator j(text2.cbegin(), text2.cend(), pattern2, 1); j != end; ++j) { 
         std::cout << *j << std::endl;
      }

      for (std::sregex_token_iterator j(text2.cbegin(), text2.cend(), pattern2, 2); j != end; ++j) { 
         std::cout << *j << std::endl;
      }
   }

   return 0;
}
