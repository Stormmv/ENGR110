/*
 *
 * */
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <string>
using namespace std;
#include "image_pr4.h"
#include <thread>
#include <chrono>
#include <math.h>
vector<int> middle_x;
vector<int> middle_y;
vector<int> timeVec;
bool debug = true;
bool runGetTrackData = true;
bool foundSunrise = false;
int counterForPoints = 0;
// you can use that
struct Orbit
{
	// logged position and time
	std::vector<int> x;
	std::vector<int> y;
	std::vector<int> t;
	int xc, yc, r; // center and radius
	int x_sunrise, y_sunrise;
	double omega = 0.1;
} orbit;

void calcMidOfSun(ImagePPM image, int time)
{
	int min_x = 0;
	int min_y = 0;
	int max_x = 0;
	int max_y = 0;
	for (int i = 0; i < image.width; i++)
	{
		for (int j = 0; j < image.height; j++)
		{
			if ((int)get_pixel(image, i, j, 0) == 255 && (int)get_pixel(image, i, j, 1) == 0 && (int)get_pixel(image, i, j, 2) == 0)
			{
				if (min_x == 0)
				{
					min_x = j;
				}
				if (min_y == 0)
				{
					min_y = i;
				}
				if (j < min_x)
				{
					min_x = j;
				}
				if (i < min_y)
				{
					min_y = i;
				}
				if (j > max_x)
				{
					max_x = j;
				}
				if (i > max_y)
				{
					max_y = i;
				}
			}
		}
	}
	int mid_x = (min_x + max_x) / 2;
	int mid_y = (min_y + max_y) / 2;
	if (mid_x != 0 && mid_y != 0)
	{
		middle_x.push_back(mid_x);
		middle_y.push_back(mid_y);
		timeVec.push_back(time);
		counterForPoints += 1;
	}
	if (debug)
	{
		std::cout << "mid_x: " << mid_x << std::endl;
		std::cout << "mid_y: " << mid_y << std::endl;
	}
}

float getXc(float a11, float a12, float a13, float b1, float a21, float a22, float a23, float b2, float a31, float a32, float a33, float b3)
{
	float a1 = b1;
	float b11 = a12;
	float c1 = a13;
	float d1 = b2;
	float e1 = a22;
	float f1 = a23;
	float g1 = b3;
	float h1 = a32;
	float i1 = a33;
	float determinate1 = (a1 * ((e1 * i1) - (f1 * h1)) - (b11 * ((d1 * i1) - (f1 * g1))) + (c1 * ((d1 * h1) - (e1 * g1))));
	float a2 = a11;
	float b22 = a12;
	float c2 = a13;
	float d2 = a21;
	float e2 = a22;
	float f2 = a23;
	float g2 = a31;
	float h2 = a32;
	float i2 = a33;
	float determinate2 = (a2 * ((e2 * i2) - (f2 * h2)) - (b22 * ((d2 * i2) - (f2 * g2))) + (c2 * ((d2 * h2) - (e2 * g2))));
	return (determinate1 / determinate2);
}

float getYc(float a11, float a12, float a13, float b1, float a21, float a22, float a23, float b2, float a31, float a32, float a33, float b3)
{
	float a1 = a11;
	float b11 = b1;
	float c1 = a13;
	float d1 = a21;
	float e1 = b2;
	float f1 = a23;
	float g1 = a31;
	float h1 = b3;
	float i1 = a33;
	float determinate1 = (a1 * ((e1 * i1) - (f1 * h1)) - (b11 * ((d1 * i1) - (f1 * g1))) + (c1 * ((d1 * h1) - (e1 * g1))));
	float a2 = a11;
	float b22 = a12;
	float c2 = a13;
	float d2 = a21;
	float e2 = a22;
	float f2 = a23;
	float g2 = a31;
	float h2 = a32;
	float i2 = a33;
	float determinate2 = (a2 * ((e2 * i2) - (f2 * h2)) - (b22 * ((d2 * i2) - (f2 * g2))) + (c2 * ((d2 * h2) - (e2 * g2))));
	return (determinate1 / determinate2);
}

float getR(float a11, float a12, float a13, float b1, float a21, float a22, float a23, float b2, float a31, float a32, float a33, float b3)
{
	float a1 = a11;
	float b11 = a12;
	float c1 = b1;
	float d1 = a21;
	float e1 = a22;
	float f1 = b2;
	float g1 = a31;
	float h1 = a32;
	float i1 = b3;
	float determinate1 = (a1 * ((e1 * i1) - (f1 * h1)) - (b11 * ((d1 * i1) - (f1 * g1))) + (c1 * ((d1 * h1) - (e1 * g1))));
	float a2 = a11;
	float b22 = a12;
	float c2 = a13;
	float d2 = a21;
	float e2 = a22;
	float f2 = a23;
	float g2 = a31;
	float h2 = a32;
	float i2 = a33;
	float determinate2 = (a2 * ((e2 * i2) - (f2 * h2)) - (b22 * ((d2 * i2) - (f2 * g2))) + (c2 * ((d2 * h2) - (e2 * g2))));
	return (determinate1 / determinate2);
}

int main()
{
	std::cout << "start..." << std::endl;
	init(1);
	// int x_sun, y_sun; // current position of the sun
	for (int time = 0; time < 950; time++)
	{
		draw_all(time); // image is ready,
		if (counterForPoints <= 24)
		{
			calcMidOfSun(image, time);
			if (debug)
			{
				std::cout << "counterForPoints: " << counterForPoints << std::endl;
			}
		}
		if (counterForPoints == 25 && runGetTrackData)
		{
			float a11 = 25;
			float a12 = 0;
			float a13 = 0;
			for (int i = 0; i < timeVec.size(); i++)
			{
				a13 += cos(0.1 * timeVec[i]);
			}
			float b1 = 0;
			for (int i = 0; i < timeVec.size(); i++)
			{
				b1 += middle_x[i];
			}
			float a21 = 0;
			float a22 = 25;
			float a23 = 0;
			for (int i = 0; i < timeVec.size(); i++)
			{
				a23 += sin(0.1 * timeVec[i]);
			}
			float b2 = 0;
			for (int i = 0; i < timeVec.size(); i++)
			{
				b2 += middle_y[i];
			}
			float a31 = 0;
			for (int i = 0; i < timeVec.size(); i++)
			{
				a31 += cos(0.1 * timeVec[i]);
			}
			float a32 = 0;
			for (int i = 0; i < timeVec.size(); i++)
			{
				a32 += sin(0.1 * timeVec[i]);
			}
			float a33 = 25;
			float b3 = 0;
			for (int i = 0; i < timeVec.size(); i++)
			{
				b3 += (middle_x[i] * cos(0.1 * timeVec[i])) + (middle_y[i] * sin(0.1 * timeVec[i]));
			}
			if (debug)
			{
				std::cout << "a11: " << a11 << std::endl;
				std::cout << "a12: " << a12 << std::endl;
				std::cout << "a13: " << a13 << std::endl;
				std::cout << "b1: " << b1 << std::endl;
				std::cout << "a21: " << a21 << std::endl;
				std::cout << "a22: " << a22 << std::endl;
				std::cout << "a23: " << a23 << std::endl;
				std::cout << "b2: " << b2 << std::endl;
				std::cout << "a31: " << a31 << std::endl;
				std::cout << "a32: " << a32 << std::endl;
				std::cout << "a33: " << a33 << std::endl;
				std::cout << "b3: " << b3 << std::endl;
			}
			float Xc = getXc(a11, a12, a13, b1, a21, a22, a23, b2, a31, a32, a33, b3);
			float Yc = getYc(a11, a12, a13, b1, a21, a22, a23, b2, a31, a32, a33, b3);
			float R = getR(a11, a12, a13, b1, a21, a22, a23, b2, a31, a32, a33, b3);
			if (debug)
			{
				std::cout << "Xc: " << Xc << std::endl;
				std::cout << "Yc: " << Yc << std::endl;
				std::cout << "R: " << R << std::endl;
			}
			orbit.xc = Xc;
			orbit.yc = Yc;
			orbit.r = R;
			int sunriseX = 0;
			int sunriseY = 0;
			for (int i = 0; i < timeVec.size(); i++)
			{
				if ((timeVec[i] += 1) != (timeVec[i + 1]) && !foundSunrise)
				{
					sunriseX = middle_x[i + 1];
					sunriseY = middle_y[i + 1];
					if (debug)
					{
						std::cout << "sunriseX: " << sunriseX << std::endl;
						std::cout << "sunriseY: " << sunriseY << std::endl;
						std::cout << "timeVec[i]: " << timeVec[i] << std::endl;
					}
					orbit.x_sunrise = sunriseX;
					orbit.y_sunrise = sunriseY;
					foundSunrise = true;
				}
			}
			runGetTrackData = false;
		}
		if (runGetTrackData == false)
		{
			int x, y;
			get_aim(x, y);
			int x1 = orbit.xc + orbit.r * cos(orbit.omega * time);
			int y1 = orbit.yc + orbit.r * sin(orbit.omega * time);
			int angle = atan2(y1 - y, x1 - x);
			move_aim(angle);
		}
		if (runGetTrackData == false)
		{
			int x, y;
			get_aim(x, y);
			int sunriseX = 0;
			int sunriseY = 0;
			for (int i = 0; i < timeVec.size(); i++)
			{
				if ((timeVec[i] += 1) != (timeVec[i + 1]) && !foundSunrise && y == 900)
				{
					sunriseX = middle_x[i + 1];
					sunriseY = middle_y[i + 1];
					if (debug)
					{
						std::cout << "sunriseX: " << sunriseX << std::endl;
						std::cout << "sunriseY: " << sunriseY << std::endl;
						std::cout << "timeVec[i]: " << timeVec[i] << std::endl;
					}
					orbit.x_sunrise = sunriseX;
					orbit.y_sunrise = sunriseY;
					foundSunrise = true;
				}
			}
		}
		if (runGetTrackData == false && foundSunrise == true)
		{
			int x, y;
			get_aim(x, y);
			if (y > 900)
			{
				int angle = atan2(orbit.y_sunrise - y, orbit.x_sunrise - x);
				move_aim(angle);
			}
		}

		std::cout << " time=" << time << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	std::cout << "end" << std::endl;
	return 0;
}
