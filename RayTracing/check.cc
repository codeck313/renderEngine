// #include "constant_project.h"
// #include <iostream>
// int main() { std::cout << random_double(0, 512); }
// #include <iostream>
// int main() {
// #pragma omp parallel
//   { std::cout << "hello world \n"; }
//   return 0;
// }
// 214 232 255

#include <iostream>
#include <vector>

void print(std::vector<int> const &a) {
  std::cout << "The vector elements are : ";

  for (int i = 0; i < a.size(); i++)
    std::cout << a.at(i) << ' ';
}

int main() {
  std::vector<int> a = {2, 4, 3, 5, 6};
  print(a);
  return 0;
}
//-fopenmp
