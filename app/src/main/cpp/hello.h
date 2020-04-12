//
// Created by lijun on 2020/4/12.
//

#ifndef ANDROIDLEARNJNI3_HELLO_H
#define ANDROIDLEARNJNI3_HELLO_H


#include <string>
#include <sstream>
using namespace std;

class Process{
    //成员sometype pr
public:
    ~Process(){
    }
    Process();
    Process(string);
    string process(int);
};

#endif //ANDROIDLEARNJNI3_HELLO_H
