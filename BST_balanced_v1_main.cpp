/*
Auther: John Blue
Time: 2022/1
Platform: ATOM with MinGw and g++compiler
Object: Balanced Binary Search Tree

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
  B_Node(int k, int d): key(k), data(d), left(0), right(0), color(false) {}
  B_Node(const B_Node& copy);
  ~B_Node();
  // function
  int get_key() const { return key; }
  int get_data() const { return data; }
  B_Node* get_left() const { return left; }
  B_Node* get_right() const { return right; }
  bool isRed() const { return color; }
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
  void Del_loop(int ky, B_Node** ad_p_p_current, B_Node** ad_p_current, B_Node* p_current, B_Node* current);
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
  void put(int ky, int dt);
  int get(int ky);
  int MinK();
  int MaxK();
  //int floor(int ky);
  //int ceil(int ky);
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



B_Node* BST::RotateLeft(B_Node* h) {
  // check
  //if (!h->right->isRed()) {
    //return h;
  //}
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
  //if (!h->left->isRed()) {
    //return h;
  //}
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
  if (h->isRed() || !h->left->isRed() || !h->right->isRed()) {
    return;
  }
  // flip
  h->color = false;
  h->left->color = false;
  h->right->color = false;
}

// Method 1
// int the end node, there have mainly two cases
// case 1, insert in 2 key:
// case 2, insert in 2 key:
//
// (insert v)
// insert in left:
// case 1:
//     Node(black)
// Left(insert) Right(null)
//
// case 2 v smaller:
//    Node(red)
//Left(insert) Right(null)
//
// insert in Right:
// case 1:
//     Node(black)
// Left(null) Right(insert)
//
// case 2 v between:
//     Node(red)
// Left(null) Right(insert)
//
// case 2 v larger
//     Node(black)
// Left(red) Right(insert)
//
// Method 2
// in fact, we just have to consideer whether it is LLRB?
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
//
// LLRB right after insert red link would have:
// after insertion, it may violate the rule:
// (11)
//     Node(red)
// Left(red) Right(null)
//
// (12)
//     Node(red)
// Left(null) Right(red)
//
// (21)
//     Node(black)
// Node(red) Right(red)
//
// (31)
//     Node(black)
// Node(red) Right(null)
//
// (32)
//     Node(black)
// Node(null) Right(red)
//
// then what is violated and what to do:
//
// (11)
//     Node(red)
// Left(red) Right(null)
// then do
// operation 1
// break
//
// (12)
//     Node(red)
// Left(null) Right(red)
// then do
// operation 2
// continue ... will meet operation 1
//
// (21)
//     Node(black)
// Left(red) Right(red)
// operation 3
// break
//
// (32)
//     Node(black)
// Left(null) Right(red)
// operation 4
// break
void BST::put(int ky, int dt) {
  // first?
  if (root == 0) {
    root = new B_Node(ky, dt);
    return;
  }
  // insert
  B_Node* current = root;
  B_Node* p_current = 0;
  B_Node** ad_p_current = &root;
  B_Node** ad_p_p_current = 0;
  // find and add new node
  while(1) {
    // <
    if (ky < current->key) {
      if (current->left == 0) {
        // new Node
        current->left = new B_Node(ky, dt);
        current->left->color = true;
        break;
      }
      else {
        ad_p_p_current = ad_p_current;
        ad_p_current = &(current->left);
        p_current = current;
        current = current->left;
      }
    }
    // >
    else if (ky > current->key) {
      if (current->right == 0) {
        current->right = new B_Node(ky, dt);
        current->right->color = true;
        break;
      }
      else {
        ad_p_p_current = ad_p_current;
        ad_p_current = &(current->right);
        p_current = current;
        current = current->right;
      }
    }
    // ==
    else if (ky == current->key) {
      current->data = dt;
      return;
    }
  }
  // rotate or flip until it is a LLRB
  if (current->isRed()) {// node link is red
    if (current->right != 0) {// case (12)
      // operation 2
      current = RotateLeft(current);
      *ad_p_current = current;
    }
    // !!! operation 1 is after operation 2 for case (12)
    if (current->left != 0) {// case (11)
      p_current = RotateRight(p_current);
      FlipColor(p_current);
      *ad_p_p_current = p_current;
    }
  }
  else {// node link is black
    if (current->left != 0 && current->right != 0) {// case (21)
      // operation 3
      FlipColor(current);
    }
    else if (current->left == 0) {// case (32)
      // operation 4
      current = RotateLeft(current);
      *ad_p_current = current;
    }
  }
}



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

// case of deletion:
// (1) no kid
// (2) one kid
// (3) two kids
//
// LLRB should be:
// has only left lean red link
// has no side by side red link
//
// (1)
//     Node(red)
// Left(null) Right(null)
//
// (2)
//     Node(black)
// Node(null) Right(null)
//
// (3)
//     Node(black)
// Left(red) Right(null)
//
// (4)
//     Node(black)
// Left(black) Right(black)
//
// the following condition is the posibility through the whole tree
// case of deletion with color
// (1)
//     Node(red)*
// Left(null) Right(null)
//
// (21)
//           Parent(black)
// Node(black)           Node(black)*
//     ...          Node(null) Right(null)
//
// (22)
//                Parent(black)
//     Node(black)*      Node(black)
// Node(null) Right(null)           ...
//
// (3)
//                Parent(black)
//     Node(black)*      Node(black)
// Left(red) Right(null)           ...
//
// (41)
//        Node(black)*
// Left(black)     Right(black)
//     ...      ...            ...
// (42)
//        Node(black)*
// Left(black)     Right(black)
//     ...    Left(not null)   ...
//
void BST::Del_loop(int ky, B_Node** ad_p_p_current, B_Node** ad_p_current, B_Node* p_current, B_Node* current) {
  //B_Node** ad_p_current; address of parent left or right pointer
  //
  // initial
  if (ad_p_current == 0) {
    ad_p_current = &root;
  }
  // deleting
  while (current != 0) {
    // search
    if (ky < current->key) {
      ad_p_p_current = ad_p_current;
      ad_p_current = &(current->left);
      p_current = current;
      current = current->left;
    }
    else if (ky > current->key) {
      ad_p_p_current = ad_p_current;
      ad_p_current = &(current->right);
      p_current = current;
      current = current->right;
    }
    // delete
    else if (ky == current->key) {
      if (current->left == 0 && current->right == 0) {
        // relink
        *ad_p_current = 0;// !!! very important; cut the link
        // delete
        delete current;
        // # after delete
        // case (1) nothing
        // case (21)
        // case (22)
        if (p_current->right != 0) {
          // rotate parent
          p_current = RotateLeft(p_current);
          *ad_p_p_current = p_current;
        }
        if (p_current->left != 0 && !p_current->left->isRed()) {
          p_current->left->color = true;
          if (p_current->left->left != 0 && p_current->left->left->isRed()) {
            p_current = RotateRight(p_current->left);
            *ad_p_p_current = p_current;
            FlipColor(p_current);
          }
        }
      }
      // #
      // case (3)
      else if (current->left != 0 && current->right == 0) {
        // relink
        *ad_p_current = current->left;
        current->left->color = false;
        // delete
        current->left = 0;// !!! prevent further delete
        delete current;
        //return;
      }
      else {
        // #
        // case (42)
        if (current->right->left != 0) {
          // move
          current->key = current->right->left->key;
          current->data = current->right->left->data;
          // delete (key, address of parent left or right)
          Del_loop(current->right->left->key, &(current->right), &(current->right->left), current->right, current->right->left);
        }
        // #
        // case (41)
        else if (current->right != 0) {
          // move
          current->key = current->right->key;
          current->data = current->right->data;
          // delete (key, address of parent left or right)
          Del_loop(current->right->key, ad_p_current, &(current->right), current, current->right);
        }
        //return;
      }
      return;
    }
  }
  // not found
  std::cout << "no such key\n";
}

void BST::Del(int ky) {
  // check
  if (root == 0) {
    std::cout << "empty\n";
    return;
  }
  // from root
  Del_loop(ky, 0, 0, 0, root);
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
