// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int prior(char pr) {
    if (pr == '(') {
        return 1;
    }
    if (pr == '+' || pr == '-') {
        return 2;
    }
    if (pr == '*' || pr == '/') {
        return 3;
    }
    return -1;
}
std::string infx2pstfx(std::string inf) {
  TStack <char, 100> stack1;
    std::string post;
    for (int i = 0; i < inf.size(); i++) {
        int uni = prior(inf[i]);
        if ((prior(inf[i]) == -1) && (inf[i] != ')')) {
            if (!post.empty() && prior(inf[i - 1]) != -1) {
                post.push_back(' ');
            }
            post.push_back(inf[i]);
        } else if ((prior(inf[i]) > prior(stack1.get()))
                   || (stack1.isEmpty()) || (inf[i] == '(')) {
            stack1.push(inf[i]);
        } else {
            if (inf[i] == ')') {
                while (stack1.get() != '(') {
                    post.push_back(' ');
                    post.push_back(stack1.get());
                    stack1.pop();
                }
                stack1.pop();
            } else {
                while (prior(stack1.get()) >= prior(inf[i])) {
                    post.push_back(' ');
                    post.push_back(stack1.get());
                    stack1.pop();
                }
                stack1.push(inf[i]);
            }
        }
    }
    while (!stack1.isEmpty()) {
        post.push_back(' ');
        if (stack1.get() != '(') {
            post.push_back(stack1.get());
        }
        stack1.pop();
    }
    return post;
}
int lat(char x) {
    int k = 0;
    if (x >= '0' && x <= '9') {
        for (char i = '0'; i <= '9'; i++, k++) {
            if (x == i)
                return k;
        }
    }
    return -1;
}
int eval(std::string pref) {
  TStack<int, 100> stack2;
    int mr = 0;
    for (int i = 0; i < pref.size(); i++) {
        if (lat(pref[i]) > -1) {
            mr = mr * 10 + lat(pref[i]);
        } else {
            if (mr != 0) {
                stack2.push(mr);
                mr = 0;
            }
            switch (pref[i]) {
            case '+':
            {
                int ul = stack2.get();
                stack2.pop();
                int lu = stack2.get();
                stack2.pop();
                stack2.push(ul + lu);
                break;
            }
            case '-':
            {
                int ul = stack2.get();
                stack2.pop();
                int lu = stack2.get();
                stack2.pop();
                stack2.push(lu - ul);
                break;
            }
            case '*':
            {
                int ul = stack2.get();
                stack2.pop();
                int op2 = stack2.get();
                stack2.pop();
                stack2.push(ul * lu);
                break;
            }
            case '/':
            {
                int ul = stack2.get();
                stack2.pop();
                int lu = stack2.get();
                stack2.pop();
                stack2.push(lu / ul);
                break;
            }
            }
        }
    }
    return stack2.get();
}
