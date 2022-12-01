/*--------------------------*/
/* Omar Mohamed Atia Shehab */
/* Date:   November 27, 2022  */
/*       Assignment3        */
/* Time Division Multiple Access */
#include<iostream>
#include <string>
#include <cmath>
using namespace std;
#define SIZE 10000 //for number of bts
#define SLOTS 8 //for slots of ms
 
class MobileStation; //forward declaration of the mobile station class
class BaseStationController; //forward declaration of the base station controller class
//--------------------BaseTranscieverStation----------------------//
class BaseTranscieverStation {
private:
 int numOfMS;
 static int ID_BTS;
 int GeneratedID;
 int numOfBTS;
 double position[3];
 MobileStation *numOfOccupiedSlots[8]; // number of MSs occupied the BTS
public:
 //default constructor
 BaseTranscieverStation(){
   position[0], position[1], position[2] = 0;
   numOfMS = 0;
   ID_BTS++;
   GeneratedID = ID_BTS;
 };
 //Parameterized constructor
 BaseTranscieverStation(double x, double y, double z) {
   position[0] = x;
   position[1] = y;
   position[2] = z;
   numOfMS=0;
   ID_BTS++;
   GeneratedID = ID_BTS;
 }
 //getter to return the pos of the BTS
 double* getPosBTS() {
   return position;
 }
 int getID_BTS() { return GeneratedID; } //getter to return the ID of each BTS
 bool connectMSToBTS(MobileStation *newMS); // declaration of connectMSTo BTS function which checks if the MS can connect or not
 void numberOfDevices(); // void function to print the number of devices in the BTS
 void leave_MS_BTS(MobileStation* newMS);//the declaration of the leave function that is called when one of the MSs move to anther BTS

int num_of_freeslots(){
   return (SLOTS - numOfMS); //function that returns the remaining number of slots
 }
 void print() {
   cout << "The BTS ID: " << getID_BTS() << endl;
   cout << "BTS Position: " << endl;
   cout << "X: " << position[0] << " Y: " << position[1] << " Z: " << position[2] << endl;
   cout<<"number of free slots: "<<num_of_freeslots()<<endl;
 }
 ~BaseTranscieverStation(){
  
 }
};
void BaseTranscieverStation::numberOfDevices() {
 cout << "Number of connected MS: " << GeneratedID << endl;
}
int BaseTranscieverStation::ID_BTS = 0;//intializing the number of ID_BTS to 0
 
//----------------MobileStation-----------------------//
class MobileStation {
private:
 static int ID;
 int GeneratedID;
 double pos[SIZE];
 BaseTranscieverStation *connectedBTS;//referance of the BTS class that will check if the MS is connected to a specific BTS or not
 BaseStationController *connectedBSC;//referance of the BSC class that will check if the MS is connected to a specific BSC or not
public:
 //default constructor
 MobileStation() {
   ID++;
   GeneratedID = ID;
   pos[0] = pos[1] = pos[2] = 0;
 }//Parameterized constructor
 MobileStation(double x, double y, double z) {
   ID++;
   GeneratedID = ID;
   pos[0] = x;
   pos[1] = y;
   pos[2] = z;
 }
 int getID() { return GeneratedID; } // a getter to get the the ID of the MS
 double *getPos() { return pos; } // a getter to get the position of the MS
 void updateActiveBTS(BaseStationController* BSC, int numofBTS); // the update function that will be called each time the MS moves
 void connected_BTS(BaseTranscieverStation *BTS) {
   connectedBTS = BTS; // assigning the connectedBTs to the BTs we will get from the function
 }
 static void numberOfDevices() {
   cout << "The number of MS devices is: " << ID << endl;
 }
 void move(double x, double y, double z, BaseStationController* nn, int n); // the move function that changes the position of the MS and calls the function update and leave
 //function to print the position
 void printPos() {
   cout << "X: " << pos[0] << " Y: " << pos[1] << " Z: " << pos[2] << endl;
 }//destructor
 ~MobileStation(){
  
 }
};
int MobileStation::ID = 0;//intializing the value of the id to 0
 
//-------------------BaseStationController-----------------------------//
class BaseStationController {
private:
 BaseTranscieverStation *numOfBTS; // an array of objects to get the number of BTSs
 static int numBTS;
public:
 BaseStationController(){
   numBTS = 0;
   numOfBTS= new BaseTranscieverStation[SIZE]; //intializing the array of objects
 }//function to add the BTSs to the BSC
 void Add_BTS(BaseTranscieverStation BTS) {
   if (numBTS < SIZE) {//checking if there is a place to add the the bts
     numOfBTS[numBTS] = BTS;
     numBTS++;
   } else
     cout << "No Space for more BTSs as the max number of BTSs is "<<SIZE << endl; // message if there is no space for new bts
 }
 void PrintInfo(); // function to print all the information of each bts
 BaseTranscieverStation* getAllBTS() {//function to get the btss
   return numOfBTS;
 }
 static int getNUM(){ // funciton that returns number of bts
   return numBTS;
 }
 //destructor of the bsc
 ~BaseStationController(){
 
 }
};
int BaseStationController::numBTS = 0; // intializing the number of bts
//function that connects the MS to BTS
bool BaseTranscieverStation::connectMSToBTS(MobileStation *newMS) {
 if (numOfMS >= SLOTS) {// checking if there are free slots or not
   return false;
 }else{
   numOfOccupiedSlots[numOfMS] = newMS; //assigning the current position of the array of objects to the new MS
   newMS->connected_BTS(this);//passing the object to the function to assign it to the BTS
   numOfMS++;//incrementing the num of MS because we added a new one
   cout << "MS "<<newMS->getID()<<" to BTS with ID: " << GeneratedID <<endl;
   return true;
 }
}
void BaseTranscieverStation::leave_MS_BTS(MobileStation *newMS){
   bool check = false;
   //looping through the objects of the bts
   for(int i = 0; i < (8-num_of_freeslots()); i++ ){
     if(newMS == numOfOccupiedSlots[i]){ // if the newMS is equal to one of the occupied ms in the bts
       for(int j = 0; j < (8-num_of_freeslots()); j++){//loop through the occupied objects to shift its position
         
         numOfOccupiedSlots[j] = numOfOccupiedSlots[j+1];
       }
       numOfMS--; //decrement the number of the MSs
       check = true;
     }
   }
   if(!check){ // check if there are MSs in the BTS or not
     cout<<"No MS to leave"<<endl;
   }else{//printing a message about which MS left the bts
     cout<<"MS "<< newMS->getID() << " Left the BTS "<<this->getID_BTS()<<endl;
   }
}
void MobileStation::updateActiveBTS(BaseStationController* BSC, int numofBTS){
 double Dis = 0;
 int check = 0;
 BaseTranscieverStation* BTS = BSC->getAllBTS(); // getting all the BTSs
 double min = 1000000000; // assigning a large number to compare it with the distance
 for (int i = 0; i < numofBTS; i++) {//looping through the number of objects to see if there is a free space to update the position of ms or not
   if(BTS[i].num_of_freeslots() == 0){//if there are no free space then ignore this bts
     continue;
   }
     Dis = sqrt(pow(pos[0] - (BTS[i].getPosBTS()[0]), 2) +
                pow(pos[1] - (BTS[i].getPosBTS()[1]), 2) +
                pow(pos[2] - (BTS[i].getPosBTS()[2]), 2));
     if (Dis < min) {
       min = Dis;
       check = i; //getting the index of the BTS
     }
 }//checking if the bts has free space or not
 if(BTS[check].connectMSToBTS(this) == false){
   cout<<"The BTS "<<BTS[check].getID_BTS()<<" is full\n";
 }
}
void MobileStation::move(double x, double y, double z, BaseStationController* newBSC, int n) {
 pos[0] = x;
 pos[1] = y;
 pos[2] = z;
 cout<<"MS "<<getID()<<" Moved to: ("<<pos[0]<<" , "<<pos[1]<<" , "<<pos[2]<<")"<<endl;
 connectedBTS->leave_MS_BTS(this);//checking if it has left the current bts or not
 this->updateActiveBTS(newBSC, n);// updating the position again 
}
//print the information of the btss
void BaseStationController::PrintInfo() {
 for (int i = 0; i < numBTS; i++) {
   numOfBTS[i].print();
   cout << endl;
 }
}
 
//-----------------MAIN----------------//
int main() {
 MobileStation* ms1 = new MobileStation(10,11,12);
 MobileStation* ms2 = new MobileStation(11,13,12);
 MobileStation* ms3 = new MobileStation(19,17,11);
 MobileStation* ms4 = new MobileStation(4,3,5);
 MobileStation* ms5 = new MobileStation(5,4,3);
 MobileStation* ms6 = new MobileStation(3,4,5);
 MobileStation* ms7 = new MobileStation(0,1,0);
 MobileStation* ms8 = new MobileStation(0,0,1);
 MobileStation* ms9 = new MobileStation(1,0,1);
 MobileStation* ms10 = new MobileStation(0,1,1);
 MobileStation* ms11 = new MobileStation(0,2,1);
 MobileStation* ms12 = new MobileStation(3,2,1);
 MobileStation* ms13 = new MobileStation(10,2,1);
 MobileStation* ms14 = new MobileStation(5,12,2);
 MobileStation* ms15 = new MobileStation(2,3,1);
 MobileStation* ms16 = new MobileStation(3,3,5);
 MobileStation* ms17 = new MobileStation(5,4,2);
 
 BaseTranscieverStation bts1(10,11,12); BaseTranscieverStation bts2(-1,2,13);
 BaseTranscieverStation bts3(9,8,10); BaseTranscieverStation bts4(19,18,10);
 BaseTranscieverStation bts5(30,30,10);
 
 BaseStationController* bsc = new BaseStationController;
 bsc->Add_BTS(bts1); bsc->Add_BTS(bts2);
 bsc->Add_BTS(bts3); bsc->Add_BTS(bts4);
 bsc->Add_BTS(bts5);
 ms1->updateActiveBTS(bsc, bsc->getNUM()); ms1->move(18,18,10, bsc, bsc->getNUM());
 ms2->updateActiveBTS(bsc, bsc->getNUM());
 ms3->updateActiveBTS(bsc, bsc->getNUM()); ms3->move(10,11,12, bsc, bsc->getNUM());
 ms4->updateActiveBTS(bsc, bsc->getNUM());
 ms5->updateActiveBTS(bsc, bsc->getNUM());
 ms6->updateActiveBTS(bsc, bsc->getNUM());
 ms7->updateActiveBTS(bsc, bsc->getNUM());
 ms8->updateActiveBTS(bsc, bsc->getNUM());
 ms9->updateActiveBTS(bsc, bsc->getNUM()); ms5->move(21,31,11, bsc, bsc->getNUM());
 ms10->updateActiveBTS(bsc, bsc->getNUM());
 ms11->updateActiveBTS(bsc, bsc->getNUM());
 ms12->updateActiveBTS(bsc, bsc->getNUM());
 ms13->updateActiveBTS(bsc, bsc->getNUM());
 ms14->updateActiveBTS(bsc, bsc->getNUM());
 ms15->updateActiveBTS(bsc, bsc->getNUM());
 ms16->updateActiveBTS(bsc, bsc->getNUM());
 ms17->updateActiveBTS(bsc, bsc->getNUM());
 cout<<endl;
  
 bsc->PrintInfo();
  // deallocate the classes
 delete ms1; delete ms2;
 delete ms3; delete ms4;
 delete ms5; delete ms6;
 delete ms7; delete ms8;
 delete ms9; delete ms10;
 delete ms12; delete ms13;
 delete ms14; delete ms15;
 delete ms16; delete bsc;
 return 0;
}
