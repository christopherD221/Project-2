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
void dsplyBd(int [], int[], int, int);
void dsplyBd(int [], int, int, int);
void hitMiss(int [], int [], int, int, int);
void cmpChce(int [], int [], int [], int, int);
void filBoat(int [], int, int);
void usrBoat(int [], int, int);
bool winLose(int [], int, int &, int, bool);

//Execution Begins Here!
int main(int argc, char** argv) {
    //Random Number Seed Set Here
    srand(static_cast<unsigned int>(time(0)));
    
    //Variable Declarations 
    const int SIZE=50;                       //Gameboard size
    const int NBOATS=10;                     //Number of boats
    int gBoard[SIZE];                        //Array for gameboard
    int usrBrd[SIZE];                        //Array for users board which holds users boats
    int boats[NBOATS];                       //Array that holds value of boats
    int pBoats[NBOATS];                      //Array that holds value of player boats
    int guess[SIZE];                         //Used to make sure computer does not guess a number twice
    int choice;                              //User choice of where to shoot on board
    int turn, maxTurn;                       //Used for the amount of turns and max turns in game
    bool loop;                               //Used for do while loop
    char start;                              //Used to start game 
 
    //Variable Initialization   
    maxTurn=50;                  //Max amount of turns 
    turn=1;                      //Player starts on turn 1
       
    //Mapping Process Inputs to Outputs
               
    //Display Outputs
    //Assigns random value to boats
    filBoat(boats, NBOATS, SIZE);
    
    //fill board 1-100
    fillBrd(gBoard, SIZE);
    
    //Fills user board
    fillBrd(usrBrd, SIZE);
    
    //Presents start screen and instructions        
    srtScrn(start);
    
     //Fills user boats
    usrBoat(pBoats, NBOATS, SIZE);
    
    //Displays both boards before any turns have been made
    dsplyBd(gBoard, SIZE, turn, maxTurn);
    dsplyBd(usrBrd, pBoats, SIZE, NBOATS);
    
    do{
        //Gameplay function that determines a hit or a miss
        hitMiss(gBoard, boats, SIZE, NBOATS, choice);
        
        //Display GameBoard
        dsplyBd(gBoard, SIZE, turn, maxTurn);
        
        //Computers Choice
        cmpChce(usrBrd, pBoats, guess, SIZE, NBOATS);
        
        //Displays user board and boats
        dsplyBd(usrBrd, pBoats, SIZE, NBOATS);
       
        //Function either returns false or true
        loop=winLose(boats, NBOATS, turn, maxTurn, loop);
        
    }while(loop);
    
    
    //Clean Up
    
    //Exit stage right!
    return 0;
}

//Displays start screen and instructions
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
            cout<<"Turn#: "<<turn<<"                     ";
            cout<<"Max Turn#: "<<maxTurn<<endl;
            cout<<setw(27)<<"Computer Board"<<endl;
        }
        if(array[n]==0)
            cout<<"   "<<'x';
        else if(array[n]=='o')
            cout<<"   "<<'o';
        else if(array[n]<10)
            cout<<"   "<<array[n];
        else 
            cout<<"  "<<array[n];
        if(n%10==(10-1))
            cout<<endl;    
    }
    cout<<endl;
}

//Displays user board
void dsplyBd(int a[], int boat[], int SIZE, int NBOATS){
    cout<<endl;
    cout<<"Your boats#: ";
    for(int i=0; i<NBOATS; i++){
        if(i==NBOATS-1)
            cout<<boat[i];
        else 
            cout<<boat[i]<<", ";
    }
    cout<<endl;
    for (int n=0; n<SIZE; n++){
        if(n==0){
            cout<<setw(27)<<"User Board"<<endl;
        }
        if(a[n]==0)
            cout<<"   "<<'x';
        else if(a[n]=='o')
            cout<<"   "<<'o';
        else if(a[n]<10)
            cout<<"   "<<a[n];
        else 
            cout<<"  "<<a[n];
        if(n%10==(10-1))
            cout<<endl;    
    }
}

//Adds values to boats 1-5
void filBoat(int a[], int NBOATS, int SIZE){
    for(int n=0; n<NBOATS; n++){
        a[n]=rand()%SIZE+1;
    }
    for(int i=0; i<=10000; i++){
        for(int n=0; n<NBOATS; n++){
            for(int j=0; j<NBOATS; j++){
                if(a[n]==a[j])
                    a[n]=rand()%SIZE+1;
            }
        }
    }
    /*for(int j=0; j<NBOATS; j++){
        cout<<a[j]<<"   ";
    }*/
}

//Holds value for user boats
void usrBoat(int a[], int NBOATS, int SIZE){
    cout<<"Please enter "<<NBOATS<<" values for your boats from 1-"<<SIZE<<endl;
    for(int n=0; n<NBOATS; n++){
        cin>>a[n];
        while(a[n]>SIZE||a[n]<1){
            cout<<a[n]<<" is not between 1 and "<<SIZE<<endl;
            cout<<"Please enter a new number"<<endl;
            cin>>a[n];
        }
    }
}

//Function informs user whether or not they got a hit or a miss
void hitMiss(int gBoard[], int boats[], int SIZE, int NBOATS, int choice){
    cout<<endl<<"Which spot do you wanna shoot"<<endl;
    cin>>choice;
    while(choice<1||choice>SIZE){     //Input validation for keeping choice input between 1-30
        cout<<"Please pick a number between 1-"<<SIZE<<endl;
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
        cout<<"-------------------------------------------"<<endl
            <<"You got a hit"<<endl;
        for(int i=0; i<SIZE; i++){
            if(choice==gBoard[i]){
                gBoard[i]=0;
            }
        }   
    }
    if(hit==false){
        for(int j=0; j<SIZE; j++){
            if(choice==gBoard[j]){
                cout<<"-------------------------------------------"<<endl
                    <<"That was a miss"<<endl;
                static_cast<char>(gBoard[j]);
                gBoard[j]='o';
            }
        }
    }
}

//Used or the computers turn
void cmpChce(int usrBrd[], int pBoats[], int guess[], int SIZE, int NBOATS){
    bool hit=false;
    int cChoice=rand()%SIZE+1;
    
    //Prevents computer from choosing same number 
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            if(cChoice==guess[j])
                cChoice=rand()%SIZE+1;
        }
    }
    for(int n=0; n<NBOATS; n++){
        if(cChoice==pBoats[n]){
           pBoats[n]=0;
            hit=true;
        }
    }
    if(hit==true){
        cout<<"-------------------------------------------"<<endl
            <<"Enemy got a hit at "<<cChoice;
            
        for(int i=0; i<SIZE; i++){
            if(cChoice==usrBrd[i]){
                guess[i]=usrBrd[i];
                usrBrd[i]=0;
            }
        }   
    }
    if(hit==false){
        cout <<"-------------------------------------------"<<endl
              <<"Enemy missed their shot at "<<cChoice;      
        for(int j=0; j<SIZE; j++){
            if(cChoice==usrBrd[j]){
                guess[j]=usrBrd[j];
                static_cast<char>(usrBrd[j]);
                usrBrd[j]='o';
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