#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include "windows.h"
#include "FreeImage.h"
//#pragma comment(lib, "FreeImage.lib")
typedef unsigned char vector3ub[3];
typedef unsigned char vector4ub[4];
#include "../cAUV/physics/Vectors.h"


#define IMAGE_LOADER_RB 0.3f
#define IMAGE_LOADER_GB 0.59f
#define IMAGE_LOADER_BB 0.11f



void InitImageLoader();
vector3ub* LoadImage3ub(char* filename, int &w, int &h, int from=0, int to=-1);
vector4ub* LoadImage4ub(char* filename, int &w, int &h, int from=0, int to=-1);
vec3* LoadImage3f(char* filename, int &w, int &h, int from=0, int to=-1);
vec4* LoadImage4f(char* filename, int &w, int &h, int from=0, int to=-1);
float* LoadImage1f(char* filename, int &w, int &h, int from=0, int to=-1);
bool GetImageSize(char* filename, int &w, int &h);


bool SaveImageAsJPEG(char* filename, vector3ub* img, int w, int h, int quality=3);
bool SaveImageAsJPEG(char* filename, vec3* img, int w, int h, int quality=3);
bool SaveImageAsJPEG(char* filename, float* img, int w, int h, int quality=3);


bool SaveImageAsBMP(char* filename, vector3ub* img, int w, int h, int compress=0);
bool SaveImageAsBMP(char* filename, vec3* img, int w, int h, int compress=0);
bool SaveImageAsBMP(char* filename, float* img, int w, int h, int compress=0);


bool SaveImageAsPNG(char* filename, vector3ub* img, int w, int h, int compress=0);
bool SaveImageAsPNG(char* filename, vec3* img, int w, int h, int compress=0);
bool SaveImageAsPNG(char* filename, vector4ub* img, int w, int h, int compress=0);
bool SaveImageAsPNG(char* filename, vec4* img, int w, int h, int compress=0);
bool SaveImageAsPNG(char* filename, float* img, int w, int h, int compress=0);

bool SaveImage(char* filename, vector3ub* img, int w, int h, int param=-1);
bool SaveImage(char* filename, vector4ub* img, int w, int h, int param=-1);
bool SaveImage(char* filename, vec3* img, int w, int h, int param=-1);
bool SaveImage(char* filename, vec4* img, int w, int h, int param=-1);
bool SaveImage(char* filename, float* img, int w, int h, int param=-1);


void FreeImageLoader();

#endif
