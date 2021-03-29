#include <iterator>

template<typename T>
class List {
private:
  struct Node {
    Node* prev_;
    Node* next_;
    Node() {
        prev_ = next_ = this;
    }

    Node(Node* prev, Node* next) : prev_(prev), next_(next) {}

    virtual ~Node() {}
  };

  struct NodeWithValue : public Node {
    T value_;
    NodeWithValue(const T& value, Node* prev = nullptr, Node* next = nullptr) :
        Node(prev, next), value_(value) {
    }

    NodeWithValue(T && value, Node* prev = nullptr, Node* next = nullptr) :
        Node(prev, next), value_(std::move(value)) {
    }
  };
  size_t size_;
  Node* fictive_element_;
  void swap(List& other) {
      std::swap(fictive_element_, other.fictive_element_);
      std::swap(size_, other.size_);
  }
  static void unlink(Node* node) {
      node->prev_->next_ = node->next_;
      node->next_->prev_ = node->prev_;
      node->next_ = node->prev_ = nullptr;
      delete node;
  }

  static void link_after(Node* node, Node* place) {
      auto after_place = place->next_;
      place->next_ = node;
      node->next_ = after_place;
      node->prev_ = place;
      after_place->prev_ = node;
  }

public:
  class Iterator : public std::iterator<std::random_access_iterator_tag, T> {
  private:
    Node* ptr_;

  public:
    Iterator(Node* ptr) : ptr_(ptr) {}
    Iterator(Iterator&& rhs) : ptr_(std::move(rhs.ptr_)) {}
    Iterator(const Iterator& rhs) : ptr_(rhs.ptr_) {}
    Iterator operator++(int) {
        Iterator old_v(*this);
        ptr_ = ptr_->next_;
        return old_v;
    }
    Iterator& operator++() {
        ptr_ = ptr_->next_;
        return *this;
    }
    Iterator operator--(int) {
        Iterator old_v(*this);
        ptr_ = ptr_->prev_;
        return old_v;
    }

    Iterator& operator--() {
        ptr_ = ptr_->prev_;
        return *this;
    }

    T& operator*() const {
        return (static_cast<NodeWithValue*>(ptr_))->value_;
    }

    bool operator==(const Iterator& rhs) const {
        return ptr_ == rhs.ptr_;
    }

    bool operator!=(const Iterator& rhs) const {
        return !(*this == rhs);
    }
  };
  List() : size_(), fictive_element_(new Node) {}
  List(const List& rhs) : size_(rhs.size_) {
      fictive_element_ = new Node();
      for (const T& elem : rhs) {
          push_back(std::move(elem));
      }
      size_ = rhs.size();
  }
  List(List&& other) : size_(other.size_), fictive_element_(other.fictive_element_) {
      other.fictive_element_ = nullptr;
      other.size_ = 0;
  }
  ~List() {
      auto current = fictive_element_->next_;
      while (current != fictive_element_) {
          auto next = current->next_;
          delete current;
          current = next;
      }
      size_ = 0;
      delete fictive_element_;
  }

  List& operator=(const List& other) {
      List temp(other);
      swap(temp);
      return *this;
  }

  List& operator=(List&& other) {
      List temp(std::move(other));
      swap(temp);
      return *this;
  }
  size_t size() const {
      return size_;
  }
  void push_back(const T& value) {
      Node* node = new NodeWithValue(value);
      link_after(node, fictive_element_->prev_);
      ++size_;
  }
  void push_front(const T& value) {
      Node* node = new NodeWithValue(value);
      link_after(node, fictive_element_);
      ++size_;
  }
  void pop_back() {
      unlink(fictive_element_->prev_);
      --size_;
  }
  void pop_front() {
      unlink(fictive_element_->next_);
      --size_;
  }
  void push_back(T&& other) {
      Node* node = new NodeWithValue(std::move(other));
      link_after(node, fictive_element_->prev_);
      ++size_;
  }
  void push_front(T&& other) {
      Node* node = new NodeWithValue(std::move(other));
      link_after(node, fictive_element_);
      ++size_;
  }
  Iterator begin() const {
      return Iterator(fictive_element_->next_);
  }
  Iterator end() const {
      return Iterator(fictive_element_);
  }
};
