#ifndef CHAINCODE_H
#define CHAINCODE_H

#include <iostream>
using namespace std;

class ChainCode{
    struct Point{
        int row;
        int col;
    };

    struct CCProperty{
        int label;
        int numPixels;
        int minRow;
        int minCol;
        int maxRow;
        int maxCol;
    }; 
    
    private:
        int numRows;
        int numCols;
        int minVal;
        int maxVal;

        int **imageAry;
        int **boundaryAry;
        int **CCAry;

        int numCC;

        CCProperty CC;

        Point startP;
        Point currentP;
        Point nextP;
        
        int lastQ;

        int nextQ;

        int PChainDir;

        Point *coordOffset = new Point[8];
        Point *neighborCoord = new Point[8];

        int *zeroTable = new int[6,0,0,2,2,4,4,6];




    public:
        ChainCode(int ImageRows, int ImageColumns, int ImageMin, int ImageMax, int numOfCC, int label, int pixels, int minR, int minC, int maxR, int maxC, int **image, int **cc, int** boundary);
        void loadImage(ifstream& labelFile);
        void clearCCAry();

        void loadCCAry();

        void getChainCode();
        
        int findNextP(Point currP, int lastQ);

        void loadNeighBors(Point current);
        
        void print();

};

#endif