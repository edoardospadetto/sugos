#include <turtle.h>

void render();

//Shader loading utility programs
void printProgramLog( GLuint program );
void printShaderLog( GLuint shader );


GLint gVertexPos2DLocation = -1;



int main( int argc, char* args[] )
{
	
	// Create Window
	EventEngine MainEngine=EventEngine(60);
	Window_Class window = Window_Class(SDL_WINDOW_OPENGL| SDL_WINDOW_SHOWN,"Sat_ex", 640,320 ); 
	MainEngine.HandleWindow(&window);
	
	// Shader
	GPUcodes gpucodes0=GPUcodes(&window,"./src/shaders_/vectorizedobjectnc.shader");	
	gpucodes0.Load("vecv","vecf", "vv");
	glClearColor( 0.f, 0.f, 0.f, 1.f );
	ColliderObject2D Square(2,4,1,2,GL_QUADS), Triangle(2,3,1,2,GL_TRIANGLES);
	
	
	Triangle.SpecifyBuffersAttributes("r_", 2) ;
	Square.SpecifyBuffersAttributes("r_", 2) ;
	
	Square.LinkUniformToVariable("CM", 4, GL_FLOAT);
	Triangle.LinkUniformToVariable("CM", 4, GL_FLOAT);

	
	
	GenQuad(Square);
	GenTriangle(Triangle);	
	Square.SetToOrigin(0);
	Triangle.SetToOrigin(0);
	
	Triangle.Rescale(0, 5.0);
	Triangle.SetToOrigin(0);
	Square.Rescale(0,2.0);
	
	Triangle.SameShapeCollider(0, GENERIC);
	Square.SameShapeCollider(0, GENERIC);

	
	
	Scene test = Scene();
	test.SetCollisionHandler(RigidCollision);
	test.LoadObject(&Square, gpucodes0.glprograms[0]);
	test.LoadObject(&Triangle, gpucodes0.glprograms[0]);
	

	Square.collider->xc = &(Square.position[0]);
	Square.collider->yc = &(Square.position[1]);
	Square.collider->angle = &(Square.angle);
	Triangle.collider->xc = &(Triangle.position[0]);
	Triangle.collider->yc = &(Triangle.position[1]);
	Triangle.collider->angle = &(Triangle.angle);
	
	test.DebugColliders(&window);
	
	
  std::string str1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.,!?";
  GPUcodes gpucodes1=GPUcodes(&window,"./src/shaders_/font.shader");	
  gpucodes1.Load("fontV","fontF", "font");
  Texture fontTexture = Texture();	
  fontTexture.LoadTexture(&window,"./etc/fonts/font.png",true,4, GL_RGBA);
  BitmapFont pixelFont =  BitmapFont("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.,!?", 5, 8, 8, 10, &fontTexture);
  Textbox tbtext = Textbox("PRESS A W S D Z X", &pixelFont,1,17,0.1,0.14);
  tbtext.SetUpDefaultShader();
  tbtext.SetCoords(-0.9,0.8,-0.0,0.0);
  test.LoadObject(&tbtext, gpucodes1.glprograms[0]);
	
	test.Prepare();

	const Uint8* kb = SDL_GetKeyboardState(NULL);
	int counter = 0;
	
	
	while( window.IsAlive() )
	{
		window.CycleStart();
	
		Triangle.position[0]+= 0.005*(-kb[SDL_SCANCODE_A] + kb[SDL_SCANCODE_D]) 
			- 2*float(Triangle.position[0]>1.0) + 2*float(Triangle.position[0]<-1.0);
		Triangle.position[1] += 0.005*(-kb[SDL_SCANCODE_S] + kb[SDL_SCANCODE_W]) 
			- 2*float(Triangle.position[1]>1.0) + 2*float(Triangle.position[1]<-1.0);
		Triangle.angle +=  0.005*(-kb[SDL_SCANCODE_Z] + kb[SDL_SCANCODE_X])  ;
		
		Triangle.SetUniform("CM",0,Triangle.position[0]);
		Triangle.SetUniform("CM",1,Triangle.position[1]);
		Triangle.SetUniform("CM",2,Triangle.angle);
		Square.SetUniform("CM",0,Square.position[0]);
		Square.SetUniform("CM",1,Square.position[1]);
		Square.SetUniform("CM",2,Square.angle);
		
		test.Update();
		test.Prepare();
	
		window.CycleEnd();
		MainEngine.WindowsEvents();
	}
	window.Close();

	return 0;
}
