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
    graphStructure *covid19 = new graphStructure();

    string name; 
    int age;
    double s_prob;
    
    ifstream inf("smalldo.dat");
    
    while(inf>>name>>age>>s_prob){
        
        covid19->addPersonNode(new Person(name,age,s_prob));
    }
    
}
//***************************************************************************************************
//My code

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>
#include <random>

using namespace std;

enum Status{one, two, three, four};

class Person{
	private:
		string name;
		int age;
		float s_prob;
		float d_prob;
		int duration;
		bool is_infected;
		bool is_sick;
		bool is_alive;
		bool is_dead;
		bool recovered;
		Status status;
		vector<Person*> *connections;



	public:
		Person(string name, int age, float s_prob){
			this->name = name;
			this->age = age;
			this->s_prob = s_prob;
			this->d_prob = d_prob;
			this->duration = duration;
			this->status = status;
			this->is_infected = false;
			this->is_sick = false;
			this->is_alive = true;
			this->is_dead = false;
			this->recovered = false;
			this -> connections = new vector<Person*>();
		}

		void setName(std::string name){
			this->name = name;
		}

		std::string getName(){
			return name;
		}

		void setAge(int age){
			this->age = age;
		}

		int getAge(){
			return age;
		}

		void setS_Prob(float s_prob){
			this->s_prob = s_prob;
		}

		float getS_Prob(){
			return s_prob;
		}

		void setD_Prob(float d_prob){
			this->d_prob = d_prob;
		}

		float getD_Prob(){
			return d_prob;
		}

		void setStatus(Status status){
			this->status = status;
		}

		Status getStatus(){
			return status;
		}

		void setDuration(int duration){
			this->duration = duration;
		}

		int getDuration(){
			return duration;
		}

		void setis_Infected(bool is_infected){
			this->is_infected = is_infected;
		}

		bool getis_Infected(){
			return is_infected;
		}

		void setis_Sick(bool is_sick){
			this->is_sick = is_sick;
		}

		bool getis_Sick(){
			return is_sick;
		}

		void setis_Alive(bool is_alive){
			this->is_alive = is_alive;
		}

		bool getis_Alive(){
			return is_alive;
		}

		void setis_Dead(bool is_dead){
			this->is_dead = is_dead;
		}

		bool getis_Dead(){
			return is_dead;
		}

		void setRecovered(bool recovered){
			this->recovered = recovered;
		}

		bool getRecovered(){
			return recovered;
		}

		bool checkIn(Person* node){
			for(auto person: *connections){
				if(node == person)
					return true;
			}
			return false;
		}

		void insertNode(Person* node){
			if(!checkIn(node)){
				connections -> push_back(node);
			}
		}



		void printConns(){
			for(auto x:*connections){
				cout<<x->getName()<<" "<<endl;
			}
		}

		bool checkInfect(){

			for(auto v: *connections){
				v->setis_Infected(true);
				return true;
			}

		}

		bool simulate_prob(float prob){
		    prob = prob*1000;

		    std::random_device dev;
		    std::mt19937 rng(dev());

			static std::uniform_int_distribution<std::mt19937::result_type>
			random_number(1, 1000);

		    if (random_number(rng) <= prob){

		    	return true;
			}
		    return false;
		}

		void infect(){
			for(auto v: *connections){
				if(simulate_prob(v->getS_Prob())){
					v->setStatus(Status::two);
					cout<<v->getName()<<" has been infected" <<endl;
				}
			}

		}

		void print(){
			cout<<name<<" "<<age<<" "<<s_prob<<endl;
		}
};


class graph{
	int maximumAge;
	int peopleInfected;
	int recoveredPeople;
	float diseaseProb;
	vector<Person*> *adjacencyList;

	bool checkIn(Person* node){
		for(auto person: *adjacencyList){
			if(node == person){
				return true;
			}
		}
		return false;
	}

	public:
		graph(){
			maximumAge = 0;
			peopleInfected = 0;
			recoveredPeople = 0;
			diseaseProb = 0.0;
			adjacencyList = new vector<Person*> ();
		}

		bool addPersonNode(Person* n){
			if(!checkIn(n)){
				adjacencyList->push_back(n);
				return true;
			}
			return false;
		}

		bool addConnections(string name1, string name2){
			Person* person1 = nullptr;
			Person* person2 = nullptr;

			for(auto prsn: *adjacencyList){
				if(person1 != nullptr && person2 != nullptr)
					break;

				if(prsn -> getName() == name1)
					person1 = prsn;

				else if(prsn -> getName() == name2)
					person2 = prsn;
			}
			person1->insertNode(person2);
			person2->insertNode(person1);
		}

		int maxAge(){
			for(auto v:*adjacencyList){
				if(v->getAge() > maximumAge){
					maximumAge = v->getAge();
				}
			}
			return maximumAge;
		}


		void printGraph(){
			for(auto x: *adjacencyList){
				x->print();
			}
		}

		void getConnections(){
			for(auto x: *adjacencyList){
				cout<<"List of people "<<x->getName()<<"'s"<<" infected: "<<endl;
				x->printConns();
				cout<<"------------------------"<<endl;
				cout<<endl;
			}
		}

		bool simulate_prob(float prob){

		    prob = prob*1000;

		    std::random_device dev;
		    std::mt19937 rng(dev());

		    std::uniform_int_distribution<std::mt19937::result_type>
		    random_number(1, 1000);

		    if (random_number(rng) <= prob)
		        return true;

		    return false;
		}


		void infectPerson(){
			int randIndex = rand() % adjacencyList->size();
			Person* c = adjacencyList->at(randIndex);
			c->setD_Prob(float(c->getAge())/float(maximumAge));
			diseaseProb = c->getD_Prob();
			if(simulate_prob(c->getS_Prob())){
				c->setStatus(Status::two);
			}
			cout<<c->getName()<<" has been infected "<<endl;
			c->infect();
			if(simulate_prob(diseaseProb)){
				c->setis_Sick(true);
				cout<<c->getName()<<" is sick "<<endl;

			}




		}

		void getSummary(){
			int countPeople  = 0;
			for(unsigned int i=0; i<adjacencyList->size(); i++){
				adjacencyList[i];
				countPeople += 1;
			}
			cout<<"Total number of people in the population: "<<countPeople<<endl;

			int countAlive = 0;
			for(auto v: *adjacencyList){
				if(v->getis_Alive()==true){
					countAlive += 1;
				}

			}
			cout<<"Total number of Alive people: "<<countAlive<<endl;

			int countRecovered = 0;
			for(auto v: *adjacencyList){
				if(v-> getRecovered() == true){
					countRecovered += 1;
				}
			}
			cout<<"Total number of recovered people: "<<countRecovered<<endl;

			int countSick = 0;
			for(auto v: *adjacencyList){
				if(v->getis_Sick()==true){
					countSick += 1;
				}
			}
			cout<<"Total number of sick people: "<<countSick<<endl;

			int countDead = 0;
			for(auto v: *adjacencyList){
				if(v->getis_Dead()==true){
					countDead += 1;
				}
			}
			cout<<"Total number of dead people: "<<countDead<<endl;

			int countInfected = 0;
			for(auto v: *adjacencyList){
				if(v->checkInfect() == true){
					countInfected += 1;
				}
			}
			cout<<"Total number of infected people: "<<countInfected<<endl;
		}

//		void updateStats(){
//			int choice;
//			cout<<"Enter choice"<<endl;
//			cin>>choice;
//
//			switch(choice){
//				case 1:
//					//
//					graph::infectPerson();
//
//					break;
//
//				case 2:
//
//					break;
//
//				case 3:
//
//
//					break;
//
//				case 4:
//
//
//					break;
//
//			}
//
//
//
//		}
};

//int main(){
//	ifstream file("smallpopulation.dat");
//	string name, nam1, nam2;
//	int age;
//	float s_prob;
//
//	graph* covid = new graph();
//
//	while(file>>name >> age >> s_prob){
//		Person p(name, age, s_prob);
//		covid->addPersonNode(new Person(name, age, s_prob));
//
//	}
//	file.close();
//	covid->printGraph();
//
//	cout<<"----Testing Connections---"<<endl;
//
//	ifstream file2("smallconnections.dat");
//
//	while(file2>>nam1>>nam2){
//		covid->addConnections(nam1, nam2);
//
//	}
//	file.close();
//	covid->infectPerson();
//
//
//}

}
