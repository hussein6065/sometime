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
        string getName(){
            return name;
        }

        // You can add the gettors and settor for the instance variables

};


class graphStructure{
    
    int maximumAge;
    int peopleInfected;
    int recoveredPeople;
    vector <Person*> *adjacencyListPerson;

    bool checkIn(Person* node){
            for(auto person: *adjacencyListPerson){
                if(node == person){
                    return true;
                }
            }
            return false;
        }

    public:

    graphStructure(){
        maximumAge = 0;
        peopleInfected = 0;
        recoveredPeople = 0;
        adjacencyListPerson = new vector<Person*>();
    }

    bool addPersonNode(Person* Node){
        if(!checkIn(Node)){
            adjacencyListPerson->push_back(Node);
        
            return true;
        }
        return false;
    }
    bool addConnect(string name1, string name2){

        Person* Nm = nullptr;
        Person* Nm2 = nullptr;
        for(auto person: *adjacencyListPerson){

            if (Nm != nullptr && Nm2 != nullptr)
                break;

            if(person -> getName() == name1)
                Nm = person;

            else if(person -> getName() == name2)
                Nm2 = person;

        }

        Nm->insertNode(Nm2);
        Nm2->insertNode(Nm);
    }
};

int main(){
    
}
