#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<time.h>

using namespace std;

class Person{
    
    string name;
    int age;
    double s_prob;
    double d_prob;
    int howlong;
    int covidStatus;
    vector<Person*> connectedPeople;

    public:
        Person(string name, int age, double s_prob){
            this -> name = name;
            this -> age = age;
            this -> s_prob = s_prob;
        }

};
