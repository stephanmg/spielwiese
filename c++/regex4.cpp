#include <iostream>
#include <regex>
#include <string>

int main() {
 const std::regex pattern("hello ([0-9]+)");
 std::string text = "hello 1, hello 2, hello 17, and done!";
   
          const std::sregex_token_iterator end;
             for (std::sregex_token_iterator i(text.cbegin(), text.cend(), pattern, 1);
                     i != end;
                             ++i)
                                {
                                 
                                      std::cout << *i << std::endl;
                                         }
   
                                            return 0;
                                            }
