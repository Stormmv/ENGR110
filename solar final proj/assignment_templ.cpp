#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "image_l4.hpp"
#include <string>
using namespace std;

ImagePPM applyKernal(ImagePPM main){
    double kernel[3][3] = {
    {1.0/9.0,1.0/9.0,1.0/9.0},
    {1.0/9.0,1.0/9.0,1.0/9.0},
    {1.0/9.0,1.0/9.0,1.0/9.0}
    };
    ImagePPM noiseReduction;
    init_image(noiseReduction, main.width, main.height);
    for(unsigned int row = 1; row < main.height-1; row++){
        for(unsigned int col = 1; col < main.width-1; col++){
            int sum = 0;
            for(int i = -1; i <=1 ; i++){
                for(int j = -1; j <= 1; j++){
                    sum += ((int)get_pixel(main, row+i, col+j, 0)) * kernel[i+1][j+1];
                }
            }
            sum = abs(sum);
            set_pixel(noiseReduction, row, col, sum, sum, sum);
        }
    }
    return noiseReduction;
}


int main(){
    ImagePPM image;
    OpenPPMFile("line.ppm",image); // reserves the memory too

    ofstream myfile;
    myfile.open("luminosityNormal.txt");
    for(int col = 0; col < image.width; col++){
        myfile <<col<<" "<< (int)get_pixel(image, 360, col, 3) << endl;
    }

    ImagePPM noiseRED = applyKernal(image);
    SavePPMFile("filtered.ppm", noiseRED); 

    ofstream myfile2;
    myfile2.open("luminosityNoiseRed.txt");
    for(int col = 0; col < noiseRED.width; col++){
        myfile2 <<col<<" "<< (int)get_pixel(noiseRED, 360, col, 3) << endl;
    }
    
    return 0;
}
