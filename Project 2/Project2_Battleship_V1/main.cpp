/* 
 * File:   main.cpp
 * Author: Christopher Delgado
 * Created on May 1st, 2020, 9:59 PM
 * Purpose: Battleship
 */

//System Level Libraries
#include <iostream>   //I/O Library
#include <ctime>
#include <iomanip>
using namespace std;  //Libraries compiled under std

//User Level Libraries

//Global Constants - Science/Math Related
//Conversions, Higher Dimensions

//Function Prototypes
void srtScrn(char);
void fillBrd(int [], int);
void dsplyBd(int [], int, int, int);
void hitMiss(int [], int [], int, int, int);
void filBoat(int [], int);
bool winLose(int [], int, int &, int, bool);

//Execution Begins Here!
int main(int argc, char** argv) {
    //Random Number Seed Set Here
    srand(static_cast<unsigned int>(time(0)));
    
    //Variable Declarations 
    const int SIZE=100;
    const int NBOATS=10;
    int gBoard[SIZE];
    int boats[NBOATS];
    int choice;                              //User choice of where to shoot on board
    int turn, maxTurn;                       //Used for the amount of turns and max turns in game
    bool loop;                               //Used for do while loop
    char start;                              //Used to start game 
 
    //Variable Initialization   
    maxTurn=50;                  //Max amount of turns is 25
    turn=1;                      //Player starts on turn 1
       
    //Mapping Process Inputs to Outputs
               
    //Display Outputs
    //Assigns random value to boats
    filBoat(boats, NBOATS);
    
    //fill board 1-100
    fillBrd(gBoard, SIZE);
    
    //Presents start screen and instructions        
    srtScrn(start);
    
    do{
        //Display GameBoard
        dsplyBd(gBoard, SIZE, turn, maxTurn);
        
        //Gameplay function that determines a hit or a miss
        hitMiss(gBoard, boats, SIZE, NBOATS, choice);
       
        //Function either returns false or true
        loop=winLose(boats, NBOATS, turn, maxTurn, loop);
        
    }while(loop);
    
    
    //Clean Up
    
    //Exit stage right!
    return 0;
}

void srtScrn(char start){
    //Asks user to start or exit
    cout<<"Welcome to Battleship\n";
    cout<<"Press Y to play or press N to exit\n";
    cin>>start;
    while(start!='y'&&start!='Y'&&start!='n'&&start!='N'){   //Input validation using while loop
        cout<<"Please enter either Y or N\n";
        cin>>start;
    }
    switch(start){   //Pressing Y leads to rest of code while N exits program
        case('Y'):
        case('y'):
            break;
        case('N'):
        case('n'):
            exit (0);
            break;
    }
    //Instructions for game
    cout<<"You will have to sink all of the computers ships in order to win!\n";
    cout<<"Each row is labeled from 1-10, 11-20, etc.\n";
    cout<<"The computer will randomly place 10 boats 1 space big and "
        <<"it is your objective to find them and sink them.\n";
    cout<<"A hit will be indicated by a \"X\" and a miss will be indicated by a \"0\".\n\n";
    
}

//Gives Values to array starting at 1 to 100
void fillBrd(int array[],int SIZE){
    int temp=1;
    for(int n=0; n<SIZE; n++){
        array[n]=temp++;
    }
}

//Displays the gameboard 
void dsplyBd(int array[], int SIZE, int turn, int maxTurn){
    for (int n=0; n<SIZE; n++){
        if(n==0){
            cout<<"Turn#: "<<turn<<endl;
            cout<<"Max Turn#: "<<maxTurn<<endl;
            cout<<setw(27)<<"Battleship"<<endl;
        }
        if(array[n]=='X')cout<<"   "<<'X';
        else if(array[n]<10)cout<<"   "<<array[n];
        else cout<<"  "<<array[n];
        if(n%10==(10-1))cout<<endl<<endl;;
    }
}

//Adds values to boats 1-5
void filBoat(int a[], int NBOATS){
    for(int n=0; n<NBOATS; n++){
        a[n]=rand()%100+1;
    }
    for(int i=0; i<=100; i++){
        for(int n=0; n<NBOATS; n++){
            if(a[n]==a[n+1])a[n]=rand()%100+1;
            if(a[n]==a[n+2])a[n]=rand()%100+1;
            if(a[n]==a[n+3])a[n]=rand()%100+1;
            if(a[n]==a[n+4])a[n]=rand()%100+1;
            if(a[n]==a[n+5])a[n]=rand()%100+1;
            if(a[n]==a[n-1])a[n]=rand()%100+1;
            if(a[n]==a[n-2])a[n]=rand()%100+1;
            if(a[n]==a[n-3])a[n]=rand()%100+1;
            if(a[n]==a[n-4])a[n]=rand()%100+1;
            if(a[n]==a[n-5])a[n]=rand()%100+1;
        }
    }
    //for(int j=0; j<NBOATS; j++){
    //    cout<<a[j]<<"   ";
    //}
}


//Function informs user whether or not they got a hit or a miss
void hitMiss(int gBoard[], int boats[], int SIZE, int NBOATS, int choice){
    cout<<"Which spot do you wanna shoot"<<endl;
    cin>>choice;
    while(choice<1||choice>100){     //Input validation for keeping choice input between 1-30
        cout<<"Please pick a number between 1-100\n";
        cin>>choice;
    }
    bool hit=false;
    
    for(int n=0; n<NBOATS; n++){
        if(choice==boats[n]){
            boats[n]=0;
            hit=true;
        }
    }
    if(hit==true){
        cout<<"You got a hit"<<endl;
        for(int n=0; n<NBOATS; n++){
            for(int i=0; i<SIZE; i++){
                if(choice==gBoard[i]){
                    static_cast<char>(gBoard[i]);
                    gBoard[i]='X';
                }
            }
        }
    }
    if(hit==false){
        for(int j=0; j<SIZE; j++){
            if(choice==gBoard[j]){
                cout<<"That was a miss"<<endl;
                gBoard[j]=0;
            }
        }
    }
}

//Function that informs if game has been won or lost
bool winLose(int boats[], int NBOATS, int &turn, int maxTurn, bool loop){
    //Informs the player that they have run out of turns and lost
    if(turn==maxTurn){              
            cout<<"You ran out of turns.\n";
            cout<<"You Lost! :(\n";
            return false;
    }
    //Informs the player that they have sunken all the ships
    else if(boats[0]==0&& boats[1]==0&& boats[2]==0&& boats[3]==0&& boats[4]==0,
            boats[5]==0&& boats[6]==0&& boats[7]==0&& boats[8]==0&& boats[9]==0){  
            cout<<"You sunk all the ships!\n";
            cout<<"You won!\n";
            return false;
    }
    else{
        turn++;
        return true;
    }    
}