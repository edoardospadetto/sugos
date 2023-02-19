#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <turtle.h>


//Problems multiwindow.
//Focus textbox single window
int main()
{
 //std::string font0 = "!\"#$%_'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_'abcdefghiklmnopqrstuvwxyz{|}~ç€£&à";
 //"ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.,!?"
  EventEngine MainEngine=EventEngine(60);
  Window_Class w = Window_Class(SDL_WINDOW_OPENGL| SDL_WINDOW_SHOWN, "PerlinNoise", 640,640 ); 
  MainEngine.HandleWindow(&w);
  
  
  int Nx = 100, Ny=100; 
  
  
  GPUcodes matT=GPUcodes(&w);
  matT.AddSource("./src/shaders_/matrix_texture.shader");
  matT.Load("texturev","texturef", "text");

  std::vector<float> noise_data = Perlin2D(Nx, Ny, 3.0,3.0,  2, 3);
  /*for(int i = 0; i< Nx; i++)
  {
  for(int j = 0; j< Ny; j++)
  {
    std::cout << noise_data[i*Nx+j] << std::endl; //= 0.5;
  }
  }*/
  
  /*
  for(int i=0; i<noise_data.size(); i++)
  {
    //std::cout << noise_data[i] << "\n" ;
    //noise_data[i]+=1.0;
    //noise_data[i] *=0.5; 
  }
  */

  VectorizedObject noise_surf = VectorizedObject (2,4,2,2,GL_TRIANGLES) ;
  GenQuad2T(noise_surf);

  Texture noise_t = Texture();
  noise_t.LoadTexture(&w,&(noise_data[0]) ,Nx, Ny, 1);
  
  /*for(int i=0; i<noise_surf.vertex_num * noise_surf.vertex_len; i++)
  {
    std::cout << noise_surf.vertex_buffer[i] << "\n" ;
    
  }*/


  noise_surf.SpecifyBuffersAttributes("aPos", 2);
  noise_surf.LinkUniformToVariable("m_sizes", 2, GL_FLOAT);
  noise_surf.LinkUniformToVariable("w_sizes", 2, GL_FLOAT);
  
  noise_surf.SetUniform("w_sizes",0,640.0);
  noise_surf.SetUniform("w_sizes",1,640.0);
  noise_surf.SetUniform("m_sizes",0,Nx);
  noise_surf.SetUniform("m_sizes",1,Ny);


  noise_surf.SetTexture(&noise_t);
  
  Scene scene = Scene();

  scene.LoadObject(&noise_surf, matT.glprograms[0]);

  scene.Prepare();
  //menuscene = Scene()
  std::cout << "MAIN LOOP \n \n"; 
 
  while(w.IsAlive())
  {     
        w.CycleStart();
      
	    scene.Prepare();
	   
  	    scene.Update();
  	    
  	
	    w.CycleEnd();
	    MainEngine.WindowsEvents();
  }
  w.Close();
  
}
