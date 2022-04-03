// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
int priority(char pr) {
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
        int mr = priority(inf[i]);
        if ((priority(inf[i]) == -1) && (inf[i] != ')')) {
            if (!post.empty() && priority(inf[i - 1]) != -1) {
                post.push_back(' ');
            }
            post.push_back(inf[i]);
        } else if ((priority(inf[i]) > priority(stack1.get()))
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
                while (priority(stack1.get()) >= priority(inf[i])) {
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
    int uni = 0;
    for (int i = 0; i < pref.size(); i++) {
        if (lat(pref[i]) > -1) {
            uni = uni * 10 + lat(pref[i]);;
        } else {
            if (uni != 0) {
                stack2.push(uni);
                uni = 0;
            }
            switch (pref[i]) {
            case '+':
            {
                int uni1 = stack2.get();
                stack2.pop();
                int uni2 = stack2.get();
                stack2.pop();
                stack2.push(uni1 + uni2);
                break;
            }
            case '-':
            {
                int uni1 = stack2.get();
                stack2.pop();
                int uni2 = stack2.get();
                stack2.pop();
                stack2.push(uni2 - uni1);
                break;
            }
            case '*':
            {
                int uni1 = stack2.get();
                stack2.pop();
                int uni2 = stack2.get();
                stack2.pop();
                stack2.push(uni1 * uni2);
                break;
            }
            case '/':
            {
                int uni1 = stack2.get();
                stack2.pop();
                int uni2 = stack2.get();
                stack2.pop();
                stack2.push(uni2 / uni1);
                break;
            }
            }
        }
    }
    return stack2.get();
}
