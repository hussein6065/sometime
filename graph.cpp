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
    vector<Person*> *connectedPeople;

    public:
        Person(string name, int age, double s_prob){
            this -> name = name;
            this -> age = age;
            this -> s_prob = s_prob;
            this -> covidStatus = 0;
            this->howlong = 0;
            this -> connectedPeople = new vector<Person*>();

        }
        bool checkIn(Person* node){
            for(auto person: *connectedPeople){
                if(node == person){
                    return true;
                }
            }
            return false;
        }
        
        void insertNode(Person* node){
            if(!checkIn(node)){
                connectedPeople->push_back(node);
            }
        }

        // You can add the gettors and settor for the instance variables

};

int main(){
    
}
