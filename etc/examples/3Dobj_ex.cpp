#include "turtle.h"


int main( int argc, char* args[] )
{
    	// Create Window
	EventEngine MainEngine=EventEngine(60);
	Window_Class window = Window_Class(SDL_WINDOW_OPENGL| SDL_WINDOW_SHOWN, "Vob_ex", 640,640 ); 
	MainEngine.HandleWindow(&window);
	
	// Shader
	GPUcodes gpucodes0=GPUcodes(&window,"./src/shaders_/3d_simple.shader");	
	gpucodes0.Load("3Dsimplev","3Dsimplef", "3Dsimple");
	VectorizedObject* obj;
	LoadObjFile("./etc/assets/eb_house_plant_01.obj", &obj);
    Texture objTexture = Texture();
    objTexture.LoadTexture(&window,"./etc/assets/eb_house_plant_01_c1.png",true,4, GL_RGBA);
    //obj->RescaleTextureCoordinatesMaxMin01(3,2);
    //obj->RescaleTextureCoordinates01(3, 2, -2.55, 2.55);
 
	obj->SpecifyBuffersAttributes("p3d_Vertex", 3);
	obj->SpecifyBuffersAttributes("vTexCoord", 2);
	obj->SetTexture(&objTexture, "uTexture");
	obj->SpecifyBuffersAttributes("b", 3);
	obj->SkipAttribute("b");
	
	
	
   
	obj->SetToOrigin(0);
	obj->Rescale(0,0.05);

	
	dbglog("test" , obj, obj->vertex_buffer[4]);
	
	Scene test = Scene();
	test.LoadObject(obj, gpucodes0.glprograms[0]);
	test.Prepare();
	
	
	
  while(window.IsAlive())
  {
    window.CycleStart();
    
    test.Prepare();
	test.Update();
		
  	window.CycleEnd();
	MainEngine.WindowsEvents();
	
		
  }     
  window.Close();

}
