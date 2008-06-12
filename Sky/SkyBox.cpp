// Sky box
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include "SkyBox.h"

#include "Meta/OpenGL.h"

#include <Resources/ResourceManager.h>
#include <Renderers/DisableLightingNode.h>

#include <Scene/GeometryNode.h>

#include <string.h>
using std::string;

using OpenEngine::Renderers::DisableLightingNode;

namespace OpenEngine {
namespace Sky {

  SkyBox::SkyBox(PropertyList* plist) {
    size = plist->GetFloat("size");
    
    textures[0] = ResourceManager<ITextureResource>::Create(plist->GetString("back"));
    textures[1] = ResourceManager<ITextureResource>::Create(plist->GetString("front"));
    textures[2] = ResourceManager<ITextureResource>::Create(plist->GetString("left"));
    textures[3] = ResourceManager<ITextureResource>::Create(plist->GetString("right"));
    textures[4] = ResourceManager<ITextureResource>::Create(plist->GetString("down"));
    textures[5] = ResourceManager<ITextureResource>::Create(plist->GetString("up"));
    
    float halfSize = size / 2;
    
    FaceSet* faces = new FaceSet();
    for (int i = 0; i < 6; i++) {
      faces->Add(CreatePlane(i, ((i % 2) == 0 ? -halfSize : halfSize), textures[i]));
    }
    
    sceneNode = new DisableLightingNode();
    sceneNode->AddNode(new GeometryNode(faces));
  }

  SkyBox::~SkyBox() {

  }
  
  FaceSet* SkyBox::CreatePlane(int dir, float displacement, ITextureResourcePtr tex) {
    FaceSet* faces = new FaceSet();
    
    float halfSize = size / 2;
    
    Vector<3,float> vertices[4];
    Vector<3,float> norm;
    if (dir == 0 || dir == 1) {         // if front or back  	
      vertices[0] = Vector<3,float>(-halfSize, -halfSize, displacement);
      vertices[1] = Vector<3,float>(-halfSize,  halfSize, displacement);
      vertices[2] = Vector<3,float>( halfSize,  halfSize, displacement);
      vertices[3] = Vector<3,float>( halfSize, -halfSize, displacement);
    } else if (dir == 2 || dir == 3) {	// if right or left
      vertices[0] = Vector<3,float>(displacement, -halfSize, -halfSize);
      vertices[1] = Vector<3,float>(displacement,  halfSize, -halfSize);
      vertices[2] = Vector<3,float>(displacement,  halfSize,  halfSize);
      vertices[3] = Vector<3,float>(displacement, -halfSize,  halfSize);
      norm = Vector<3,float>((displacement < 0 ? 1.0 : -1.0), 0.0, 0.0);
    } else if (dir == 4 || dir == 5) {  // if top or buttom
      vertices[0] = Vector<3,float>(-halfSize, displacement,  halfSize);
      vertices[1] = Vector<3,float>(-halfSize, displacement, -halfSize);
      vertices[2] = Vector<3,float>( halfSize, displacement, -halfSize);
      vertices[3] = Vector<3,float>( halfSize, displacement,  halfSize);
      norm = Vector<3,float>(0.0, (displacement < 0 ? 1.0 : -1.0), 0.0);
    }
    
    FacePtr face1 = FacePtr(new Face(vertices[0], vertices[1], vertices[2]));
    FacePtr face2 = FacePtr(new Face(vertices[2], vertices[3], vertices[0]));
    
    face1->mat->texr = face2->mat->texr = tex;
    
    face1->norm[0] = face1->norm[1] = face1->norm[2] = norm;
    face2->norm[0] = face2->norm[1] = face2->norm[2] = norm;
    
	if (dir == 0 || dir == 3 || dir == 4) {
		face1->texc[0] = Vector<2,float>(0.0, 0.0);
		face1->texc[1] = Vector<2,float>(0.0, 1.0);
		face1->texc[2] = Vector<2,float>(1.0, 1.0);
		face2->texc[0] = face1->texc[2];
		face2->texc[1] = Vector<2,float>(1.0, 0.0);
		face2->texc[2] = face1->texc[0];
	} else if (dir == 1 || dir == 2 || dir == 5) {
		face1->texc[0] = Vector<2,float>(1.0, 0.0);
		face1->texc[1] = Vector<2,float>(1.0, 1.0);
		face1->texc[2] = Vector<2,float>(0.0, 1.0);
		face2->texc[0] = face1->texc[2];
		face2->texc[1] = Vector<2,float>(0.0, 0.0);
		face2->texc[2] = face1->texc[0];
	}
    
    faces->Add(face1);
    faces->Add(face2);
    
    return faces;
  } 
  
  ISceneNode* SkyBox::GetSceneNode() {
    return sceneNode;
  }

}
}
