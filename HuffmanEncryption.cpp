#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <list>

class Node {
public:
  int a;
  char c;
  Node* left, * right;
  Node() {
      left = right = nullptr;
  }
  Node(Node* l, Node* r) {
      left = l;
      right = r;
      a = l->a + r->a;
  }
};

struct Compare {
  bool operator()(const Node* l, const Node* r) const { return l->a < r->a; }
};
std::vector<bool> code;
std::map<char, std::vector<bool>> table;

void BuildTable(Node *root) {
    if (root->right != nullptr) {
        code.push_back(1);
        BuildTable(root->right);
    }
    if (root->left != nullptr) {
        code.push_back(0);
        BuildTable(root->left);
    }
    if (root->left == nullptr && root->right == nullptr) {
        table[root->c] = code;
    }
    code.pop_back();
}

int main() {
    std::ifstream f("имя файла");
    setlocale(LC_ALL,"Russian");
    std::string s = "it is my striiing!";
    std::map<char, int> m;
    std::list<Node*> t;
    for (auto& e : s) {
        m[e]++;
    }
    for (auto i = m.begin(); i != m.end(); ++i) {
        Node* p = new Node;
        p->c = i->first;
        p->a = i->second;
        t.push_back(p);
    }
//    Создание дерева
    while (t.size() != 1) {
        t.sort(Compare());
        Node *lson = t.front();
        t.pop_front();
        Node *rson = t.front();
        t.pop_front();
        Node *par = new Node(lson, rson);
        t.push_back(par);
    }
    Node * root = t.front();
    BuildTable(root);

    std::ofstream g("имя выходного файла");
    int count = 0;
    char buf = 0;
    while (!f.eof()) {
        char c;
        f >> c;
        std::vector<bool> x = table[c]; // получаем последовательность из 0 и 1 для данной буквы
        for (int i = 0; i < (int)x.size(); ++i) {
            buf = buf | x[i] << (7 - count);
            ++count;
            if (count == 8) {
                count = 0;
                g << buf;
                buf = 0;
            }
        }
    }
    g.close();
    f.close();

    std::ifstream F("имя считываемого файла");
    Node *p = root;
    count = 0; char byte;
    byte = F.get();
    while (!F.get()) {
        bool b = byte & (1 << (7 - count));
        if (b) {
            p = p->right;
        } else {
            p = p->left;
        }
        if (p->left == nullptr && p->right == nullptr) {
            std::cout << p->c;
            p=root;
        }
        ++count;
        if (count == 8) {
            count = 0;
            byte = F.get();
        }
    }
    F.close();
    return 0;
}
