
#include <iostream>
#include <fstream>
#include <math.h>
#include <cstring>
#include <inttypes.h>
#include<vector>
#include<sstream>

using namespace std ;

const int ROWS = 28;
const int COLS = 28;

const int Training_size = 60000 ; 

float ArrayData[Training_size][800] ;
 

int main() {
	
//open mnist_train.csv and read into array 
fstream DataFile;
DataFile.open("mnist_train.csv" , ios::in);
	if(!DataFile.good()){
		cerr << "Error opening Data file" << endl;
		exit(EXIT_FAILURE);
	}
      string line;
	getline(DataFile , line);

    for(int row = 0 ; row <= Training_size ; ++row){
  
        getline(DataFile, line);
		//cout << "getline complete " << line << endl; 
        if ( !DataFile.good() ){
		cerr << "DataFile not good" << endl ;
            break;
		}
        std::stringstream iss(line);

        for (int col = 0; col <= 800; ++col)
        {
		//if(col%200 == 0) cout << "col = " << col << endl ;
            std::string val;
            std::getline(iss, val, ',');
            if ( !iss.good() )
                break;

            std::stringstream convertor(val);
            convertor >> ArrayData[row][col];
			

			
		
        }
		if(row% 2000 == 0) cout << "row = " << row << endl ;
			
		

    }

cout << "data read into array" << endl ; 

fstream outputFile;
remove("Extracted_Train.csv");
outputFile.open("Extracted_Train.csv" , ios::app);
if(!outputFile.good()){
	cerr << "Error opening Extracted_Train.csv" << endl;
		exit(EXIT_FAILURE);
	}


for(int Line = 0 ; Line <= Training_size ; ++Line){ 
	int row = 0 , col = 0 , i = 0 , Value = 0; 
	float ImageTotal = 0 , ImageAverage = 0 ; 
	
//put large array into smaller array for the image selected.
	int ArrayImage[ROWS][COLS];
	int j = 0 , k = 0 ; 
	for(i=0 ; i <= ROWS*COLS+2 ; ++i){
		ArrayImage[k][j] = ArrayData[Line][i];
		ImageTotal = ImageTotal + ArrayImage[k][j] ; //sum values in the image to find average
		++j ; 
		if(j >= COLS) {
			j = 0;
			k++ ; 
			//cout << " k = " << k << endl;  
		}
	}
	Value = ArrayData[Line][ROWS*COLS] ; //number the image represents
	ImageAverage = ImageTotal /(ROWS*COLS) ; //average value of all pixels in image

//zone image	
	float sum4x4 = 0 ; 
	for(i=1 ; i <=14 ; ++i){
		sum4x4 = 0 ; 
		for(j=1 ; j <=14 ; ++j){
			sum4x4 = ArrayImage[2*i-2][2*j-2] + ArrayImage[2*i-2][2*j-1] ;
			sum4x4 = sum4x4 + ArrayImage[2*i-1][2*j-2] + ArrayImage[2*i-1][2*j-1] ;			
			if(sum4x4 > ImageAverage*4){
				outputFile << "1," ;
			} else {
				outputFile << "0," ;
			}
		}
	}
	outputFile << Value << endl ; 
	if(Line%2000 == 0) cout << "Line = " << Line  << " Value = " << Value << endl ;
}

cout << "feature extraction complete" <<endl ;
outputFile.close();	
DataFile.close();
return 0 ;
}	