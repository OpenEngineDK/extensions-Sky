// Sky box
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _SKY_BOX_H_
#define _SKY_BOX_H_

#include <Scene/ISceneNode.h>
#include <Resources/ITextureResource.h>
#include <Geometry/FaceSet.h>

#include <Utils/PropertyList.h>

using namespace OpenEngine::Scene;
using namespace OpenEngine::Utils;
using namespace OpenEngine::Resources;
using namespace OpenEngine::Geometry;

namespace OpenEngine {
namespace Sky {

  /**
   * 
   */
  class SkyBox{
  private:
  	float size;
  	ISceneNode* sceneNode;
	ITextureResourcePtr textures[6];
  	
  	FaceSet* CreatePlane(int dir, float displacement, ITextureResourcePtr tex);
	
  public:
	SkyBox(PropertyList* plist);
	virtual ~SkyBox();
	virtual ISceneNode* GetSceneNode();
  };

}
}

#endif // _SKY_BOX_H_
