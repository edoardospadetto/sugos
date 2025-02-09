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

   obj->SetTexture(&objTexture);
	obj->SpecifyBuffersAttributes("p3d_Vertex", 3);
	obj->SpecifyBuffersAttributes("vTexCoord", 2);
    // "uTexture");
	//obj->SpecifyBuffersAttributes("vnormals", 3);
	//obj->SkipAttribute(3);


   //float dx = -0.5;
   //obj->Translate(0,&dx);
   //obj->Translate(1,&dx);

   //obj->SetToOrigin(0);

	obj->Rescale(0,0.2);
   //obj->Rescale(1,0.01);
   //obj->Rescale(2,0.01);


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
