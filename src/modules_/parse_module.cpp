#include <vector>
#include <string>
#include <cstring>

#include "../include/safe_include_SDLGL_OpenGL.h"
#include "../objects_/vectorizedobject.h"




#include "./parse_module.h"

int LoadObj(std::string &&  path, VectorizedObject** obj)
{
	printf("Loading OBJ file %s...\n", path.c_str());

	std::vector<int> vertexIndices, uvIndices, normalIndices;
	std::vector<float> temp_vertices; 
	std::vector<float> temp_uvs;
	std::vector<float> temp_normals;
	
	

	FILE * file = fopen(path.c_str(), "r");
	if( file == NULL ){
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		getchar();
		return false;
	}

	while( 1 )
	{

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF) break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader
		
		if ( strcmp( lineHeader, "v" ) == 0 )
		{
			float x,y,z;
			fscanf(file, "%f %f %f\n", &x, &y, &z );
			temp_vertices.push_back(x);
			temp_vertices.push_back(y);
			temp_vertices.push_back(z);
		}
		else if ( strcmp( lineHeader, "vt" ) == 0 )
		{
			float x,y;
			fscanf(file, "%f %f\n", &x, &y );
			//uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(x);
			temp_uvs.push_back(-y);
		}
		else if ( strcmp( lineHeader, "vn" ) == 0 )
		{
			float x,y,z;
			fscanf(file, "%f %f %f\n", &x, &y, &z );
			temp_normals.push_back(x);
			temp_normals.push_back(y);
			temp_normals.push_back(z);
		}
		else if ( strcmp( lineHeader, "f" ) == 0 )
		{	
			char* tmpbuffer = (char*)malloc(sizeof(char)*256);
			fgets(tmpbuffer,256,file);
			//fscanf(file, "%s", tmpbuffer);
			int vertexIndex[4], uvIndex[4], normalIndex[4];
			
			
			int check = sscanf(tmpbuffer, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", 
		   	    &vertexIndex[0], &uvIndex[0], &normalIndex[0],
			    &vertexIndex[1], &uvIndex[1], &normalIndex[1],
			    &vertexIndex[2], &uvIndex[2], &normalIndex[2],
			    &vertexIndex[3], &uvIndex[3], &normalIndex[3]);
			    
			//printf("%s  %d\n", tmpbuffer, check );
			   
			if (check == 9)
			{
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices    .push_back(uvIndex[0]);
				uvIndices    .push_back(uvIndex[1]);
				uvIndices    .push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
			else if(check == 12) 
			{
			
	
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices    .push_back(uvIndex[0]);
				uvIndices    .push_back(uvIndex[1]);
				uvIndices    .push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
						 	
			 	vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[3]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices    .push_back(uvIndex[0]);
				uvIndices    .push_back(uvIndex[3]);
				uvIndices    .push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[3]);
				normalIndices.push_back(normalIndex[2]);
				
				//printf("quad\n");
			 
			 
			 
			 } 
			 else
			 {
			 	printf("Error, format not understood\n"); 
			    	return 1; 
			 }
			 free(tmpbuffer);
			
			
			
		}
		else
		{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}
	
	unsigned int vals = 8;
	unsigned int vertnum = vertexIndices.size(); 
	unsigned int idxnum  = vertexIndices.size();
	int* idx = new int[idxnum];
	float* buffer = new float[idxnum*vals];

	*obj = new VectorizedObject(8,vertnum, idxnum,3,GL_TRIANGLES);
	
	// For each vertex of each triangle
	for( unsigned int i=0; i<idxnum; i++){

		// Get the indices of its attributes
		int vertexIndex = abs(vertexIndices[i]);
		int uvIndex = abs(uvIndices[i]);
		int normalIndex = abs(normalIndices[i]);
		
		idx[i] = i;
		// Get the attributes thanks to the index
		buffer[vals*i+0] = temp_vertices[3*(vertexIndex-1)+0];
		buffer[vals*i+1] = temp_vertices[3*(vertexIndex-1)+1];
		buffer[vals*i+2] = temp_vertices[3*(vertexIndex-1)+2];
		
		buffer[vals*i+3] = temp_uvs[2*(uvIndex-1)+0];
		buffer[vals*i+4] = temp_uvs[2*(uvIndex-1)+1];
		
		
		buffer[vals*i+5]=temp_normals[3*(normalIndex-1)+0];
		buffer[vals*i+6]=temp_normals[3*(normalIndex-1)+1];
		buffer[vals*i+7]=temp_normals[3*(normalIndex-1)+2];
		
		//std::cout << buffer[vals*i+5] << "  "
		//	<< buffer[vals*i+6] << "  "
		//	<< buffer[vals*i+7] << "  " << std::endl;
		// Put the attributes in buffers
		//out_vertices.push_back(vertex);
		//out_uvs     .push_back(uv);
		//out_normals .push_back(normal);
	
	}
	
	//ResetOrigin();
	fclose(file);
	printf("Done!\n");
	 
	 return 0;

}





//https://github.com/chinedufn/collada-dae-parser/blob/master/src/parse-collada.js
//For collada use XML parser (Rapid XML) and then look up other that did that with js
