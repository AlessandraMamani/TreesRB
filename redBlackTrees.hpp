#ifndef REDBLACKTREE_HPP
#define REDBLACKTREE_HPP

enum Color {RED, BLACK};

struct Node {
  int key;
  Color color;
  Node *left,
       *right,
       *parend;
  Node(int value = 0) {
    key = value;
    color = RED;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }
};

class RedBackTree {
  private:
    Node* root;
    Node* NIL;

    void leftRotate(Node* _);
    void rightRotate(Node* _);
    void insertFixUp(Node* _);
    void inordenHelper(Node* _) const;
    void clearHelper(Node* _);

  public:
    RedBlackTree();
    ~RedBlackTree();
    
    Node* getRoot();

    void insert(int key);
    void display() const;
}

#endif
