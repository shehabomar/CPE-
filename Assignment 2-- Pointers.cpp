/*--------------------------*/
/* Omar Mohamed Atia Shehab */
/* Date:   November 13, 2022  */
/*       Assignment2        */
/* Image Features Extraction using GLCM */
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
// Function to find the Maximum number in the Grey Scale Matrix
int max_ArrNumber(int **arr, int rows, int cols) {
  int max_num = arr[0][0]; 
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (arr[i][j] > max_num) {
        max_num = arr[i][j]; // assigning the max number to the variable
      }
    }
  }
  return max_num;
}
// Creating the GLCM Matrix
void GLCM_matrix(double **glcm, int **arr, int rows, int cols, int MAX_NUM) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols - 1; j++) {
      int x = arr[i][j]; // rows index of the new created number in the GLCM
      int y = arr[i][j + 1]; // columns index of the new created number in the GLCM
      glcm[x][y]++; // incrementing the value of the array by one if it exists
    }
  }
}
// function to calculate the normalized array based on the values of the GLCM array
void normalize_GLCM(double **normalizedArr, double **glcm, int **arr, int rows, int cols, int MAX_NUM) {
  // summation of the array
  double sum = 0;
  for (int i = 0; i < MAX_NUM; ++i) {
    for (int j = 0; j < MAX_NUM; ++j) {
      sum += glcm[i][j]; // computing the summation of the array
    }
  }
  for (int i = 0; i < MAX_NUM; ++i) {
    for (int j = 0; j < MAX_NUM; ++j) {
      normalizedArr[i][j] = (glcm[i][j] / sum); // dividing numbers of the array with the summation
    }
  }
}
// Statistical Parameters of the texture
double Contrast(double **normalizedArr, int MAX_NUM) {
  double contrast = 0;
  for (int i = 0; i < MAX_NUM; ++i) {
    for (int j = 0; j < MAX_NUM; ++j) {
      // contrast equals the summation of the absolute value squared of the difference in the indexe multiply the value of in the glcm array
      contrast += (pow(abs(i - j), 2) * normalizedArr[i][j]);
    }
  }
  return contrast;
}
double Energy(double **normalizedArr, int MAX_NUM) {
  double energy = 0;
  for (int i = 0; i < MAX_NUM; i++) {
    for (int j = 0; j < MAX_NUM; j++) {
      // energy equals the summation of the values of the glcm matrix squared
      energy += pow(normalizedArr[i][j], 2);
    }
  }
  return energy;
}
double Homogeneity(double **normalizedArr, int MAX_NUM) {
  double homo = 0;
  for (int i = 0; i < MAX_NUM; i++) {
    for (int j = 0; j < MAX_NUM; j++) {
      homo += (normalizedArr[i][j] / (1 + pow(abs(i - j), 2)));
    }
  }
  return homo;
}
int main() {
  // The choice the user has to choose, the rows and columns of the grey scale array
  // intializing the grayscale array and the maximum number of the array variable
  int choice, rows, cols, **arr, MAX_NUM ,check = 0;
  string filenameIn, filenameOut; // files to store the data of the grey scale and print the results
  double **glcm, **normalizedArr; // intrializing the glcm matrix and the normalized matrix 
  ifstream infile(filenameIn);//intializing the input file
  // Displaying the menu function serveral times for the user to print the results of what he chooses
Menu:
  // calling the menu function
  cout << "1- Create and normalize the GLCM matrix. \n";
  cout << "2- Compute the statistical parameters of the texture. \n";
  cout << "3- Print the GLCM matrix. \n";
  cout << "4- Exit. \n";
  cout << "Enter a Number: \n";
  cin >> choice;
  if (choice == 1) {
    check++; // incrementing check varible to let the other processes to be created (GLCM, Normalized Matrixes)
    files:
    cout << "Please enter the name of the file: \n";
    cin >> filenameIn;
    ifstream infile(filenameIn);
    // checking if the file exists or not
    if (infile.fail()) {
      cout << "file failed to operate.. please enter again\n";
      goto files;
    }
    // geting the data of the matrix from the file
    infile >> cols >> rows;
    // Creatring the Grey Scale Matrix
    arr = new int *[rows];
    for (int i = 0; i < rows; i++) {
      arr[i] = new int[cols];
    }
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        infile >>arr[i][j]; // entering the values of the grey scale array from the file
      }
    }
    // assigning the value that the max function will return to a variable
    MAX_NUM = max_ArrNumber(arr, rows, cols);
    MAX_NUM++; // incrememting the value of the matrix to print till 8 columns and
               // rows
    // GLCM Array
    glcm = new double *[MAX_NUM];
    for (int i = 0; i < MAX_NUM; ++i) {
      glcm[i] = new double[MAX_NUM];
    }
    GLCM_matrix(glcm, arr, rows, cols, MAX_NUM); // calling the function here for the sake of creating the normalized Matrix
    normalizedArr = new double *[MAX_NUM];
    for (int i = 0; i < MAX_NUM; ++i) {
      normalizedArr[i] = new double[MAX_NUM];
    }
    // calling the function to create the normalized Matrix
    normalize_GLCM(normalizedArr, glcm, arr, rows, cols, MAX_NUM);
    cout << "The Normalized Matrix is created\n";
    goto Menu;
  } else if (choice == 2 && check != 0) {
    // computing the statistical parameters
    cout << "The Contrast: " << Contrast(normalizedArr, MAX_NUM) << "\n";
    cout << "The Energy: " << Energy(normalizedArr, MAX_NUM) << "\n";
    cout << "The Homogeneity: " << Homogeneity(normalizedArr, MAX_NUM) << "\n";
    goto Menu;
  } // when user chooses option 3
  else if (choice == 3 && check != 0) {
    // printing the matrix into file to display this matrix later
    for (int i = 0; i < MAX_NUM; ++i) {
      for (int j = 0; j < MAX_NUM; ++j) {
        cout << glcm[i][j] << " ";
      }
      cout << endl;
    }
    goto Menu;
  } else if (choice == 4 && check != 0) {
    // exiting the porgram
    cout << "Thanks for using the program....exit\n";
    // deallocating the greyscale Matrix
    for (int i = 0; i < rows; i++) {
      delete[] arr[i];
    }
    delete[] arr;
    // deallocating the GLCM matrix
    for (int i = 0; i < MAX_NUM; i++) {
      delete[] glcm[i];
    }
    delete[] glcm;
    // deallocating the normalized matrix
    for (int i = 0; i < MAX_NUM; i++) {
      delete[] normalizedArr[i];
    }
    delete[] normalizedArr;
  }else if(choice == 4 && check == 0){
    cout << "Thanks for using the program....exit\n";
  } else {
    // if the user enetered an invalid input
    if(check == 0){
      cout<<"enter 1 please: \n";
    }else if(choice > 4){
      cout << "Invalid Input, enter again: \n";
    }
    goto Menu;
  }
  infile.close(); // closing the file of the input
  return 0;
}