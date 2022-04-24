#include <iostream>
#include <fstream>
#include <sstream>
#include "ChainCode.h"
#include "ChainCode.cpp"

using namespace std;

int main(int argc, char* argv[]){

    //get the label file 
    string label = argv[1];
    ifstream labelFile;
    labelFile.open(label);

    //get the prop file 
    string prop = argv[2];
    ifstream propFile;
    propFile.open(prop);

    //creating the chainCode file
    string chainCodeString = label + "_chainCode.txt";
    ofstream chainFile;
    chainFile.open(chainCodeString);

    //creating the boundary file
    string boundaryString = label + "_Boundary.txt";
    ofstream boundaryFile;
    boundaryFile.open(boundaryString);

    //get the numRows, numCols, minVal and maxVal from labelFile
    int *labelHeader = new int[4]();

    int number;
    string line;
    istringstream iss;

    if(labelFile.good()){
        getline(labelFile, line);

            iss.clear();
            iss.str(line);

            int i = 0;

            while (iss >> number){ // only used for collecting the values from the image header
                labelHeader[i] = number;
                i++;
            }
   }

    //get all property information from propFile
    int *propHeader = new int[6]();

    int number1;
    string line1;
    istringstream iss1;

    int numberOfCC = 0;

    if(propFile.good()){
     
        
        getline(propFile, line1); // we dont want to record the imageHeader again
        
        //while(!propFile.eof()){
            getline(propFile, line1);   //gets the Connected component stored in numberOfCC

            iss1.clear();
            iss1.str(line1);

            while (iss1 >> number1){
                numberOfCC = number;
                //propHeader[j] = number1;
                //j++;
            }

        }
//    }

   //dynamically allocate the CCArray: numRows+2 by numCols+2
   //dynamically allocate the imageArray and boundaryArray
   int numRows = labelHeader[0]+2;
   int numCols = labelHeader[1]+2;
   int **CCArray = new int*[numRows];
   int **imageArray = new int*[numRows];
   int **boundaryArray = new int*[numRows];

    for(int i = 0; i < numRows; i++){
       CCArray[i] = new int[numCols];
       imageArray[i] = new int[numCols];
       boundaryArray[i] = new int[numCols];
    }

    ChainCode ChainCodeObject(labelHeader[0], labelHeader[1], labelHeader[2], labelHeader[3],numberOfCC, imageArray, CCArray, boundaryArray);

    chainFile << labelHeader[0] << " " << labelHeader[1] << " " << labelHeader[2] << " " << labelHeader[3] << endl;
    chainFile << numberOfCC << endl;

    // //load image file into the imageArray
    ChainCodeObject.loadImage(labelFile);

    int j = 0;
    int counter = 0;

    // while(counter < numberOfCC){

        getline(propFile, line1);   //gets the label stored in propHeader[0]

                iss1.clear();
                iss1.str(line1);

                while (iss1 >> number1){
                    propHeader[j] = number1;
                    j++;
                }

                getline(propFile, line1);   //gets the number of pixels stored in propHeader[1]

                iss1.clear();
                iss1.str(line1);

                while (iss1 >> number1){
                    propHeader[j] = number1;
                    j++;
                }

                getline(propFile, line1);   //gets the minRow and minCol stored in propHeader[2] and propHeader[3] 

                iss1.clear();
                iss1.str(line1);

                while (iss1 >> number1){
                    propHeader[j] = number1;
                    j++;
                }

                getline(propFile, line1);   //gets the maxRow and maxCol stored in propHeader[4] and propHeader[5]

                iss1.clear();
                iss1.str(line1);

                while (iss1 >> number1){
                    propHeader[j] = number1;
                    j++;
                }

        ChainCodeObject.setCCProperty(propHeader[0], propHeader[1], propHeader[2], propHeader[3], propHeader[4], propHeader[5]);
        
        for(int i = 0; i < j; i++){
            propHeader[i] = 0;
        }
        j=0;

        ChainCodeObject.clearCCAry();
        ChainCodeObject.loadCCAry();
        ChainCodeObject.getChainCode(chainFile);
        // counter++;
    // }



    

    // ChainCodeObject.print();



  






    return 0;
}