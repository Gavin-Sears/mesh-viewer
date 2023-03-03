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
         curMesh++;
      }
      // Last Mesh
      else if (key == 'p' || key == 'P')
      {
         if (curMesh > 0)
         {
            curMesh--;
         }
      }
   }

   void draw() {
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

      if ((rangex >= rangey) || (rangex >= rangez))
      {
         renderer.scale(
            vec3(
               (6.0f / (rangex)), 
               (6.0f / (rangex)), 
               (6.0f / (rangex))
            )
         );
      }
      else if (rangey >= rangez)
      {
         renderer.scale(
            vec3(
               (6.0f / (rangey)),
               (6.0f / (rangey)),
               (6.0f / (rangey))
            )
         );
      }
      else
      {
         renderer.scale(
            vec3(
               (6.0f / (rangez)),
               (6.0f / (rangez)),
               (6.0f / (rangez))
            )
         );
      }

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
   }

protected:
   PLYMesh mesh;
   PLYMesh viewMesh;
   std::vector<PLYMesh> _meshes;
   std::vector<string> fileNames;
   vec3 eyePos = vec3(10, 0, 0);
   vec3 lookPos = vec3(0, 0, 0);
   vec3 up = vec3(0, 1, 0);
   bool MDown = false;
   float Elevation = 0.0f;
   float Azimuth = 0.0f;
   float Radius = 10.0f;
   int curMesh = 0;
};

int main(int argc, char** argv)
{
   MeshViewer viewer;
   viewer.run();
   return 0;
}

