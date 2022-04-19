#include <iostream>
#include <fstream>
#include <sstream>
#include "ChainCode.h"

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
    int *propHeader = new int[11]();

    int number1;
    string line1;
    istringstream iss1;

    if(propFile.good()){
        int j = 0;
        
        while(!propFile.eof()){
            getline(propFile, line1);
            
            iss1.clear();
            iss1.str(line1);


            while (iss1 >> number1){
                propHeader[j] = number1;
                j++;
            }
        }

   }

    for(int i = 0; i < 11; i++){
        cout << propHeader[i] << endl;
    }






    return 0;
}