#include <iostream>
#include <boost/optional/optional.hpp>
#include <boost/optional/optional_io.hpp>

using namespace std;

template< typename left_type, typename right_type>
struct either
{
  union either_u {
    left_type l;
    right_type r;
  };

  either_u value;
  bool current_type;

  // postcondition, is_left()
  either( left_type lt) {
    current_type = 0;
    value.l = lt; 
  }

  // postcondition, is_right()
  either( right_type rt) {
    current_type = 1; 
    value.r = rt;
  }

  bool is_left() {
    !current_type; 
  } 

  bool is_right() {
    current_type;
  } 

//  // postcondition, is_left()
//  either & operator=( const left_type & lt ) {
//    return *this;  
//  }
//
//  // postcondition, is_right()
//  either & operator=( right_type & rt ) {
//    return *this;
//  }

  // precondition, is_left()
  left_type left() {
    return value.l;
  }

  // precondition, is_right()
  right_type right() {
    return value.r;
  }
private:
};

template <typename optional_type>
struct some;
struct none;

struct nothing {
};

template <typename optional_type>
struct option {
  virtual bool isEmpty() = 0; 
  //virtual bool isDefined();
  //virtual optional_type get();
  //virtual getOrElse
  virtual option<optional_type> map() = 0;
//  template <typename A>  
//  option<optional_type> map(A &lambda) {
//    if (isEmpty()) {
//      none y;
//      return y;
//    }
//    else {
//      return some<optional_type>(lambda(this.get()))
//    }
//  }
private: 
};

template <typename optional_type>
struct some : public option<optional_type> {
public:
  optional_type x;
  bool isEmpty() { return false; }
  optional_type get() { return x; }
  some(optional_type optional) { x = optional; }

  option<optional_type> map(optional_type &lambda) {
    return some<optional_type>(x);
  }
private:
};

//struct none : public option<nothing> {
//  bool isEmpty() { return true; } 
//  void get() { throw std::invalid_argument("Can't get from None"); } 
//private:
//};

int add2(int x) {
  return x + 2; 
} 

int main() {

either<int, bool> banana(33);

some<int> apple(10);
some<int> apple2(apple.map(add2));

//none carrot;

cout << apple.get() << endl;

cout << banana.left() << endl;


//auto banana = either<int, bool>(33);
//
//  if (banana.is_left())
//    cout << banana.left();

}
