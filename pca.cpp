/*
* Dylan Carlson
* Machine Learning
* Assignment 5
* 4/2018
*/

#include <iostream>
#include <fstream>
#include "mat.h"

using namespace std;

void centerMatrix(Matrix, Matrix*); //Centers the Matrix
void uncenterMatrix(Matrix*, Matrix, Matrix); //Uncenters the Matrix

int main(int argc, char *argv[]){
  //////DECLARATIONS//////
  Matrix input_ppm; //input .ppm matrix
  Matrix center;
  Matrix mean_i;
  Matrix std_i;
  Matrix covariance;
  Matrix eigen_vectors;
  Matrix eigen_values;
  Matrix translated_data;
  Matrix recovered_data;

  double difference;

  int k_ev;


  //////INPUT////////
  cin >> k_ev;
  input_ppm.readImagePpm("", "ppm"); //read in .ppm file to matrix
  mean_i = Matrix(Matrix(input_ppm).meanVec());
  std_i = Matrix(Matrix(input_ppm).stddevVec());

  cout << "size of Pic: " << input_ppm.numRows() << " X " << input_ppm.numCols() << endl;
  //////CENTER MATRIX/////
  center = new Matrix(input_ppm); //creates a copy of input matrix to use for the centered matrix

  centerMatrix(input_ppm, &center); //centers the 'center' matrix


  //////COVARIANCE MATRIX/////
  covariance = Matrix(Matrix(center).cov()); //Computes the covariance matrix

  /////COMPUTE EIGENVALUES AND EIGENVECTORS OF M//////
  eigen_vectors = new Matrix(covariance); //Copies the covariance matrix into eigen_vectors

  eigen_values = Matrix(eigen_vectors.eigenSystem()); //Creates the eigenvalues and eigen_vectors


  cout << "size of EigenValues: " << eigen_values.numRows() << " X " << eigen_values.numCols() << endl;
  ////NARROW THE EIGEN SYSTEM TO ONLY KEEP K LARGEST/////
  eigen_values.narrow(k_ev);
  eigen_vectors.shorten(k_ev);

  //////TRANSLATE THE NORMALIZED DATA//////
  Matrix center_copy = new Matrix(center);
  Matrix eigenVec_copy = new Matrix(eigen_vectors);


  eigenVec_copy.transposeSelf();

  translated_data = Matrix(center_copy.dot(eigenVec_copy));

  cout << "size of Encoded: " << translated_data.numRows() << " X " << translated_data.numCols() << endl;
  //////RECOVER DATA FROM COMPRESSED IMAGE/////
  recovered_data = Matrix(translated_data.dot(eigen_vectors));

  uncenterMatrix(&recovered_data, mean_i, std_i);

  ///////RECOVERED DATA ANALYSIS//////
  difference = (input_ppm.dist2(recovered_data))/(input_ppm.numRows() * input_ppm.numCols());

  cout << "DIST: " << difference << endl;;

  ////SAVE NEW PPM FILE/////
  recovered_data.writeImagePpm("Z-After.ppm", "output");

}

/*
*Centers the center matrix using Z-Score method
*/
void centerMatrix(Matrix input, Matrix *center){
  Matrix mean;
  Matrix std;

  mean = Matrix(Matrix(input).meanVec());
  std = Matrix(Matrix(input).stddevVec());

  for(int r = 0; r < center->numRows(); r++){
    for(int c = 0; c < center->numCols(); c++){
      double zscore;
      zscore = ((input.get(r,c) - mean.get(0,c))/std.get(0,c));
      center->set(r,c, zscore);
    }
  }


}

/*
*Uncenters the centered matrix using the previous inputs Mean and std
*/
void uncenterMatrix(Matrix *recovered, Matrix mean, Matrix std){
  Matrix recov_copy = new Matrix(recovered);

  for(int r = 0; r < recovered->numRows(); r++){
    for(int c = 0; c < recovered->numCols(); c++){
      double redo;
      redo = ((recov_copy.get(r,c) * std.get(0,c)) + mean.get(0,c));
      recovered->set(r,c, redo);
    }
  }

}
