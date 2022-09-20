// Copyright 2022 Zener
// Created by Zener on 15.09.22.
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float x;
    float y;
} Point;

/// finds euclidean distance between 2 points
/// @param A the first point
/// @param B the second point
/// @return distance between 2 points
float distance(Point A, Point B){
    float result;

    float _x_ = A.x - B.x;
    float _y_ = A.y - B.y;


    result = sqrtf(powf(_x_, 2) + powf(_y_, 2));

    return result;
}

/// finds area of the triangle
/// @param A the first point of the triangle
/// @param B the second point of the triangle
/// @param C the third point of the triangle
/// @return the area of the triangle
float area(Point A, Point B, Point C){
    float result;

    float x1y2 = A.x * B.y;
    float x2y1 = B.x * A.y;
    float x2y3 = B.x * C.y;
    float x3y2 = C.x * B.y;
    float x3y1 = C.x * A.y;
    float x1y3 = A.x * C.y;

    result = fabsf(x1y2 - x2y1 + x2y3 - x3y2 + x3y1 - x1y3) / 2;

    return result;
}

int main(void){

    Point A, B, C;
    A.x = 2.5, A.y = 6;
    A.x = 1, B.y = 2.2;
    A.x = 10, C.y = 6;


    float f = distance(A, B);
    printf("A -- B distance is %f\n", f);


    float a = area(A, B, C);
    printf("Area of triangle ABC is %f\n", a);

    return EXIT_SUCCESS;
}