#include <stdio.h>
#include <math.h>
#include <iostream>
#include "RGB2LAB.h"
void RGB2LAB ( float R_value, float G_value, float B_value, float &L, float &a, float &b)
{
        double RGB[3];
        double XYZ[3];
//	double Lab[3];
//	double RGB2[3];
//	double XYZ2[3];
//	double Lab2[3];
        double adapt[3];

        adapt[0] = 0.950467;
        adapt[1] = 1.000000;
        adapt[2] = 1.088969;

        RGB[0] = R_value * 0.003922;
        RGB[1] = G_value * 0.003922;
        RGB[2] = B_value * 0.003922;

        XYZ[0] = 0.412424 * RGB[0] + 0.357579 * RGB[1] + 0.180464 * RGB[2];
        XYZ[1] = 0.212656 * RGB[0] + 0.715158 * RGB[1] + 0.0721856 * RGB[2];
        XYZ[2] = 0.0193324 * RGB[0] + 0.119193 * RGB[1] + 0.950444 * RGB[2];

        L = 116 * H( XYZ[1] / adapt[1] ) - 16;
        a = 500 * ( H( XYZ[0] / adapt[0] ) - H( XYZ[1] / adapt[1] ) );
        b = 200 * ( H( XYZ[1] / adapt[1] ) - H( XYZ[2] / adapt[2] ) );

//	RGB2[0] = R_value2 * 0.003922;
//	RGB2[1] = G_value2 * 0.003922;
//	RGB2[2] = B_value2 * 0.003922;

//	XYZ2[0] = 0.412424 * RGB2[0] + 0.357579 * RGB2[1] + 0.180464 * RGB2[2];
//	XYZ2[1] = 0.212656 * RGB2[0] + 0.715158 * RGB2[1] + 0.0721856 * RGB2[2];
//	XYZ2[2] = 0.0193324 * RGB2[0] + 0.119193 * RGB2[1] + 0.950444 * RGB2[2];

//	Lab2[0] = 116 * H( XYZ2[1] / adapt[1] ) - 16;
//	Lab2[1] = 500 * ( H( XYZ2[0] / adapt[0] ) - H ( XYZ2[1] / adapt[1] ) );
//	Lab2[2] = 200 * ( H( XYZ2[1] / adapt[1] ) - H ( XYZ2[2] / adapt[2] ) );

//	printf("r=%f g=%f b=%f nr=%f ng=%f nb=%f\n",Lab[0],Lab[1],Lab[2],Lab2[0],Lab2[1],Lab2[2]);

//	value = pow( (Lab[0] - Lab2[0]), 2 ) + pow( (Lab[1] - Lab2[1]), 2 ) + pow( (Lab[2] - Lab2[2]), 2 );

//	return value;
}

double H(double q)
{
        double value;
        if ( q > 0.008856 ) {
                value = pow ( q, 0.333333 );
                return value;
        }
        else {
                value = 7.787*q + 0.137931;
                return value;
        }
}

