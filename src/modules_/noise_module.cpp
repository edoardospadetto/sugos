#include "./noise_module.h"

#include <algorithm>
#include <random>
#include <exception>
#include "../include/safe_include_glm.h"
#include "../include/glm/gtx/norm.hpp"
#include <iostream>
#include <math.h>       /* modf */


float lerp_perlin(float a, float b, float  x)
{
    return a + x * (b - a);
}


float fade_perlin(float t)
{
    return ( (6 * t*t - 15 * t + 10) * t*t*t);
}

float gradient_perlin(int h, float x, float y)
{

    h = h%4; 
    int i= int(2*(h%2-0.5)), j=(h/2); 
    glm::vec2 g = glm::vec2(i*j, i*(1-j));
    return g.x * x + g.y * y ;
}

std::vector<float> Perlin2D(int Nx, int Ny, float freqX, float freqY,int octaves, int seed)
{
        
        //std::srand(201);
        std::vector<float> noise;
        std::vector<int> p;
        for (int i=0; i<256; i++) p.push_back(i);        
        
        auto rng = std::default_random_engine {};
        rng.seed(seed);
        std::shuffle(std::begin(p), std::end(p), rng);
        p.insert(p.end(), p.begin(), p.end());
        
        float noiseMax=-9000000;
        float noiseMin=+9000000;
        float div = 1;
    
        noise.resize(Nx*Ny);
        //xf, yf = x - xi, y - yi on the fly
       for(int oo =1; oo<=octaves; oo++)
       {
       for (int j=0; j<Ny ; j++)
       {
       for (int i=0; i<Nx ; i++)
       {
       
            int  xi = int(i*freqX/Nx) %512; 
            int  yi = int(j*freqY/Ny) %512;
            
            //std::cout<<xi<< " " << yi << "\n";
            
            float xf = i*freqX/Nx-xi;
            float yf = j*freqY/Ny-yi;
            float u = fade_perlin( xf ) ; 
            float v = fade_perlin( yf ) ;
            
            float n[4] = {  gradient_perlin(p[p[xi] + yi]         , xf, yf),
                            gradient_perlin(p[p[xi] + yi + 1]     , xf, yf - 1),
                            gradient_perlin(p[p[xi + 1] + yi + 1] , xf - 1, yf - 1),
                            gradient_perlin(p[p[xi + 1] + yi]     , xf - 1, yf) };
                            
            float x1 = lerp_perlin(n[0], n[3], u);
            float x2 = lerp_perlin(n[1], n[2], u);
            
            float noise_val =lerp_perlin(x1, x2, v);
            if(noiseMax<noise_val) noiseMax = noise_val*div;
            if(noiseMin>noise_val) noiseMin = noise_val*div;
            noise[i*Nx+j] = noise_val;
       }
       }
       div *=0.5;
       freqX*=2;
       freqY*=2;
       }
       
       for(int i=0; i<noise.size(); i++) {noise[i]  =(noise[i]-noiseMin)/(noiseMax-noiseMin);}
  
 
        return  noise;
} 


//1/rr smoothing
void MatrixCircleSmooth(std::vector<float> &noise_data, int Nx, int Ny, float rad, float temp)
{
    
    glm::vec2 center = glm::vec2(Nx*0.5, Ny*0.5);
    glm::vec2 tmp;
    float dist;
    for (int i=0; i<Nx ; i++)
    {
        for (int j=0; j<Ny ; j++)
        {
            tmp.x = j - center.x; 
            tmp.y = i - center.y;  
            dist = glm::length(tmp);
            //if( dist*dist >center.x*center.y*0.25)
            //{
                float distr = 1/ (1+ exp((dist*dist-rad*center.x*center.y)/(temp*temp)) );
                noise_data[i*Ny + j] =  (noise_data[i*Ny + j]-0.5)*distr; //center.x*center.y*(0.1/(dist*dist)) ;
                if (noise_data[i*Ny + j]< 0 ) noise_data[i*Ny + j] = 0.0;
                // exp(-0.005*( dist-0.3*center.x)*( dist-0.3*center.x)); 
            //}
           // else 
           // {
           //     noise_data[i*Ny + j] =1.0;
           // }
        }
    }
    


    float noiseMin = *std::min_element(noise_data.begin(), noise_data.end()) ;
    float noiseMax = *std::max_element(noise_data.begin(), noise_data.end()) ;
    
     for(int i=0; i<noise_data.size(); i++) {noise_data[i]  =(noise_data[i]-noiseMin)/(noiseMax-noiseMin);}
     
    
    

}


void  Equalize(std::vector<float> &noise_data, int N)
{
    float noiseMin = *std::min_element(noise_data.begin(), noise_data.end()) ;
    float noiseMax = *std::max_element(noise_data.begin(), noise_data.end()) ;
    float oneoverdom = (1.0-(0.1/N))/(noiseMax-noiseMin);
    int* hist = new int[N];
    float* cms = new float[N+1];
    int tmp0= 0;
    memset(hist, 0, N*sizeof(int));
 
    for (int i=0; i<noise_data.size(); i++)
    {
        tmp0 = int ( floor((noise_data[i]-noiseMin)*oneoverdom*N )) ;
  
        hist [int ( floor((noise_data[i]-noiseMin)*oneoverdom*N ))] +=1;         
    }

    cms[0] = 0;
    for (int i=0; i<N; i++)
    {
        cms[i+1] = cms[i]+ hist[i];
  
    }

    float tmp = 0;
    float tmp1 =0;
    float tmp2 =0;
    for (int i=0; i<noise_data.size(); i++)
    {
       tmp =  (noise_data[i]-noiseMin)*oneoverdom*N ;
       //std::cout << tmp << " " <<(noise_data[i]-noiseMin) << " " << 1.0/oneoverdom <<"\n ";
       tmp1 = modf(tmp, &tmp2);
       noise_data[i] =  ( tmp1*hist[int(tmp)] +  cms[int(tmp)]) / cms[N];
       //std::cout << tmp << " " << tmp2 << " " << tmp1 << " " << cms[int(tmp)] << " "  <<cms[N] << "\n"; 
       //std::cout <<  noise_data[i] << " " ; 
    }
    std::cout <<"\n";
    
    delete[] hist;
    delete[] cms;
    
}


void MatrixBlurFilter(std::vector<float> &data, int Nx, int Ny, int stride, float coeff)
{

    std::vector<float> tmp = {};
    tmp.resize(Nx*Ny);
    float mean = 0;
    for(int i=0; i<Nx; i++)
    {
    for(int j=0; j<Ny; j++)
    {
    for(int a=std::max(0,i-stride); a<std::min(Nx,i+stride); a++)
    {
    for(int b=std::max(0,j-stride); b<std::min(Ny,j+stride); b++)
    {
        mean += data[a*Nx+b];

    
    }
    }

    mean /= (2*stride + 1)*(2*stride + 1); 
    tmp[i*Nx+j]=mean*coeff;
    mean =0;
    }
    }
    data = tmp;
    

    
    float mmin = *std::min_element(data.begin(), data.end()) ;
    float mmax = *std::max_element(data.begin(), data.end()) ;
    //for(int i=0; i<data.size(); i++) {data[i]  =(data[i]-mmin)/(mmax-mmin);}
    
}

void Expand(std::vector<float> &data, int Nx, int Ny, int scalex, int scaley)
{

     
     data.resize(Nx*scalex*Ny*scaley);   
     
     
     for(int i=Nx-1; i>=0; i-- )
     {
     for(int j=Ny-1; j>=0; j-- )
     {
        data[i*scalex*scalex*Nx+j*scaley] = data[i*Nx+j]; 
        data[i*Nx+j]=0;    
     }
     }
     
     
     int a=0;
     int b=0;
     for(int i=0; i<Nx; i++ )
     {
     for(int j=0; j<Ny; j++ )
     {
     for(int ab=1; ab<scalex*scaley; ab++ )
     {
        a = ab/scalex;
        b = ab%scalex;
        data[(i*scalex+a)*Nx*scalex+j*scaley+b]=data[i*Nx*scalex*scalex+j*scaley];     
        
     }
     }
     }
     
}

void Replicate(std::vector<float> &data, int Nx, int Ny, int scalex, int scaley)
{
    
    int a=0;
    int b=0;
    data.resize(Nx*scalex*Ny*scaley);
    for (int i=0; i<Ny; i++)
    {
    for (int ab=1; ab<scalex*scaley; ab++)
    {
       a = ab/scalex;
       b = ab%scalex;
       std::cout << i*Nx <<" " <<scalex*a*Nx*Ny+(b+i)*Nx  << " " << Nx*scalex*Ny*scaley <<"\n";
       memcpy(&data[i*Nx],&data[scalex*a*Nx*Ny+(b+i)*Nx ],Ny*sizeof(float));
       
    }
    }


}
