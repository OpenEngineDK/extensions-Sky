// Sky dome
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _SKY_DOME_H_
#define _SKY_DOME_H_

#include <Scene/ISceneNode.h>
#include <Resources/ITextureResource.h>
#include <Geometry/FaceSet.h>

#include <Utils/PropertyList.h>

#include <vector>

using namespace OpenEngine::Scene;
using namespace OpenEngine::Utils;
using namespace OpenEngine::Resources;
using namespace OpenEngine::Geometry;

namespace OpenEngine {
namespace Sky {

  /**
   * 
   */
  class SkyDome {
  private:
  	ISceneNode* sceneNode;
	
	std::vector< Vector<3,float> > positions;
	std::vector< Vector<2,float> > texCoords;
  	
  	FaceSet* CreateDome(int horiRes, int vertRes, float texturePercentage, float domePercentage, float radius, Vector<3,float> center, ITextureResourcePtr texture);
  	FacePtr CreateDomeFace(int i1, int i2, int i3, ITextureResourcePtr texture);
	
  public:
	SkyDome(PropertyList* plist);
	virtual ~SkyDome();
	virtual ISceneNode* GetSceneNode();
  };

}
}

#endif // _SKY_DOME_H_
