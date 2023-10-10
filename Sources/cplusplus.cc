#include <map>
#include <string>
#include <vector>

int main() {
  std::vector<int> marks = { 1, 3, 4, 2, 9 };

  for (auto & value : marks) {
    value -= 1;
  }

  std::map<std::string, int> named_marks = {{ "Pierre", 5 }, { "Paul", 2 }, { "Jacques", 7 }};

  for (auto & [ key, value ] : named_marks) {
    value -= 2;
  }

}
