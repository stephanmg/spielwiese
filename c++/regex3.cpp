#include <iostream>
#include <regex>
#include <string>
 
int main()
{
std::smatch OuMatches;
std::string myCertSubject = "O=\"My Company, Incorporated\", OU=Technician Level - A3, OU=Access Level - 1, CN=\"Name, My\", E=namem@company.com";
myCertSubject = "sectionWpt3daddWWpt3daddWWWpt3daddsection2Wpt3dadd";
std::regex subjectRx("OU=[^,;]+", std::regex_constants::icase);
subjectRx = "^section((?:W*)pt3dadd(?:W*))";

std::regex_iterator<std::string::iterator> it (myCertSubject.begin(), myCertSubject.end(), subjectRx);
std::regex_iterator<std::string::iterator> end;

while (it != end)
{
    std::cout << it->str() << std::endl;
    ++it;
}
}