/* 
*	       GEOMETRY MODULE
* Geometry routines to generate basic shapes
* Objects in input should be of the right size
*/



#ifndef GEOMETRY
#define GEOMETRY

class VectorizedObject;
class ColliderObject2D;


void GenTriangle(VectorizedObject& obj);
void GenQuad(VectorizedObject& obj);
void GenQuadText(VectorizedObject& obj);
void GenQuad2TText(VectorizedObject& obj);
void GenQuad2T(VectorizedObject& obj);
void GenQuad2TColor(VectorizedObject& obj,float xa,float ya,float x1,float y1);
void SetColor(VectorizedObject *obj,int sides_, float r,float g,float b, float a);
void GenPolygon(VectorizedObject *obj, int sides_, float radius_);
void GenPolygonCollider(ColliderObject2D *obj, int sides_, bool colored);
template<typename T>
void JoinBufferInstances(T* a_, int stridea_,  T* b_, int strideb_, T* c);
void GenColoredPolygon(VectorizedObject *obj, int sides_, float radius_, float r,float g,float b, float a);
void GenColorQuad(VectorizedObject& obj, float xa,float ya,float x1,float y1);
#endif


