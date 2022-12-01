/*--------------------------*/
/* Omar Mohamed Atia Shehab */
/* Date: October 9, 2022    */
/*       Assignment1        */
/* Aviation Safety program  */

#include<iostream>
#include<fstream>
#include<iomanip>
#include<cmath>

using namespace std;
int main(){
	//declaring variables 
	float tolerance;
	float x1, y1,z1; // coordinates of the first point(point on earth)
	float x2, y2, z2;// coordinates of the second point(point of plane) 
	float dis; //the distance between the two points 
	double time = 0; // the time that will be calculated after each process 
	bool valid = true;//a boolean value to be used for looping
	//looping to implement the process based on the value of "valid"
	while(valid){
		//printing the options for the user		
		cout<<"Choose your option:\n";
		cout<<"(1) Calculate the error between the two sensors recordings and saving in the error file\n"; 
		cout<<"(2) Display the error file information\n";
		cout<<"(3) Quit the program\n";
		//reading the input value that the user will enter
		int num;
		cin>>num;
		//checking if the user entered one
		if(num == 1){
			//declaring two variables as strings to be the name files from the user
			string name1 , name2;
			//asking the user to enter the names of the two files
			cout<<"Please Enter the Two file names"<<endl;
			//reading the input values of the two variables
			cin>>name1>>name2;
			//identifying files as input files for later use
			ifstream file1;
			// opening the files with names given by the user
			file1.open(name1);
			ifstream file2;
			file2.open(name2);		
		//checking if they exist or not
		if(file1.fail() || file2.fail()){
			//printing error message if the files failed
			cout<<"Error in displaying the files\nplease try again\n";
			//reading the names entered by the user
			cin>>name1>>name2;	
		}
		//declaring a err as output file 		
		ofstream err("Err.log");
		//checking if it failed or not
		if(err.fail()){
			//printing error message when the fles failed to open	
			cout<<"Error in displaying the file\n";
			exit(1);
		}	
		//Asking the user to enter the tolerance
		cout<<"Please Enter a non-negative tolerance: \n";
		//Reading the value of the tolerance
		cin>>tolerance;
		while(tolerance){
			if(tolerance > 0)
				break;
			cout<<"please enter a non-negative tolerance: \n";
			cin>>tolerance;
		}
		
		//setting the table of the data to be printed
		cout<<setw(10)<<"Distance:"<<setw(10)<<"Time: "<<endl;
		//looping to the end of the file to get the data stored there
		while(!file1.eof() && !file2.eof()){
				//readint the coordinates from the files
				file1>>x1>>y1>>z1;
				file2>>x2>>y2>>z2;
				//calculating the distance 
				dis = sqrt(pow((x1-x2),2)+pow((y1-y2),2)+pow((z1-z2),2));
				//checking if the distance is greater than tolerance or not
				if(dis >  tolerance){
					//incrementing the time by quarter 
					time += 0.25;
					//printing the results in the error file
					err<<dis<<setw(10)<<time<<endl;	
					//printing the results in the consol
					cout<<setw(10)<<dis<<setw(10)<<time<<endl;				
				}
			}
			//assigning false to valid variable to stop the loop
			valid = false;
		}//when the user chooses number "2"
		else if(num == 2){
			//changing the stream of error file to be an input file
			ifstream display("Err.log");
			//checking if the file failed to open
			if(display.fail()){
				//printing error message
				cout<<"Failed to open the files\n";
			}
			//declaring two variables one for distance and one for time
			double number,sec;
			//looping through the files to get the data from it
			while(display>>number>>sec){
				cout<<setw(5)<<number<<setw(5)<<sec<<endl;
			}
			break;
		}//when user chooses option 3
		else if(num == 3){
			cout<<"Quitted"<<endl;
			valid = false;
		}else{
			cout<<"Invalid input, please Enter a correct number"<<endl;
			cout<<"(1) Calculate the error between the two sensors recordings and saving in the error file\n"; 
			cout<<"(2) Display the error file information\n";
			cout<<"(3) Quit the program\n";
			cin>>num;
		}
	}
	return 0;
}