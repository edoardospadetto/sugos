/* 
*	       GEOMETRY MODULE
* Geometry routines to generate basic shapes
* Objects in input should be of the right size
*/

#ifndef GEOMETRY
#define GEOMETRY

void GenTriangle(VectorizedObject& obj);
void GenQuad(VectorizedObject& obj);
void GenQuadText(VectorizedObject& obj);

void SetColor(VectorizedObject *obj,int sides_, float r,float g,float b, float a);
void GenPolygon(VectorizedObject *obj, int sides_, float radius_);
void GenPolygonCollider(ColliderObject2D *obj, int sides_, bool colored);
template<typename T>
void JoinBufferInstances(T* a_, int stridea_,  T* b_, int strideb_, T* c);
void GenColoredPolygon(VectorizedObject *obj, int sides_, float radius_, float r,float g,float b, float a);
#endif


