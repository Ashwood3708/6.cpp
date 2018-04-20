/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   6.cpp
 * Author: Abdul
 *
 * Created on April 17, 2018, 5:57 PM
 */

#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;

/*
 * 
 */

string convert(int i) {
    switch (i) {
        case 0: return "A";
        case 1: return "B";
        case 2: return "C";
        case 3: return "D";
        case 4: return "E";
        case 5: return "F";
        case 6: return "G";
        case 7: return "H";
        case 8: return "I";
    }
}

int main(int argc, char** argv) {
    ifstream inFile;
    inFile.open("graph.txt");     //open file with graph values
    if (!inFile) {
        cout << "unable to open file graph.txt";
        exit(1); // terminate with error
    }
    int maxSize;                     //size of graph
    inFile>> maxSize;
    int a[maxSize][maxSize];         //create double array of graph
    for (int i = 0; i < maxSize; i++) {
        for (int j = i; j < maxSize; j++) {
            if (i == j) {          //fills in 0 along the diagonal
                a[i][j] = 0;
            } else {
                inFile >> a[i][j];  //enters the values for mirror locations
                a[j][i] = a[i][j];
            }
        }
    }
    inFile.close();         //no longer need file so close it

    int fastI[maxSize]; //array to hold path value
    int b[maxSize]; //array to keep track which paths found
    string fastS[maxSize]; // array to hold path 
    for (int k = 0; k < maxSize; k++) {  
        fastI[k] = 1000;
        fastS[k] = "";
        b[k] = 1;
    }
    //0 means its path has been found, start from A so it starts at 0
    b[0] = 0; 
    //shortest path markers
    int est = 0, min = 0, turnMin; 
    //est is current path being checked
    //min is the index of the lowest path/value
    //turnMin is the lowest path value found from est 

    for (int m = 0; m < maxSize; m++) { //it finds a path for each point
        turnMin = 1000;   //gotta reset each time
        for (int p = 0; p < maxSize; p++) { //loop to find path from est
            if (a[est][p] != 0 && b[p] != 0) { //makes sure there is a path
                if (a[est][p] < fastI[p] && fastI[est] == 1000) {  //only if this is the first time a path to this node is found
                    fastI[p] = a[est][p];                     //sets path length to weight of est to p
                    fastS[p] = convert(est) + convert(p);     //sets path label to string format of est to p
                    if (fastI[p] < turnMin) {                 //saves the smallest current path value seen so far
                        turnMin = fastI[p];
                        min = p;                               //index of lowest value found
                    }
                } else
                    if (a[est][p] + fastI[est] < fastI[p]) {    //if total path weight lessthan saved path weight
                    fastI[p] = a[est][p] + fastI[est];          //save the combined new path weight
                    fastS[p] = fastS[est] + convert(p);
                    if (fastI[p] < turnMin) {
                        turnMin = fastI[p];
                        min = p;
                    }
                }
            }
        }
        b[min] = 0;                //0 means the lowest possible path has been found to that node
        est = min;                 //will now find other paths begining from current index
    }

   

    ofstream myfile;
  myfile.open ("result.txt");
   for (int o = 1; o < maxSize; o++) {
        cout << fastS[o] << " = " << fastI[o] << endl;
        myfile<<"Shortest path from "<< convert(0)<< " to "<< convert(o)<<" is: "<< fastI[o];
        myfile<<endl;
        myfile<<"Path taken: "<< fastS[o];
        myfile<<endl;
    }
  myfile.close();
    return 0;
}

