#include<bits/stdc++.h>
using namespace std;
 
int min(int a, int b){
    if (a<=b){
        return a;
    } else{
        return b;
    }
}
 
 
 
int precedence(const string& op) {
    if (op == "+" || op =="-"){
        return 0;
 
    } else if(op == "*" || op == "/" ){
            return 1;
    } else if (op == "max" || op == "min") {
        return 2;
    } else {
        return -1;
    }
}
 
int max(int a, int b){
    if (a>=b){
        return a;
    } else{
        return b;
    }
}
 
 
template <typename T>
class Stack {
private:
    T* stack;
    int size;
    int top;
 
public:
    Stack() {
        size = 100;
        stack = new T[size];
        top = -1;
    }
 
    ~Stack() {
        delete[] stack;
    }
 
    void push(const T& c) {
        if (top < size - 1) {
            stack[++top] = c;
        }
    }
 
    T pop() {
        if (!isEmpty()) {
            T a = stack[top];
            --top;
            return a;
        }
    }
 
    T peek() const {
        if (!isEmpty()) {
            return stack[top];
        } else {
            return T();
        }
    }
 
    bool isEmpty() const {
        return top == -1;
    }
};
 
 
 
int main()
{
    int i = 0;
    Stack<string> operators;
    Stack<string> mmStack;
    string a;
    string postfix;
    getline(cin, a);
    while (i < a.length()) {
        if (isdigit(a[i])) {
            string temp;
            temp.push_back(a[i]);
            postfix += temp + " ";
            i++;
        }
        else if (a[i] == 'm') {
            if (a[i + 1] == 'a') {
                mmStack.push("max");
            }
            if (a[i + 1] == 'i') {
                mmStack.push("min");
            }
            i += 3;
            continue;
        } else if (a[i] == '+' || a[i] == '-' || a[i] == '/' || a[i] == '*'){
            string op;
            switch (a[i]) {
                case '+':
                    op = "+";
                    break;
                case '-':
                    op = "-";
                    break;
                case '/':
                    op = "/";
                    break;
                case '*':
                    op = "*";
            }
            if (!operators.isEmpty()) {
                if (precedence(operators.peek()) != -1) {
                    while (precedence(operators.peek()) >= precedence(op)) {
                        postfix += operators.pop() + " ";
                    }
                }
            }
            operators.push(op);
            i++;
        }
        else if (a[i] == ','){
            while (!(operators.peek() == "(" || operators.peek() == ")")) {
                postfix += operators.pop() + " ";
            }
            operators.pop();
            operators.push(mmStack.pop());
            operators.push("(");
            i += 1;
        }
        else if (a[i] == '(') {
            operators.push("(");
            i+=1;
        }
        else if (a[i] == ')') {
            while (!(operators.peek() == "(")) {
                postfix += operators.pop() + " ";
            }
            operators.pop();
            i+=1;
        } else {
            i += 1;
        }
    }
 
    while (!operators.isEmpty()) {
        postfix += operators.pop() + " ";
    }
    
    Stack<int> operands;
 
    //Evaluate the postfix expression postfix using the stack operands
    for(int i = 0; i<postfix.length(); i++)
    {
        if(postfix[i] == ' ')
        {
            continue;
        }
        else if(isdigit(postfix[i]))
        {
 
            operands.push(postfix[i] - '0');
        }
        else if(postfix[i] == '+')
        {
            int a = operands.pop();
            int b = operands.pop();
            operands.push(a+b);
        }
        else if(postfix[i] == '-')
        {
            int a = operands.pop();
            int b = operands.pop();
            operands.push(b-a);
        }
        else if(postfix[i] == '*')
        {
            int a = operands.pop();
            int b = operands.pop();
            operands.push(a*b);
        }
        else if(postfix[i] == '/')
        {
            int a = operands.pop();
            int b = operands.pop();
            operands.push(b/a);
        }
        else if(postfix[i] == 'm')
        {
            if(postfix[i+1] == 'a')
            {
                int a = operands.pop();
                int b = operands.pop();
                operands.push(max(a,b));
            }
            else if(postfix[i+1] == 'i')
            {
                int a = operands.pop();
                int b = operands.pop();
                operands.push(min(a,b));
            }
            i+=2;
        }
    }
 
    cout << operands.pop() << endl;
    
    return 0;
}