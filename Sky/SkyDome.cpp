// Sky dome
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include "SkyDome.h"

#include "Meta/OpenGL.h"

#include <Resources/ResourceManager.h>
#include <Renderers/DisableLightingNode.h>
#include <Scene/GeometryNode.h>

#include <string.h>
using std::string;


using std::vector;

using OpenEngine::Renderers::DisableLightingNode;

namespace OpenEngine {
namespace Sky {

  SkyDome::SkyDome(PropertyList* plist) {
	int horiRes                 = plist->GetInt("resolution.horizontal");
	int vertRes                 = plist->GetInt("resolution.vertical");
	float texturePercentage     = plist->GetFloat("texture.percentage");
	float domePercentage        = plist->GetFloat("dome.percentage");
	float radius                = plist->GetFloat("dome.radius");
    Vector<3,float> center      = plist->GetVector<3,float>("dome.center");
    ITextureResourcePtr texture = ResourceManager<ITextureResource>::Create(plist->GetString("texture"));
    
    FaceSet* faces = CreateDome(horiRes, vertRes, texturePercentage, domePercentage, radius, center, texture);
    
    sceneNode = new DisableLightingNode();
    sceneNode->AddNode(new GeometryNode(faces));
  }

  SkyDome::~SkyDome() {

  }
  
  FaceSet* SkyDome::CreateDome(int horiRes, int vertRes, float texturePercentage, float domePercentage, float radius, Vector<3,float> center, ITextureResourcePtr texture) {
  	// COPYRIGHT NOTICE: Code in this method is based on code written by Anders la Cour-Harbo for the irrlicht engine
  
	if (domePercentage < 0.0)	domePercentage =- domePercentage;
	if (domePercentage > 2.0)	domePercentage = 2.0;

	float azimuth = 0.0;
	float azimuth_step = 2.0 * Math::PI / (float)horiRes;
	
	//float elevation; // = Math::PI / 2.0;
	float elevation_step = domePercentage * Math::PI / 2.0 / (float)vertRes;

	const float tcV = (float)texturePercentage / (float)vertRes;
	for (int i = 0; i <= horiRes; i++)	{
		float elevation = Math::PI / 2.0;
		const float tcU = (float)i / (float)horiRes;
		const float sinA = sin(azimuth);
		const float cosA = cos(azimuth);
		for (int j = 0; j <= vertRes; j++) {
			const float cosEr = radius * cos(elevation);
			Vector<3,float> pos((cosEr * sinA),
								(radius * sin(elevation) + 50.0f),
								(cosEr * cosA));
			positions.push_back(pos);
			texCoords.push_back(Vector<2,float>(tcU, (float)j*tcV));

			elevation -= elevation_step;
		}
		azimuth += azimuth_step;
		printf("azimuth: %f\n", azimuth);
	}
	
	FaceSet* faces = new FaceSet();
	for (int i = 0; i < horiRes; i++) {
		faces->Add(CreateDomeFace(vertRes+2+(vertRes+1)*i, 1+(vertRes+1)*i, 0+(vertRes+1)*i, texture));

		for (int j = 1; j < vertRes; j++)	{
			faces->Add(CreateDomeFace(vertRes+2+(vertRes+1)*i+j, 1+(vertRes+1)*i+j, 0+(vertRes+1)*i+j, texture));
			faces->Add(CreateDomeFace(vertRes+1+(vertRes+1)*i+j, vertRes+2+(vertRes+1)*i+j, 0+(vertRes+1)*i+j, texture));
		}
	}
	
	positions.clear();
	texCoords.clear();
	
	return faces;
  }
  
  FacePtr SkyDome::CreateDomeFace(int i1, int i2, int i3, ITextureResourcePtr texture) {
	Vector<3,float> pos1 = positions[i1];
	Vector<3,float> pos2 = positions[i2];
	Vector<3,float> pos3 = positions[i3];
  	FacePtr face = FacePtr(new Face(pos1, pos2, pos3));
	face->texc[0] = texCoords[i1];
	face->texc[1] = texCoords[i2];
	face->texc[2] = texCoords[i3];
	face->mat->texr = texture;
	return face;
  }
  
  ISceneNode* SkyDome::GetSceneNode() {
    return sceneNode;
  }

}
}
