
/*
Auther: John Blue
Time: 2022/10
Platform: ATOM with MinGw and g++compiler
Object: Binary Search Tree
Version 2: BST as Node
Version 3: BST as controller to Node
Version 4(*): BST as controller to Node AND refine put_loop(...) and Del_loop(...)
*/

#include <iostream> // i/o
#include <stdlib.h> // include rand function
#include <time.h>   // time function

// Method: Binary Search Tree
// left < root < right
//
// on average
// put 1.39 log N
// get 1.39 log N
// gaurantee
// put N
// get N
//
// note:
// sequential search: unsorted linked list
//                    one by one
//     binary search: sorted array
//                    half by half
//                    smaller? |find| larger? | ...

class BST;

class B_Node {
private:
  // content
  int key;
  int data;
  B_Node* left;
  B_Node* right;
  // operator
  B_Node& operator=(const B_Node& copy);

public:
  // constructor
  //B_Node(): key(- 1), data(0), left(0), right(0) {}
  B_Node(int k, int d): key(k), data(d), left(0), right(0) {}
  B_Node(const B_Node& copy);
  ~B_Node();
  // function
  int get_key() const { return key; }
  int get_data() const { return data; }
  B_Node* get_left() const { return left; }
  B_Node* get_right() const { return right; }
  // friend
  friend BST;
};

class BST {
private:
  // root
  B_Node* root;
  // operator
  BST& operator=(const BST& copy);
  

public:
  // constructor
  BST(): root(0) {}
  BST(const BST& copy);
  ~BST();

  // function
  void print();
  void print_loop(B_Node* current);
  
  // function
  
  int get(int ky);
  int MinK();
  int MaxK();
  //int floor(int ky);
  //int ceil(int ky);

  void put(int ky, int dt);
  B_Node* put_loop(B_Node* current, int ky, int dt);
	
  void Del(int ky);
  B_Node* Del_loop(B_Node* current, int ky);
};

B_Node::B_Node(const B_Node& copy) {
  // copy data
  key = copy.key;
  data = copy.data;
  left = 0;
  right = 0;
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
  std::cout << "key" << current->key << ": " << current->data << "\n";
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

void BST::put(int ky, int dt) {
  if (root == 0) {
    root = new B_Node(ky, dt);
    return;
  }
	
  put(root, ky, dt);
}

B_Node* BST::put_loop(B_Node* current, int ky, int dt) {
  // first?
  if (current == 0) {
    return new B_Node(ky, dt);
  }
  // insert
  if (ky < current->key) {
        current->left = put(current->left, ky, dt);
  }
  else if (ky > current->key) {
          current->right = put(current->right, ky, dt);
  }
  else if (ky == current->key) {
      current->data = dt;
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


void BST::Del(int ky) {
  // check
  if (root == 0) {
    std::cout << "empty\n";
    return;
  }
  // from root
  root = Del_loop(ky, root);
}

B_Node* BST::Del_loop(B_Node* current, int ky) {
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
    
// method **
// !!! del_llop2() of v4 is right; v3 is wrong due to "cur = ..." cannot remeber the change
/*
    if (current->left == 0 && current->right == 0) {
        // relink
      return 0;// !!! very important; cut the link
    }
    else {
    
      B_Node** cur = 0;
      if (current->left != 0 && current->right == 0) {
                cur = &(current->left);
                while ((*cur)->right) {
                  cur = &((*cur)->right);
                }
      }
      else {
                cur = &(current->right);
                while((*cur)->left) {
                  cur = &((*cur)->left);
                }
      }
            
      current->key = (*cur)->key;
      current->data = (*cur)->data;
      *cur = Del_loop2((*cur)->key, *cur);
      return current;
*/
	
// method *
// a more straight forward alogorithm
	    /*
            if (current->right == 0) return current->left;
            if (current->left  == 0) return current->right;

            B_Node* tmp = current;
            current = Min(tmp->right);
            current->right = deleteMin(tmp->right);
            current->left = tmp->left;
	    return current;
	    */
	    
	    // method * expanding
	    if (current->right == 0) return current->left;
            if (current->left  == 0) return current->right;

	    //
            B_Node* tmp = current;
	    //
	    current = tmp->right
            while (current->left) current = current->left;
	    //
            current->right = Del_loop(current);
            current->left = tmp->left;
	    //
	    return current;
    }
  }
}



int main()
{
  //
  //                        8(0)
  //           4(10)                     12(20)
  //     2(30)       6(40)        10(50)         14(60)
  // 1(70) 3(80) 5(90) 7(100) 9(110) 11(120) 13(130) 15(140)
  //
  // order of key when print: 8, 4, 2, 1, 3, 6, 5, 7, 12, 10, 9, 11, 14, 13, 15
  //
  int dt[15] = {8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15};
  BST bt;
  // put
  for (int i = 0; i < 15; i++) {
    bt.put(dt[i], i * 10);
  }
  // print
  std::cout << "  BST:\n";
  std::cout << "with print():\n";
  bt.print();
  std::cout << "\n";
  // get
  std::cout << "get key(8):" << bt.get(8) << "\n";
  std::cout << "get key(9):" << bt.get(9) << "\n\n";
  // max key vale
  std::cout << "Max Key:" << bt.MaxK() << "\n\n";
  // delete
  //
  //                        8(0)
  //           4(10)                     13(130)
  //     2(30)       6(40)        10(50)
  // 1(70) 3(80) 5(90) 7(100) 9(110) 11(120)
  //
  // order of key when print: 8, 4, 2, 1, 3, 6, 5, 7, 13, 10, 9, 11
  //
  std::cout << "Del(15):\n";
  bt.Del(15);
  std::cout << "Del(14):\n";
  bt.Del(14);
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
