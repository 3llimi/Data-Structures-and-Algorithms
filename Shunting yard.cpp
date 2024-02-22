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
 
 
class Stack {
private:
    string* stack;
    int size;
    int top;
 
public:
    Stack() {
        size = 100;
        stack = new string[size];
        top = -1;
    }
 
    ~Stack() {
        delete[] stack;
    }
 
    void push(const string& c) {
        if (top < size - 1) {
            stack[++top] = c;
        }
    }
 
    string pop() {
        if (!isEmpty()) {
            string a = stack[top];
            --top;
            return a;
        }
    }
 
    string peek() const {
        if (!isEmpty()) {
            return stack[top];
        } else {
            return "";
        }
    }
 
    bool isEmpty() const {
        return top == -1;
    }
};
 
int main()
{
    int i = 0;
    Stack operators;
    Stack mmStack;
    string a;
    getline(cin, a);
    while (i < a.length()) {
        if (isdigit(a[i])) {
            cout << a[i] << " ";
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
                        cout << operators.pop() << " ";
                    }
                }
            }
            operators.push(op);
            i++;
        }
        else if (a[i] == ','){
            while (!(operators.peek() == "(" || operators.peek() == ")")) {
                cout << operators.pop() << " ";
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
                cout << operators.pop() << " ";
            }
            operators.pop();
            i+=1;
        } else {
            i += 1;
        }
    }
    while(!operators.isEmpty()){
        cout << operators.pop() << " ";
    }
 
    return 0;
}