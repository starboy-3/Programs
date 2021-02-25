#include<iostream>
#include<list>

class Vim {
private:
  std::list<char> text;
  std::list<char>::iterator it;

public:
  bool insertion_mode;
  Vim() {
      it = text.begin();
      insertion_mode = false;
  }
  void ApplyCommand(char command) {
      if (!insertion_mode) {
          if (command == 'l') {
              MoveRight();
          } else if (command == 'h') {
              MoveLeft();
          } else if (command == 'i') {
              insertion_mode = true;
          }
          return;
      }
      text.insert(it, command);
  }
  std::string GetText() {
      return {text.begin(), text.end()};
  }
  void MoveRight() {
      if (it != text.end()) {
          ++it;
      }
  }
  void MoveLeft() {
      if (it != text.begin()) {
          --it;
      }
  }
};

int main() {
    Vim vim;
    char symbol;
    while (std::cin.get(symbol)) {
        if (symbol == '<') {
            std::cin.ignore(4);
            vim.insertion_mode = false;
        } else {
            vim.ApplyCommand(symbol);
        }
    }
    std::cout << vim.GetText() << '\n';
}
