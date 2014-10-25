#include <iostream>
#include <regex>
#include <string>
 
int main()
{
    std::string target("baaabbyccccaabb");
    std::smatch sm;
 
    std::regex re1("a(a)*b");
    std::regex_search(target, sm, re1);
    std::cout << "entire match: " << sm[0] << '\n'
              << "submatch #1: " << sm[1] << '\n';
 
// /\s*\Q$section\E\s?\{\s?(?:pt3dclear\(\)|(?=pt3dadd\([^(]*))(?=\)?.)(.*?)\}/sg)
    target = "YYYYsectionYYYYpt3daddNNNNpt3daddNNNNpt3daddNNNNZZZZ";
   target = "pt3daddNNNpt3daddNNN";
    std::regex re3("(pt3dadd(?:N*))*");
 //   std::regex re2("(Y*section(pt3dadd)X*)*");
   target = "sectionWpt3daddWWpt3daddWWWpt3daddWWWsection2Wpt3dadd";
   std::regex re4("^section((?:W+)pt3dadd)*");
    std::regex_search(target, sm, re4);
    std::cout << "entire match: " << sm[0] << '\n'
              << "submatch #1: " << sm[1] << '\n'
              << "submatch #2: " << sm[2] << '\n';
 
}
