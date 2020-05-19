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
		bool recovered;
		Status status;
		vector<Person*> *connections;



	public:
		Person(string name, int age, float s_prob){
			this->name = name;
			this->age = age;
			this->s_prob = s_prob;
			this->d_prob = 0.0;
			this->duration = 0;
			this->status = one;
            recovered = false;
			this -> connections = new vector<Person*>();
		}

		void setName(string name){
			this->name = name;
		}

		string getName(){
			return name;
		}

		void setAge(int age){
			this->age = age;
		}
        void setRecovery(bool recover){
            this->recovered = recover;
        }
        bool getRecovery(){
            return recovered;
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

		bool simulate_prob(float prob){

            prob = prob*1000.0;
            if (rand()%1000 <= prob){
                return true;
            }
            return false;
        }

		void infectPeople(){
			for(auto v: *connections){
				if(simulate_prob(v->getS_Prob())){
					v->setStatus(Status::two);
					// cout<<v->getName()<<" has been infected" <<endl;
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
                if(n->getAge()>maximumAge)
                    maximumAge = n->getAge();
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
            person1 ->setD_Prob((float)person1->getAge()/(float)this->maximumAge);
			person2->insertNode(person1);
		}


		void printGraph(){
			for(auto x: *adjacencyList){
				x->print();
			}
		}
        int getNumInfected(){
            int count = 0;
            for(auto person:*adjacencyList){
                if(person->getStatus()!= one)
                    count++;
            }
            return count;
        }
        
        int getNumInfectedAndSick(){
            int count = 0;
            for(auto person:*adjacencyList){
                if(person->getStatus()== three)
                    count++;
            }
            return count;
        }
        int getRecovedCase(){
            int count = 0;
            for(auto person:*adjacencyList){
                if(person->getRecovery()== true)
                    count++;
            }
            return count;
        }
        int getNumDeath(){
            int count = 0;
            for(auto person:*adjacencyList){
                if(person->getStatus()== four)
                    count++;
            }
            return count;
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

            prob = prob*1000.0;
            if (rand()%1000 <= prob){
                return true;
            }
            return false;
        }

        void updateCovidStatus(){

            for(auto person: *adjacencyList){
                
                switch (person->getStatus()){

                case two:
                    person->setDuration(person->getDuration()+1);
                    if(simulate_prob(person->getD_Prob())){
                        person -> setStatus(Status::three);
                        
                    }
                    person ->infectPeople();
                    break;
                case three:
                    person->setDuration(person->getDuration()+1);   
                    if(person->getDuration()>=7)
                        person ->setStatus(four);
                    person ->infectPeople();
                    break;
                default:
                    break;
                }
            }
        }

        void patientsRecovery(){
            for(auto person:*adjacencyList){
                if(simulate_prob(1-person->getD_Prob())){
                    person->setStatus(Status::one);
                    person->setDuration(0);
                    person ->setRecovery(true);
                }
            }
        }

        void infectPerson(){
            int randIndex = rand() % adjacencyList->size();
			Person* c = adjacencyList->at(randIndex);
            if(simulate_prob(c->getS_Prob())){
				c->setStatus(Status::two);
			}
            else{
                infectPerson();
            }

        }
        void summary(){
            cout<<"****** Simulation Summary ********" <<endl;
            cout<<" Days: "  <<endl;
            cout<<" Total Number of cases: "<<this->getNumInfected()<<endl;
            cout<<" Total Number of Recovery: "<<this->getRecovedCase()<<endl;
            cout<<" Total Number of Sick Covid patients: "<<this->getNumInfectedAndSick()<<endl;
            cout<<" Total Number of Deaths: "<<this->getNumDeath()<<endl;

        }

	};
		
// int main(){
    
// 	ifstream file("population.dat");
// 	string name, nam1, nam2;
// 	int age;
// 	float s_prob;
//     srand(time(NULL));

// 	graph* covid = new graph();

// 	while(file>>name >> age >> s_prob){
// 		Person p(name, age, s_prob);
// 		covid->addPersonNode(new Person(name, age, s_prob));

// 	}
// 	file.close();
// 	// covid->printGraph();

// 	cout<<"----Testing Connections---"<<endl;

// 	ifstream file2("connections.dat");

// 	while(file2>>nam1>>nam2){
// 		covid->addConnections(nam1, nam2);

// 	}
// 	file.close();

// 	covid->summary();
//     covid->infectPerson();
//     for(int i = 0; i<10;i++){
//         cout<<"--------------------"<<endl;
//         covid -> updateCovidStatus();
//         cout<<"--------------------"<<endl;
//         if(i>3){
//             covid->getRecovedCase();
//         }
//     }
//     covid->summary();

   

// }
