#include <iostream>
#include <regex>
#include <fstream>
#include <string>
#include <cerrno>
#include <unordered_map>
#include <sstream>

std::string get_file_contents(const char *filename)
{
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in)
  {
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return(contents);
  }
  throw(errno);
}

int main() {
   std::unordered_map<std::string, std::vector<std::string> >all_sections_raw_points;
//  push \@{$all_sections_raw_points{$section}}, "$1 $2 $3" i
// if (@strings = ($string =~ /\s*\Q$section\E\s?\{\s?(?:pt3dclear\(\)|(?=pt3dadd\([^(]*))(?=\)?.)(.*?)\}/sg)) {$
//

 //const std::regex pattern("axon(W*pt(?:3|4)daddN*)*");
  const std::regex pattern("apic[^]*\\}");
  std::string text = "XXaxonWWWpt3daddNNNWWWpt3daddNNNdendWWWpt3daddNNNWWWpt3daddNNNaxonWWWpt3daddNNNWWWpt4daddNNN"; // replace with real whitespace... and pattern match
   text = get_file_contents("foo.hoc");
   const std::sregex_token_iterator end;
   for (std::sregex_token_iterator i(text.cbegin(), text.cend(), pattern, 0); i != end; ++i) { // emulates perls global match operator /g
      std::cout << *i << std::endl;
      //  print "$1, $2, $3 \n" if m/\s*pt3dadd\(\s*([-+]?\d+\.\d+)\s*,\s*([-+]?\d+\.\d+)\s*,\s*([-+]?\d+\.\d+).*/;$
 //     const std::regex pattern2("(pt)(?:3|4)(dadd)");
   const std::regex pattern2("(pt3dadd\\(.*[^]\\))");
      std::string text2 = *i;

      // single string, emulate perls groups $1, ... $n
      for (std::sregex_token_iterator j(text2.cbegin(), text2.cend(), pattern2, 0); j != end; ++j) { 
         //  print "$1, $2, $3 \n" if m/\s*pt3dadd\(\s*([-+]?\d+\.\d+)\s*,\s*([-+]?\d+\.\d+)\s*,\s*([-+]?\d+\.\d+).*/;$
         //std::cout << *j << std::endl;
         const std::regex pattern3("\\s*\\(([-+]?\\d+\\.\\d+)\\s*,\\s*([-+]?\\d+\\.\\d+),\\s*([-+]?\\d+\\.\\d+),\\s*(\\d+\\.\\d+)\\)"); 
         std::string text3 = *j;
         std::string x, y, z, diam;
         for (std::sregex_token_iterator k(text3.begin(), text3.cend(), pattern3, 1); k != end; ++k) {
            std::cout << "Match pt3dadd x: " << *k << std::endl;
            x = *k;
         }

         for (std::sregex_token_iterator k(text3.begin(), text3.cend(), pattern3, 2); k != end; ++k) {
            std::cout << "Match pt3dadd y: " << *k << std::endl;
            y = *k;
         }

         for (std::sregex_token_iterator k(text3.begin(), text3.cend(), pattern3, 3); k != end; ++k) {
            std::cout << "Match pt3dadd z: " << *k << std::endl;
            z = *k;
         }

         for (std::sregex_token_iterator k(text3.begin(), text3.cend(), pattern3, 4); k != end; ++k) {
            std::cout << "Match pt3dadd diam: " << *k << std::endl;
            diam = *k;
         }
         
         std::stringstream ss;
         ss << x << " ";
         ss << y << " ";
         ss << z << " ";
         ss << diam;

         if (all_sections_raw_points.find("apic") != all_sections_raw_points.cend()) {
            all_sections_raw_points.at("apic").push_back(ss.str());
            std::cout << "second" << std::endl;
         } else {
            all_sections_raw_points.insert(std::make_pair<std::string,std::vector<std::string> >("apic",std::vector<std::string>()));
            std::cout << "first" << std::endl;
         }
//  push \@{$all_sections_raw_points{$section}}, "$1 $2 $3" i

         
      }

 /*     for (std::sregex_token_iterator j(text2.cbegin(), text2.cend(), pattern2, 1); j != end; ++j) { 
         std::cout << *j << std::endl;
      }

      for (std::sregex_token_iterator j(text2.cbegin(), text2.cend(), pattern2, 2); j != end; ++j) { 
         std::cout << *j << std::endl;
      }*/
   }

   return 0;
}
