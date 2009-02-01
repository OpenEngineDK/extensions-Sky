// Node that disables lighting on all subnodes.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _DISABLE_LIGHTING_NODE_H_
#define _DISABLE_LIGHTING_NODE_H_

#include <Meta/OpenGL.h>
#include <Scene/RenderNode.h>
#include <Renderers/IRenderingView.h>

namespace OpenEngine {
namespace Renderers {

using OpenEngine::Scene::RenderNode;
using OpenEngine::Renderers::IRenderingView;

class DisableLightingNode : public RenderNode {
public:
    virtual void Apply(IRenderingView* view) {
    	GLboolean lighting = glIsEnabled(GL_LIGHTING);
    	glDisable(GL_LIGHTING);
    	
    	VisitSubNodes(*view);
    	
    	if (lighting) {
    		glEnable(GL_LIGHTING);
    	} 
    }
};

} // NS Renderers
} // NS OpenEngine

#endif // _DISABLE_LIGHTING_NODE_H_
