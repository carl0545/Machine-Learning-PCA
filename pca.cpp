/*
* Dylan Carlson
* Machine Learning
* Assignment 5
* 4/2018
*/

#include <iostream>
#include "mat.h"

using namespace std;

void centerMatrix(Matrix, Matrix*); //Centers the Matrix


int main(int argc, char *argv[]){
  //////DECLARATIONS//////
  Matrix input_ppm; //input .ppm matrix
  Matrix center;
  Matrix covariance;
  Matrix eigen_vectors;
  Matrix eigen_values;

  int k_ev;

  k_ev = 50; //testing purposes delete later

  //////INPUT////////
  input_ppm.readImagePpm(argv[1], "ppm"); //read in .ppm file to matrix


  //////CENTER MATRIX/////
  center = new Matrix(input_ppm); //creates a copy of input matrix to use for the centered matrix

  centerMatrix(input_ppm, &center); //centers the 'center' matrix

  //////COVARIANCE MATRIX/////
  covariance = Matrix(Matrix(center).cov()); //Computes the covariance matrix

  /////COMPUTE EIGENVALUES AND EIGENVECTORS OF M//////
  eigen_vectors = new Matrix(covariance); //Copies the covariance matrix into eigen_vectors

  eigen_values = Matrix(eigen_vectors.eigenSystem()); //Creates the eigenvalues and eigen_vectors

  //////NORMALIZE EIGEN VECTORS/////////
  eigen_vectors.normalizeCols();

  ////NARROW THE EIGEN SYSTEM TO ONLY KEEP K LARGEST/////
  eigen_values.narrow(k_ev);
  eigen_vectors.narrow(k_ev);

  //////TRANSLATE THE NORMALIZED DATA//////










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
