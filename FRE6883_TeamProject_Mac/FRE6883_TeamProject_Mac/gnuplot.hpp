//
//  plot.hpp
//  script
//
//  Created by Yipei Zhang on 12/13/21.
//
#include <vector>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;
void plotResults(vector<double> &ydata1,vector<double> &ydata2,vector<double> &ydata3, int dataSize) {
    int i;
    int nIntervals = 120;
    double intervalSize = 1.0;
    double stepSize = intervalSize/nIntervals;
    vector<double> xData;
    vector<double> data1;
    vector<double> data2;
    vector<double> data3;
    double x0 = -60;
    xData.push_back(x0);
    for (i = 0; i < nIntervals; i++) {
        x0 = x0 + 1;
        xData.push_back(x0);
    }
    for (i = 0; i <= nIntervals; i++) {
        x0 = xData[i];
        data1.push_back(ydata1[i]);
    }
    for (i = 0; i <= nIntervals; i++) {
        x0 = xData[i];
        data2.push_back(ydata2[i]);
    }
    for (i = 0; i <= nIntervals; i++) {
        x0 = xData[i];
        data3.push_back(ydata3[i]);
    }
    
    
    FILE *gnuplotPipe,*tempDataFile;
    const char *tempDataFileName1 = "Miss";
    const char *tempDataFileName2 = "Meet";
    const char *tempDataFileName3 = "Beat";
    double x,y, x2, y2, x3, y3;

    gnuplotPipe = popen("/opt/local/bin/gnuplot","w");
    if (gnuplotPipe) {
        
        // need these two lines or we can not create file to store data.
        cin.clear();
        cin.ignore(9999,'\n');
        fprintf(gnuplotPipe,"plot \"%s\" with lines, \"%s\" with lines, \"%s\" with lines\n",tempDataFileName1, tempDataFileName2, tempDataFileName3);
        fflush(gnuplotPipe);
        
        tempDataFile = fopen(tempDataFileName1,"w");
        for (i=0; i < dataSize; i++) {
            x = xData[i];
            y = data1[i];
            fprintf(tempDataFile,"%lf %lf\n",x,y);
        }
        fclose(tempDataFile);
        
        tempDataFile = fopen(tempDataFileName2,"w");
        for (i=0; i < dataSize; i++) {
            x2 = xData[i];
            y2 = data2[i];
            fprintf(tempDataFile,"%lf %lf\n",x2,y2);
        }
        fclose(tempDataFile);
        
        tempDataFile = fopen(tempDataFileName3,"w");
        for (i=0; i < dataSize; i++) {
            x3 = xData[i];
            y3 = data3[i];
            fprintf(tempDataFile,"%lf %lf\n",x3,y3);
        }
        fclose(tempDataFile);
        
        printf("press enter to continue...");
        getchar();
        remove(tempDataFileName1);
        remove(tempDataFileName2);
        remove(tempDataFileName3);
        fprintf(gnuplotPipe,"exit \n");
    } else {
        printf("gnuplot not found...");
    }
}
