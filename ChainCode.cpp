#include "ChainCode.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

//constructor
ChainCode::ChainCode(int ImageRows, int ImageColumns, int ImageMin, int ImageMax, int numOfCC, int **image, int **cc, int** boundary){
    numRows = ImageRows;
    numCols = ImageColumns;
    minVal = ImageMin;
    maxVal = ImageMax;

    numCC = numOfCC;

    // CC.label = label;
    // CC.numPixels = pixels;
    // CC.minRow = minR;
    // CC.minCol = minC;
    // CC.maxRow = maxR;
    // CC.maxCol = maxC;

    imageAry = image;
    CCAry = cc;
    boundaryAry = boundary;

    zeroTable[0] = 6; 
    zeroTable[1] = 0;
    zeroTable[2] = 0;
    zeroTable[3] = 2;
    zeroTable[4] = 2;
    zeroTable[5] = 4;
    zeroTable[7] = 4;
    zeroTable[8] = 6;
}

//load the label file into the imageArray starting at (1,1) position
void ChainCode::loadImage(ifstream& labelFile){

    //variables used to obtain the values from the inFile
    string line;
    istringstream iss;
    int number; 

    int rows = 1;
    int columns = 1;

    if(labelFile.is_open()){
        while(!labelFile.eof()){
            getline(labelFile, line);

            iss.clear();
            iss.str(line);
            
            while(iss >> number){ 
              imageAry[rows][columns] = number;
              columns++;
            }
            rows++;
            columns = 1;
        }                   
    }

}

//this zeros out the CCArry
void ChainCode::clearCCAry(){
    for(int i = 0; i < numRows + 2; i++){
        for(int j = 0; j < numCols + 2; j++){
            CCAry[i][j] = 0;
        }
    }
}

//load the imageArray of the specified label into the CCArray
void ChainCode::loadCCAry(){
    for(int i = 0; i < numRows + 2; i++){
        for(int j = 0; j < numCols + 2; j++){
            if(imageAry[i][j] == CC.label){
                CCAry[i][j] = imageAry[i][j];
            }
        }
    }

} 

void ChainCode::getChainCode(ofstream& ChainCodeFile){

    int label = CC.label;
    bool foundFirst = false;

    //we want to store the starting position of the pixel that is equal to the label
    
    for(int i = 0; i < numRows + 2; i++){
        for(int j = 0; j < numCols + 2; j++){
            if(CCAry[i][j] == CC.label && !foundFirst){ //means we encountered the first starting pixel
                startP.row = i;
                startP.col = j;

                currentP.row = i;
                currentP.col = j;

                lastQ = 4;

                foundFirst = true;
            }
        }
    }
    
    while((currentP.row != startP.row && currentP.row != currentP.col) || foundFirst){
        nextQ = (lastQ + 1) % 8;
        PChainDir = findNextP(currentP, nextQ);
        nextP.row = neighborCoord[PChainDir].row;
        nextP.col = neighborCoord[PChainDir].col;

        // currentP.row = currentP.row * -1;
        // currentP.col = currentP.col * -1;

        CCAry[currentP.row][currentP.col] = CCAry[currentP.row][currentP.col] * -1;

        ChainCodeFile << PChainDir << " ";

        if(PChainDir == 0){
            lastQ = zeroTable[7];
        }else{
            lastQ = zeroTable[PChainDir-1];
        }

        currentP.row = nextP.row;
        currentP.col = nextP.col;

        foundFirst = false;
    }


}

int ChainCode::findNextP(Point currP, int lastQ){

    cout << "inside find nextP" << endl;

    loadNeighBors(currentP);
    
    int index = lastQ;
    bool found = false;

    int chainDir = 0;
    
    int iRow = neighborCoord[index].row;
    int jCol = neighborCoord[index].col;

    // cout << "index " << index << endl;
    // cout << "iRow " << iRow << endl;
    // cout << "jCol " << jCol << endl;
    // while(iRow < numRows + 2){
    //     while(jCol < numCols + 2){
            while(found != true){
                iRow = neighborCoord[index].row;
                jCol = neighborCoord[index].col;

                if(imageAry[iRow][jCol] == CC.label){
                    chainDir = index;
                    found = true;
                }
                index = (index + 1) % 8;
            }
    //     }
    // }

    
    
    return chainDir;
} 



void ChainCode::loadNeighBors(Point current){
    //we are going to store the x and y coordinates of the current pixel's neighbors

    //direction 0
    coordOffset[0].row = 0;
    coordOffset[0].col = 1;

    //direction 1
    coordOffset[1].row = -1;
    coordOffset[1].col = 1;

    //direction 2
    coordOffset[2].row = -1;
    coordOffset[2].col = 0;

    //direction 3
    coordOffset[3].row = -1;
    coordOffset[3].col = -1;

    //direction 4
    coordOffset[4].row = 0;
    coordOffset[4].col = -1;

    //direction 5
    coordOffset[5].row = 1;
    coordOffset[5].col = -1;

    //direction 6
    coordOffset[6].row = 1;
    coordOffset[6].col = 0;

    //direction 7
    coordOffset[7].row = 1;
    coordOffset[7].col = 1;

    //storing the x and y coordinates in the neighborCoord array
    neighborCoord[0].row = coordOffset[0].row + current.row;
    neighborCoord[0].col = coordOffset[0].col + current.col;

    neighborCoord[1].row = coordOffset[1].row + current.row;
    neighborCoord[1].col = coordOffset[1].col + current.col;

    neighborCoord[2].row = coordOffset[2].row + current.row;
    neighborCoord[2].col = coordOffset[2].col + current.col;

    neighborCoord[3].row = coordOffset[3].row + current.row;
    neighborCoord[3].col = coordOffset[3].col + current.col;

    neighborCoord[4].row = coordOffset[4].row + current.row;
    neighborCoord[4].col = coordOffset[4].col + current.col;

    neighborCoord[5].row = coordOffset[5].row + current.row;
    neighborCoord[5].col = coordOffset[5].col + current.col;

    neighborCoord[6].row = coordOffset[6].row + current.row;
    neighborCoord[6].col = coordOffset[6].col + current.col;

    neighborCoord[7].row = coordOffset[7].row + current.row;
    neighborCoord[7].col = coordOffset[7].col + current.col;

}

void ChainCode::setCCProperty(int label, int numPixels, int minRow, int minCol, int maxRow, int maxCol){
    CC.label = label;
    CC.numPixels = numPixels;
    CC.minRow = minRow;
    CC.minCol = minCol;
    CC.maxRow = maxRow;
    CC.maxCol = maxCol;
}


void ChainCode::print(){

    // for(int i = 0; i < numRows+2; i++){
    //     for(int j = 0; j < numCols+2; j++){
    //         cout << CCAry[i][j] << " ";
    //     }
    //     cout << endl;
    // }
 
    // cout << "current p " << endl;
    // cout << currentP.row << " " << currentP.col << endl;

    cout << "neighbors array " << endl;
    for(int i = 0; i < 8; i++){
        cout << neighborCoord[i].row << " " << neighborCoord[i].col << endl;
    }

    // //cout << PChainDir << endl;

    // cout << "numRows " << numRows << endl;
    // cout << "numCols " << numCols << endl;
    // cout << "minVal " << minVal << endl;
    // cout << "maxVal " << maxVal << endl;

    // cout << "CC # " << numCC << endl;
    // cout << "label " << CC.label << endl;
    // cout << "numPixels " << CC.numPixels << endl;
    // cout << "minRow " << CC.minRow << endl;
    // cout << "minCol " << CC.minCol << endl;
    // cout << "maxRow " << CC.maxRow << endl;
    // cout << "maxCol " << CC.maxCol << endl;
    
    
}