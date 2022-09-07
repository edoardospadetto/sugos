#ifndef NOISE_MOD
#define NOISE_MOD
#include <vector>



float lerp_perlin(float a, float b, float  x);

float fade_perlin(float t);

float gradient_perlin(int h, float x, float y);

std::vector<float> Perlin2D(int Nx, int Ny, float freqX, float freqY,int octaves, int seed);

void MatrixBlurFilter(std::vector<float> &data, int Nx, int Ny, int strid, float coeff);

void Expand(std::vector<float> &data, int Nx, int Ny, int scalex, int scaley);

void MatrixCircleSmooth(std::vector<float> &noise_data, int Nx, int Ny, float rad, float temp);

void Replicate(std::vector<float> &data, int Nx, int Ny, int scalex, int scaley);

void Equalize(std::vector<float> &noise_data, int N);

#endif 
