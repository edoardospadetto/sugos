/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

#include "turtle.h"
//Screen dimension constants
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;

void render();

//Frees media and shuts down SDL


//Shader loading utility programs
void printProgramLog( GLuint program );
void printShaderLog( GLuint shader );

//The window we'll be rendering to




//Render flag



GLint gVertexPos2DLocation = -1;





void GenQuad(VectorizedObject& obj)
{
	float vertex[]= 	//VBO data
	{
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f,  0.5f
	};

	
	
	for (int i =0; i<8; i++)
	{
	obj.vertex_buffer[i] = vertex[i];
	}
	
	for (int i =0; i<3; i++)
	{
		obj.index_buffer[i] = i;
		obj.index_buffer[i+3]=i+1;
	}
	
	



					 
}


void GenTriangle(VectorizedObject& obj)
{
	float vertex[]= 	//VBO data
	{	
		 0.05f,  0.0f,
		-0.05f,  0.0f,
		 0.0f,  sqrt(3)*0.05f,

	};

	
	
	for (int i =0; i<6; i++)
	{
	obj.vertex_buffer[i] = vertex[i];
	}
	
	for (int i =0; i<3; i++)
	{
		obj.index_buffer[i]=i;
	}
	
//		for (int i =0; i<6; i++)
//	{
//		std::cout << obj.index_buffer[i] << std::endl;
//	}



					 


}




void Gen2Triangle(VectorizedObject& obj)
{
	float vertex[]= 	//VBO data
	{	
		 0.2f,  0.3f,
		-0.5f, -0.5f,
		 0.8f, -0.6f,
		 -0.1f,  0.1f,
	};

	
	
	for (int i =0; i<8; i++)
	{
		obj.vertex_buffer[i] = vertex[i];
	}
/*	for (int i =6; i<12; i++)
	{
		obj.vertex_buffer[i] = vertex[i-6]-0.3*(i%2-1)+0.6*(i%2);
	}*/
	
	
	for (int i =0; i<3; i++)
	{
		//obj.index_buffer[i] = i;
		obj.index_buffer[i]=i;
	}
	for (int i =0; i<3; i++)
	{
		//obj.index_buffer[i] = i;
		obj.index_buffer[i+3]=2*i+1;
	}
	obj.index_buffer[3]=1;
	obj.index_buffer[4]=0;
	obj.index_buffer[5]=3;
	
//		for (int i =0; i<6; i++)
//	{
//		std::cout << obj.index_buffer[i] << std::endl;
//	}



					 


}



void render(GLuint gVBO, GLuint gIBO, GLuint gProgramID)
{
	//Clear color buffer
	glClear( GL_COLOR_BUFFER_BIT );
	

		//Bind program
		glUseProgram( gProgramID );

		//Enable vertex position
		glEnableVertexAttribArray( gVertexPos2DLocation );

		//Set vertex data
		glBindBuffer( GL_ARRAY_BUFFER, gVBO );
		glVertexAttribPointer( gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL );

		//Set index data and render
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, gIBO );
		glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL );

		//Disable vertex position
		glDisableVertexAttribArray( gVertexPos2DLocation );

		//Unbind program
		//glUseProgram( NULL );
	
}




int main( int argc, char* args[] )
{
	GLuint gVBO = 0;
	GLuint gIBO = 0;
	//Start up SDL and create window
	Window_Class window = Window_Class(60,SDL_WINDOW_OPENGL| SDL_WINDOW_SHOWN ); 
	GPUcodes gpucodes0=GPUcodes("shader0");
	gpucodes0.Load("simple0","simple1", "simple");
	gpucodes0.EnableProgram("simple");
	
	
	//Get vertex attribute location
	gVertexPos2DLocation = glGetAttribLocation( gpucodes0.glprograms[0], "aPos" );
	if( gVertexPos2DLocation == -1 )
	{
		printf( "LVertexPos2D is not a valid glsl program variable!\n" );
		return false;
	}

	//Initialize clear color
	glClearColor( 0.f, 0.f, 0.f, 1.f );

	VectorizedObject Spaceship{VectorizedObject(2,3,1,2)};
	
	GenTriangle(Spaceship);
	Spaceship.SetToOrigin(0);

	//IBO data
	Spaceship.Prepare(gVBO, gIBO);

	int width, height, nrChannels;
	unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0); 
			
		
	

		
		//Enable text input
		float color=1, angle=0; 
		//Enable text input
		GLint status = glGetUniformLocation(gpucodes0.glprograms[0], "status");

		const Uint8* kb = SDL_GetKeyboardState(NULL);

	
		//While application is running
		while( window.IsAlive() )
		{
			window.CycleStart();
			
			//shootDirectionY = -kb[SDL_SCANCODE_UP] + kb[SDL_SCANCODE_DOWN];
			Spaceship.position[0] += 0.02*(-kb[SDL_SCANCODE_LEFT] + kb[SDL_SCANCODE_RIGHT]) - 2*float(Spaceship.position[0]>1.0) + 2*float(Spaceship.position[0]<-1.0);
			Spaceship.position[1] += 0.02*(-kb[SDL_SCANCODE_DOWN] + kb[SDL_SCANCODE_UP]) - 2*float(Spaceship.position[1]>1.0) + 2*float(Spaceship.position[1]<-1.0);
	
			glProgramUniform3f(gpucodes0.glprograms[0],status,angle,Spaceship.position[0],Spaceship.position[1]);
			render(gVBO,gIBO,gpucodes0.glprograms[0]);

			//Update screen
			window.CycleEnd();
		}

	return 0;
}
