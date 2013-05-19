/*
 * Blazing Griffin code test
 * Part 2 : Data structures
 *
 * Trevor Fountain
 * April 2013
 */

#include <stdio.h>
#include <stack>

/**
   @brief TopStack provides the standard push/pop stack methods, plus an additional
   `getHighest()` method that returns the highest-valued int currently on 
   the stack.

   Feel free to make additions to the class definition, but justify any 
   modifications to the existing methods!
*/
class TopStack
{
protected:
  std::stack<int> stack;

  //added second stack to contain record of highest value slightly harder on
  //memory but quicker access time for highest value.  Using a second stack will
  //allow a comprehensive record of top values.
  std::stack<int> highest;
public:

  /// Push a value onto the top of the stack
  void push(int value);

  /// Remove the topmost value from the stack and return it
  int pop();

  /// Return the highest value currently on the stack
  int getHighest();
};

void TopStack::push(int value)
{
  // Implement me!
  //push the incomming value onto the stack
  stack.push(value);

  //check to see if the highest stack is empty or the incomming value is greater
  //than or equal to the current highest value
  if(highest.empty()||(value>=highest.top()))
    {
      //if the value is greater than or equal to the current highest push it
      //onto the highest stack
      highest.push(value);
    }
}

int TopStack::pop()
{
  // Implement me!

  //check to see if the stack is empty
  if(!stack.empty());
  {
    //if the stack is not empty get the top value
    int t=stack.top();

    //pop the stack to clear the top value
    stack.pop();

    //check the highest value, if its the one we just popped set the new highest
    //to the previous highest
    if(t==highest.top())
      {
	//if the value was the highest value
	highest.pop();
      }

    //return the top value
    return t;
  }

  //if the stack is empty return 0;
  return 0;
}

int TopStack::getHighest()
{
  // Implement me!

  if(!highest.empty())
    {
      //return the top value
      return highest.top();
    }
  //if the highest stack is empty return 0
  return 0;
}

int main(int argc, char **argv)
{
  bool pass = true;

  TopStack topStack;

  topStack.push(12);
  pass = pass && (topStack.getHighest() == 12);

  topStack.push(6);
  pass = pass && (topStack.getHighest() == 12);

  topStack.push(42);
  pass = pass && (topStack.getHighest() == 42);

  topStack.pop();
  pass = pass && (topStack.getHighest() == 12);

  printf("%s\n", pass ? "PASS" : "FAIL");

  return 0;
}
