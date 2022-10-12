/*
Auther: John Blue
Time: 2022/10
Platform: ATOM with MinGw and g++compiler
Object: Balanced Binary Search Tree

Version 1: BST as Node
Version 2: BST as controller to Node
Version 3(*): BST as controller to Node AND new way to balance after deletion

Why balanced binary tree?
To solved worst case of traditional BST when the height is too tall

Balanced binary tree: 2-3 tree
which allow 2 keys and 3 kids at a time
every insert in the end node become 2 keys
if 3 keys happends, dottom up the tree untill the tree is 2-3 tree

Balanced binary tree: 2-3-4 tree
which allow 3 keys and 4 kids at a time
could be more efficient, but hard to construct

Red black tree?
One of the ways to represnt 2-3-4 tree by bibary tree
Red black tree have 2-3 tree or 2-3-4 tree

Left Lean Red Black Tree*(LLRB)?
Left Lean Red Black Tree is more easy to implement
It represents 2-3 tree

... not yet finished
basic strategy: maintain 1-1 correspondence with 2-3 tree
*/

#include <iostream> // i/o
#include <stdlib.h> // include rand function
#include <time.h>   // time function

// Method: Left Lean Red Black Binary Search Tree
// left < root < right
//
// on average
// put close to 1 log N
// get close to 1 log N
// gaurantee
// put 2 log N
// get 2 log N

class BST;

class B_Node {
private:
  // content
  int key;
  int data;
  B_Node* left;
  B_Node* right;
  bool color;// true / false : red / black
  // operator
  B_Node& operator=(const B_Node& copy);

public:
  // constructor
  //B_Node(): key(- 1), data(0), left(0), right(0) {}
  B_Node(int k, int d): key(k), data(d), left(0), right(0), color(true) {}
  B_Node(const B_Node& copy);
  ~B_Node();
  // function
  int get_key() const { return key; }
  int get_data() const { return data; }
  B_Node* get_left() const { return left; }
  B_Node* get_right() const { return right; }
  //bool isRed() const { return color; }
  // friend
  friend BST;
};

class BST {
private:
  // root
  B_Node* root;
  // operator
  BST& operator=(const BST& copy);
  // function
  void print_loop(B_Node* current);// for print_v2

  B_Node* put(B_Node* h, int ky, int dt);
  B_Node* putBalanced(B_Node* h)
    
  B_Node* Del_loop(B_Node* current, int ky);
  B_Node* delBalanced(B_Node* h);
  B_Node* Del_Min(B_Node* h);
  // function
  B_Node* RotateLeft(B_Node* h);
  B_Node* RotateRight(B_Node* h);
  void FlipColor(B_Node* h);

public:
  // constructor
  BST(): root(0) {}
  BST(const BST& copy);
  ~BST();

  // function
  void print();
  // function
  int get(int ky);
  int MinK();
  int MaxK();
  //int floor(int ky);
  //int ceil(int ky);
  //
  bool isRed(B_Node* node) const {
    if (node == 0) return false;
    return node->color;
  }
  bool isLRBT();
  bool isBST(B_Node* node);
  bool isBalanced(B_Node* node);
  int blackLen(B_Node* node);
  bool is23(B_Node* node);
  //
  void put(int ky, int dt);
  void Del(int ky);
};

B_Node::B_Node(const B_Node& copy) {
  // copy data
  key = copy.key;
  data = copy.data;
  left = 0;
  right = 0;
  color = copy.color;
  // copy pt
  if (copy.left != 0) {
    left = new B_Node(*copy.left);
  }
  if (copy.right != 0) {
    right = new B_Node(*copy.right);
  }
}

B_Node::~B_Node() {
  // delete data
  key = 0;
  data = 0;
  color = false;
  // delete pt
  if (left != 0) {
    delete left;
  }
  if (right != 0) {
    delete right;
  }
}

BST::BST(const BST& copy): root(0) {
  // check
  if (copy.root == 0) {
    return;
  }
  // copy
  root = new B_Node(*copy.root);
}

BST::~BST() {
  delete root;

  // another way?
  //https://stackoverflow.com/questions/34170164/destructor-for-binary-search-tree
  // use while ? @@; had better not
  /*
  while (root != 0) {
    while (current->left != 0) {
      while (current->right != 0) {
        break;
      }
    }
  }
  */
}

void BST::print_loop(B_Node* current) {
  // middle
  if (current->color) {
    std::cout << "key(red)" << current->key << ": " << current->data << "\n";
  }
  else {
    std::cout << "key(black)" << current->key << ": " << current->data << "\n";
  }
  // left
  if (current->left != 0) {
    print_loop(current->left);
  }
  // right
  if (current->right != 0) {
    print_loop(current->right);
  }
}

void BST::print() {
  // check
  if (root == 0) {
    std::cout << "empty\n";
    return;
  }
  // print
  print_loop(root);
}

int BST::MinK() {
  B_Node* current = root;
  while(current->left != 0) {
    current = current->left;
  }
  return current->data;
}

int BST::MaxK() {
  B_Node* current = root;
  while(current->right != 0) {
    current = current->right;
  }
  return current->data;
}

//

int BST::get(int ky) {
  B_Node* current = root;
  while (current != 0) {
    if (ky < current->key) {
      current = current->left;
    }
    else if (ky > current->key) {
      current = current->right;
    }
    else if (ky == current->key) {
      return current->data;
    }
  }
  return - 1;
}

//

B_Node* BST::RotateLeft(B_Node* h) {
  // check
  if (h->right == 0) {
    return h;
  }
  // rotate
  B_Node* x = h->right;
  h->right = x->left;
  x->left = h;
  x->color = h->color;
  h->color = true;
  return x;
}

B_Node* BST::RotateRight(B_Node* h) {
  // check
  if (h->left == 0) {
    return h;
  }
  // rotate
  B_Node* x = h->left;
  h->left = x->right;
  x->right = h;
  x->color = h->color;
  h->color = true;
  return x;
}

void BST::FlipColor(B_Node* h) {
  // check
  if (!isRed(h->left) || !isRed(h->right)) {
    return;
  }
  // flip
  h->color = false;
  h->left->color = false;
  h->right->color = false;
}

//
// LLRB should be:
// has only left lean red link
// has no side by side red link
//
// the following condition is in the end node
// (1)
//     Node(red)
// Left(null) Right(null)
//
// (2)
//     Node(black)
// Node(red) Right(null)
//
// (3)
//     Node(black)
// Left(null) Right(null)
//
// (4) this one do not exist in the end node
//     Node(black)
// Left(black) Right(black)

bool RBT::isLRBT() {
 if (this->root == 0) return true;
 
 this->root->color = false;
 if (this->root->color) return false;
 
 /* RBT is not necessary fully balanced !!!
 //https://stackoverflow.com/questions/28531044/is-red-black-tree-balanced
 */
 return isBST(this->root) && is23(this->root) && isBalanced(this->root);
 
 return isBST(this->root) && is23(this->root);
}

bool RBT::isBST(B_Node* node) {
    if (node == 0) return true;

    if (node->left != NULL && node->left->data > node->data) return false;

    if (node->right != NULL && node->data > node->right->data) return false;

    return isBST(node->left) && isBST(node->right);
}

bool RBT::isBalanced(B_Node* node) {
        if (node == 0) return true;
        
        if (abs(blackLen(node->left) - blackLen(node->right)) > 1) return false;
        
        return isBalanced(node->left) && isBalanced(node->right);
}

int RBT::blackLen(B_Node* node) {
    if (node == 0) return 0;
    
    if (isRed(node)) return max(blackLen(node->left), blackLen(node->right));
    else return max(blackLen(node->left), blackLen(node->right)) + 1;
}

bool RBT::is23(B_Node* node) {
    if (node == 0) return true;

    if (isRed(node->right)) return false;

    if (node != root && isRed(node) && isRed(node->left)) return false;
    
    if (node->left == 0 && node->right != 0) return false;

    return is23(node->left) && is23(node->right);
}

//

void BST::put(int ky, int dt) {
  // first?
  if (root == 0) {
    root = new B_Node(ky, dt);
    return;
  }
  // insert
  root = put(root, ky, dt);
}
// insert the key-value pair in the subtree rooted at h
B_Node* BST::put(B_Node* h, int ky, int dt) {
    // recursive
  
    if (h == 0) {
      return new B_Node(ky, dt);
    }

    if (ky < h->key) {
      h->left  = put(h->left,  ky, dt);
    }
    else if (ky > h->key) {
      h->right = put(h->right, ky, dt);
    }
    else {
      h->data = dt;
    }

    // fix-up any right-leaning links

    h = putBalanced(h);

    return h;
}

B_Node* RBT::putBalanced(B_Node* h) {
    // fix-up any right-leaning links

    if (!isRed(h->left) && isRed(h->right)) {
      h = RotateLeft(h);
    }
    if (isRed(h->left)) {
      if (isRed(h->left->left)) {
        h = RotateRight(h);
      }
    }
    if (isRed(h->left) && isRed(h->right)) {
      FlipColor(h);
    }
    
    return h;
}

//

void RBT::Del(int ky) {
  // check
  if (root == 0) {
    std::cout << "empty\n";
    return;
  }
  // from root
  root = Del_loop(ky, root);
}

B_Node* RBT::Del_loop(B_Node* current, int ky) {
  if (current == 0) {
    return 0;
  }
  else if (ky < current->key) {
    current->left = Del_loop(current->left, ky);
  }
  else if (ky > current->key) {
    current->right = Del_loop(current->right, ky);
  }
  // ky == current->key
  else if (ky == current->key) {	    
	    // 
	    if (current->right == 0) return current->left;
      if (current->left  == 0) return current->right;

	    //
      B_Node* tmp = current;
	    //
	    current = tmp->right
      while (current->left) current = current->left;
	    //
      current->right = Del_Min(tmp->right);
      current->left = tmp->left;
      //
      current = delBalanced(current);// balanced
	    //
	    return current;
    }
  }
}

B_Node* RBT::Del_Min(B_Node* h) {
  if h->left == 0 return Del_loop(h, h->key);
  h->left = Del_Min(h->left);
  h = delBalanced(h);
  return h;
}

B_Node* RBT::delBalanced(B_Node* h) {
    if (h->left != 0 && h->right == 0) h->left->color = true;

    if (h->left == 0 && h->right != 0) {
      h = RotateLeft(h);
      
      // rotate, then have to check left
      if (h->left) h->left = delBalanced(h->left);
    }
    if (isRed(h->left)) {
      if (isRed(h->left->left)) {
        h = RotateRight(h);
        
        // rotate, then have to check right
        if (h->right) h->right = delBalanced(h->right);
      }
    }
    if (isRed(h->left) && isRed(h->right)) {
      FlipColor(h);
    }
    
    return h;
}



int main()
{
  //
  //                        8(20)
  //           4(10)                     12(0)
  //     2(80)       6(70)        10(90)         14(100)
  //                          9(110) 11(120) 13(130) 15(140)
  //
  // order of key when print: 8, 4, 2, 6, 12, 10, 9, 11, 14, 13, 15
  //
  int dt[15] = {12, 4, 8, 6, 6, 6, 6, 6, 2, 10, 14, 9, 11, 13, 15};
  BST bt;
  // put
  for (int i = 0; i < 9; i++) {
    bt.put(dt[i], i * 10);
  }
  std::cout << "  BST(0 ~ 8):\n";
  bt.print();
  std::cout << "\n";
  for (int i = 9; i < 15; i++) {
    bt.put(dt[i], i * 10);
  }
  std::cout << "  BST(0 ~ 15):\n";
  bt.print();
  std::cout << "\n";
  // get
  std::cout << "get key(8):" << bt.get(8) << "\n";
  std::cout << "get key(9):" << bt.get(9) << "\n\n";
  // max key vale
  std::cout << "Max Key:" << bt.MaxK() << "\n\n";
  //
  // delete
  //                        8(20)
  //           4(10)                     12(0)*
  //     2(80)*       6(70)*        10(90)         14(100)
  //                          9(110) 11(120) 13(130) 15(140)
  //
  // then
  //                        8(20)
  //           6(70)                     13(130)
  //                                10(90)         15(140)
  //                          9(110) 11(120) 14(100)
  //
  // order of key when print: 8, 4, 13, 10, 9, 11, 15, 14
  //
  std::cout << "Del(2):\n";
  bt.Del(2);
  bt.print();
  std::cout << "\n";
  //
  std::cout << "Del(6):\n";
  bt.Del(6);
  bt.print();
  std::cout << "\n";
  //
  std::cout << "Del(12):\n";
  bt.Del(12);
  bt.print();
  std::cout << "\n";
  // copy
  std::cout << "Copy:\n";
  BST cp(bt);
  cp.print();
  std::cout << "\n";
}
