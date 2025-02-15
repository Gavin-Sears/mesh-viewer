//--------------------------------------------------
// Author: Gavin Sears
// Date: Thursday, March 2
// Description: Loads PLY files in ASCII format
//--------------------------------------------------

#include <cmath>
#include <string>
#include <vector>
#include "agl/window.h"
#include "plymesh.h"
#include "osutils.h"
#include <ctime>

using namespace std;
using namespace glm;
using namespace agl;

class MeshViewer : public Window {
public:
   MeshViewer() : Window() {
   }

   void setup() {
      // Getting Models and loading them
      fileNames = GetFilenamesInDir("../models", "ply");
      for (string i : fileNames)
      {
         PLYMesh tempMesh;
         tempMesh.load("../models/" + i);
         _meshes.push_back(tempMesh);
      }
      renderer.loadShader("normals", "../shaders/normals.vs", "../shaders/normals.fs");
      renderer.loadShader("phong-pixel", "../shaders/phong-pixel.vs", "../shaders/phong-pixel.fs");
      renderer.loadShader("phong-vertex", "../shaders/phong-vertex.vs", "../shaders/phong-vertex.fs");
      renderer.loadShader("wobbly", "../shaders/wobbly.vs", "../shaders/wobbly.fs");
      renderer.loadShader("toon", "../shaders/toon.vs", "../shaders/toon.fs");
      
      _shaders.push_back("normals");
      _shaders.push_back("phong-pixel");
      _shaders.push_back("phong-vertex");
      _shaders.push_back("wobbly");
      _shaders.push_back("toon");

      mesh.load("../models/"+ fileNames[0]);
   }

   void mouseMotion(int x, int y, int dx, int dy) {
      if (MDown)
      {
         // Azimuth and Elevation are updated via mouse
         Azimuth -= dx * 0.05f;
         Elevation += dy * 0.05f;
         

         eyePos = vec3(
            Radius * sin(Azimuth) * cos(Elevation), 
            Radius * sin(Elevation), 
            Radius * cos(Azimuth) * cos(Elevation)
         );
      }
   }

   void mouseDown(int button, int mods) {
      MDown = true;
   }

   void mouseUp(int button, int mods) {
      MDown = false;
   }

   void scroll(float dx, float dy) {
      // Scrolling directly affects radius (zoom)
      Radius += dy * 0.05f;

      eyePos = vec3(
         Radius * sin(Azimuth) * cos(Elevation), 
         Radius * sin(Elevation), 
         Radius * cos(Azimuth) * cos(Elevation)
      );
   }

   void keyUp(int key, int mods) {
      PLYMesh tempMesh;

      // Next Mesh
      if (key == 'n' || key == 'N')
      {
         if (curMesh < _meshes.size() - 1 )
         {
            curMesh++;
         }
      }
      // Last Mesh
      else if (key == 'p' || key == 'P')
      {
         if (curMesh > 0)
         {
            curMesh--;
         }
      }
      // Loops through shaders
      else if (key == 's' || key == 'S')
      {
         if (curShad < _shaders.size() - 1)
         {
            curShad++;
         }
         else
         {
            curShad = 0;
         }
         
      }
   }

   void draw() {
      renderer.beginShader(_shaders[curShad]);

      // renderer.setUniform() to set values in shader
      renderer.setUniform("time", elapsedTime());

      float aspect = ((float)width()) / height();
      renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);
      renderer.lookAt(eyePos, lookPos, up);

      // Rotation. Not important at the moment 
      renderer.rotate(vec3(0,0,0));

      // Current Mesh
      viewMesh = _meshes[curMesh];
      
      // Scaling. Corrects based on dimensions
      float rangex = viewMesh._maxBounds.x - viewMesh._minBounds.x;
      float rangey = viewMesh._maxBounds.y - viewMesh._minBounds.y;
      float rangez = viewMesh._maxBounds.z - viewMesh._minBounds.z;
      float maxRange = std::max(rangex, rangey);
      maxRange = std::max(maxRange, rangez);

      renderer.setUniform("maxRange", maxRange);

      renderer.scale(
         vec3(
            ((8.0f / maxRange)), 
            ((8.0f / maxRange)), 
            ((8.0f / maxRange))
         )
      );

      // Translations
      renderer.translate(
         vec3(
            (-0.5f * (viewMesh._maxBounds.x + viewMesh._minBounds.x)),
            (-0.5f * (viewMesh._maxBounds.y + viewMesh._minBounds.y)),
            (-0.5f * (viewMesh._maxBounds.z + viewMesh._minBounds.z))
         )
      );

      renderer.mesh(viewMesh);
      //renderer.teapot(); // for debugging!
      renderer.endShader();
   }

protected:
   PLYMesh mesh;
   PLYMesh viewMesh;
   std::vector<PLYMesh> _meshes;
   std::vector<string> fileNames;
   std::vector<string> _shaders;
   vec3 eyePos = vec3(10, 0, 0);
   vec3 lookPos = vec3(0, 0, 0);
   vec3 up = vec3(0, 1, 0);
   bool MDown = false;
   float Elevation = 0.0f;
   float Azimuth = 0.0f;
   float Radius = 10.0f;
   int curMesh = 0;
   int curShad = 0;
};

int main(int argc, char** argv)
{
   MeshViewer viewer;
   viewer.run();
   return 0;
}

