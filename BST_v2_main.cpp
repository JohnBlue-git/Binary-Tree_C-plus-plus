
/*
Auther: John Blue
Time: 2022/1
Platform: ATOM with MinGw and g++compiler
Object: Binary Search Tree
Version 2: update Del(...)
Version 2(*): BST as Node
Version 3: BST as controller to Node
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
class BST {
private:
  // content
  int key;
  int data;
  BST* left;
  BST* right;
  // operator
  BST& operator=(const BST& copy);

protected:
  // function
  int get_key() const { return key; }
	int get_data() const { return data; }
	BST* get_left() const { return left; }
  BST* get_right() const { return right; }

public:
  // constructor
  BST(): key(- 1), data(0), left(0), right(0) {}
  BST(int k, int d): key(k), data(d), left(0), right(0) {}
  BST(const BST& copy);
  ~BST();

  // function
  void print();
  void put(int ky, int dt);
  int get(int ky);
  int MinK();
  int MaxK();
  //int floor(int ky);
  //int ceil(int ky);
  //void Del(ky) with p_current = 0
  void Del(int ky, BST** p_current);
};

BST::BST(const BST& copy): key(copy.key), data(copy.data), left(0), right(0) {
  // left
  if (copy.left != 0) {
    left = new BST(*copy.left);
  }
  // right
  if (copy.right != 0) {
    right = new BST(*copy.right);
  }
}

BST::~BST() {
  // data
  key = 0;
  data = 0;
  // left
  if (left != 0) {
    left->~BST();
    left = 0;
    // delete null will not doing anything, but it will prevent to delete next ...
    //delete left;
    //std::cout << "left\n";
  }
  // right
  if (right != 0) {
    right->~BST();
    right = 0;
    // delete null will not doing anything, but it will prevent to delete next ...
    //delete right;
    //std::cout << "right\n";
  }
}

void BST::print() {
  // checks
  if (key == 0) {
    std::cout << "hi\n";
    return;
  }
  // middle
  std::cout << "key" << key << ": " << data << "\n";
  // left
  if (left != 0) {
    left->print();
  }
  // right
  if (right != 0) {
    right->print();
  }
}

void BST::put(int ky, int dt) {
  BST* current = this;
  // first?
  if (current->key == - 1) {
    current->key = ky;
    current->data = dt;
    return;
  }
  // insert
  while(1) {
    if (ky < current->key) {
      if (current->left == 0) {
        current->left = new BST(ky, dt);
        break;
      }
      else {
        current = current->left;
      }
    }
    else if (ky > current->key) {
      if (current->right == 0) {
        current->right = new BST(ky, dt);
        break;
      }
      else {
        current = current->right;
      }
    }
    else if (ky == current->key) {
      data = dt;
      break;
    }
  }
}

int BST::get(int ky) {
  BST* current = this;
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
  BST* current = this;
  while(current->left != 0) {
    current = current->left;
  }
  return current->data;
}

int BST::MaxK() {
  BST* current = this;
  while(current->right != 0) {
    current = current->right;
  }
  return current->data;
}

// case:
// no kid
// one kid
// two kids
void BST::Del(int ky, BST** p_current = 0) {
  //BST** p_current; address of parent left or right pointer
  BST* current = this;
  while (current != 0) {
    // search
    if (ky < current->key) {
      p_current = &(current->left);
      current = current->left;
    }
    else if (ky > current->key) {
      p_current = &(current->right);
      current = current->right;
    }
    // delete
    else if (ky == current->key) {
      if (current->left == 0 && current->right == 0) {
        *p_current = 0;// !!! very important; cut the link; prevent further delete
        current->~BST();//delete current; not work @@
        return;
      }
      else if (current->left != 0 && current->right == 0) {
        *p_current = current->left;
        current->left = 0;
        delete current;
        return;
      }
      else if (current->left != 0 && current->right == 0) {
        p_current = &(current->left);
        BST* cur = current->left;
        while (cur->right) {
          p_current = &(cur->right);
          cur = cur->right;
        }
        current->data = cur->data;
        Del(cur->data, p_current);
      }
      else {
        p_current = &(current->right);
        BST* cur = current->right;
        while (cur->left) {
          p_current = &(cur->left);
          cur = cur->left;
        }
        current->data = cur->data;
        Del(cur->data, p_current);
      }
      return;
    }
  }
  // not found
  std::cout << "no such key\n";
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
  std::cout << "BST:\n";
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
