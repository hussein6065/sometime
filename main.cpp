#include <iostream>
#include <string>
#include <time.h>
#include "graph.cpp"
using namespace std;



void Sim(graph* disease,int numOfTime);
void loadData(graph* covid, string filepop, string fileconn);
/* You can use this function to simulate
probabilities */
bool simulate_prob(float prob){

    prob = prob*1000.0;

    

    if (rand()%1000 <= prob)
        return true;

    return false;
}

int main(){
    srand(time(NULL));
    graph* covid = new graph();

    /* The number of days simulation will run for */
    int days_to_simulate = 100;

    /* Ask the user for the population and
    connections files */
    cout << "Welcome to CoronaSim!" << endl;
    string pop_file, conn_file;
    cout << "Enter population file name: ";
    cin >> pop_file;
    cout << "Enter connections file name: ";
    cin >> conn_file;

    loadData(covid,pop_file,conn_file);
    // TODO: Populate your graph data structure
    bool is_populated = false;

    if (is_populated)
        cout << "File Loaded!" << endl;
    
    while(true){

        int choice;

        /* Print menu of things that your application can do*/
        cout << "*** *** *** *** *** *** *** *** *" << endl;
        cout << "What would you like to do?" << endl;
        cout << "1. Print population" << endl;
        cout << "2. Simulate" << endl;
        cout << "3. Summarize population" << endl;
        cout << "4. Implement policy and simulate" << endl;
        cout << "5. Exit" << endl;
        cout << "*** *** *** *** *** *** *** *** *" << endl;
        cout << "Your selection: ";

        /* TODO: You should feel free to add other
        items to the menu above for your demo video */

        cin >> choice;

        /*Ideally inside the various cases of the switch
        statement below, you will call specific functions
        supported by your graph data structure and your
        simulation algorithm. You can design all these
        functions as you like.*/

        switch(choice){

            case 1:
                covid->printGraph();
                /* TODO: Print your population. Use
                any format you like.*/
                break;

            case 2:
                Sim(covid,days_to_simulate);

                /* TODO: Run simulation as described
                in the handout.*/
                break;

            case 3:
                covid->summary();

                /* TODO: Print a summary of the population
                here. Design the summary as you like.
                Print at least the number of people
                infected, sick, recovered, dead etc.*/
                break;

            case 4:

                /* TODO: Implement your own policy and
                re-simulate.*/
                break;

            case 5:

                /* TODO: Here de-allocate all dynamically
                allocated variables before exiting*/
                return 0; // exiting
        }
    }
}

void Sim(graph* disease,int numOfTime){

    for (int i = 0; i<numOfTime; i++){
        
        if(i==0){
            disease ->infectPerson();
        }
        else if(i == 1){
            disease->updateCovidStatus();
        }
        else{
            disease->updateCovidStatus();
            disease->getRecovedCase();
        }
    }
}

void loadData(graph* covid, string filepop, string fileconn){
    ifstream file(filepop);
	string name, nam1, nam2;
	int age;
	float s_prob;
    srand(time(NULL));

	

	while(file>>name >> age >> s_prob){
		Person p(name, age, s_prob);
		covid->addPersonNode(new Person(name, age, s_prob));

	}
	file.close();

	ifstream file2(fileconn);

	while(file2>>nam1>>nam2){
		covid->addConnections(nam1, nam2);

	}
	file.close();
}
