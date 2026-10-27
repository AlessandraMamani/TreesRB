#include "RedBlackTrees.hpp"
#include <iostream>

RedBlackTree::RedBlackTree(){
  NIL = new Node();

  NIL->color = BLACK;
  NIL->left = NIL;
  NIL->right = NIL;
  NIL->parent = NIL;

  root = NIL;
}

Node* RedBlackTree::getRoot(){
  return root;
}

RedBlackTree::~RedBlackTree() {
  clearHelper(root);
  delete NIL;
}

void RedBlackTree::clearHelper(Node* root){
  if(root == NIL) return;
  clearHelper(root->left);
  clearHelper(root->right);
  delete root;
}

void RedBlackTree::leftRotate(Node* x){
  Node* y = x->right;
  x->right = y->left;

  if (y->left != NIL) 
      y->left->parent = x;
  
  y->parent = x->parent;

  if (x->parent == NIL)
    root = y;

  else if (x == x->parent->left)
    x->parent->left = y;
  
  else
    x->parent->right = y;

  y->left = x;

  x->parent = y;

}

void RedBlackTree::rightRotate(){
  Node* y = x->left;
  x->left = y->right;
  
  if (x->right != NIL)
    y->right->parent = x;

  y->parent = x->parent;

  if (x->parent == NIL)
    root = y;

  else if (x == x->parent->right)
    x->parent->right = y;

  else
    x->parent->left = y;

  y->right = x;

  x->parent = y;

}

void RedBlackTree::insertFixUp(Node* z){
  while(z->parent->color == RED) {

    if (z->parent == z->parent->parent->left){
      //PART 02  
      Node* y = z->parent->parent->right;
      
      if (y->color == RED){
        z->parent->color = BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;

        z = z->parent->parent;
      }
      
      else{ 
        if (z == z->parent->right){
          z = z->parent;
          leftRotate(z);
        }
      
      z->parent->color = BLACK;
      z->parent->parent->color = RED;

      rightRotate(z->parent->parent);
      
      }
    }

    else {
      //PART 02
      Node* y = z->parent->parent->left;

      if(y->color == RED){
        z->parent->color = BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;

        z = z->parent->parent;
      }

      else{
        if (z == z->parent->left){
          z = z->parent;
          rightRotate(z);
        }
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        
        leftRotate(z->parent->parent);
      }
    }
  }
  root->color = BLACK;
}


void RedBlackTree::insert(int key){
  Node *z = new Node(key);

  z->left = NIL;
  z->right = NIL;
  z->color = RED;

  Node* y = NIL;
  Node* x = root;

  while(x != NIL){
    y = x;
    if (x->key < key)
      x = x->left;
    else
      x = x->right;
  }

  z->parent = y;

  if (y == NIL)
    root = z;

  else if (z->key < y->key)
    x->left = z;
  
  else 
    x->right = z;

  insertFixUp(z);
}

Node* RedBlackTree::minimum(Node* x){
  while(x->left != NIL)
    x = x->left;
  return x;
}
 
void RedBlackTree::transplant(Node* u, Node* v){
  if (u->parent == NIL)
    root = v;
  
  else if (u == u->parent->left)
    u->parent->left = v;
  
  else
    u->parent->right = v;

  v->parent = u->parent;

}

void RedBlackTree::remove(int key){
  Node* z = search(key);

  if (z == NIL)
    return;

  Node* y = z;
  Color yColor = y->color;
  Node* x;

  if(z->left == NIL){
    x = z->right;
    transplant(z, z->right);
  }

  else if (z->right == NIL){
    x = z->left;
    transplant(z, z->left);

  }

  else{
    y = minimum(z->right);
    
    yColor = y->color;
    x = y->right;
    if (y->parent == z)
      x->parent = y;
    else{
      transplant(y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    transplant(z, y);

    y->left = z->left;
    y->left->parent = y;

    y->color = z->color;
  } 
  delete z;
  if (yColor == BLACK)
    deleteFixUp(x);
}

Node* RedBlackTree::search(int key){
  Node* x = root;

  while(x != NIL && x->key != key){
    if (x->key > key)
      x = x->left;
    else 
      x = x->right;
  }
  return x;

}

void RedBlackTree::deleteFixUp(Node+ x){
  while (x != root && x->color == BLACK){
    if (x == x->parent->left){
      Node *w = x->parent->right;
      if (w->color == RED){
        w->color = BLACK;
        w->parent->color = RED;

        leftRotate(x->parent);

        w = x->parent->right;
      }  
      
      if (w->left->color == BLACK && w->right->color == BLACK){
        w->color = RED;
        x = x->parent;
      }
      else{
        if (w->right->color == BLACK){
          w->left->color = BLACK;
          w->color = RED;

          rightRotate(x);

          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->right->color = BLACK;

        leftRotate(x->parent);

        x = root;
      }
    }

    else{
      Node* w = x->parent->left;

      if (w->color == REED){
        w->color = BLACK;
        w->parent->color = RED;

        rightRotate(x->paent);
      }

      if (w->right->color == BLACK && w->left->color == BLACK){
        w->color = RED;
        x = x->parent;
      }
      else{
        if (w->left->color == BLACK){
          w->right->color = BLACK;
          w->color = RED;

          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->left->color = BLACK;
        rightRotate(x->parent);
        x = root;
      }

    }

  }
  x->color = BLACK;
}

void RedBlackTree::inordenHelper(Node* node){
  if (node != NIL){
    inordenHelper(node->left);
    cout << node->key << " ";
    inordenHelper(node->right);
  }
}

void RedBlackTree::inorden() const {
  inordenHelper(root);
  cout << endl;
}

void RedBlackTree::preordenHelper(Node* x){
  if (x != NIL){
    cout << x->key << " ";
    preordenHelper(x->left);
    preordenHelper(x->right);
  }
}

void RedBlackTree::preorden(){
  preordenHelper(root);
  cout << endl;
}

void RedBlackTree::printTree(){
  printHelper(root, 0);
}
