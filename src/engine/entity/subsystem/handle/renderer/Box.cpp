/*
 * Box.cpp
 *
 *  Created on: 08.02.2015
 *      Author: aschaeffer
 */

#include "Box.h"
#include "fpsgame/game.h"
#include "engine.h"

namespace inexor {
namespace entity {
namespace particle {

Box::Box() : EntityFunction(RENDERER_CUBE_FUNCTION)
{
}

Box::~Box()
{
}

void Box::Before(TimeStep time_step, EntityInstance* handle_renderer)
{
    glPushMatrix();
    lineshader->set();
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor4f(0.1f, 1.0f, 0.9f, 0.2f);
    glBegin(GL_QUADS);
}

void Box::Execute(TimeStep time_step, EntityInstance* handle_renderer, EntityInstance* handle)
{
    vec pmin((*handle)[POS]->vec3Val);
    vec pmax(pmin);
    pmin.sub((*handle)[DIM]->vec3Val);
    pmax.add((*handle)[DIM]->vec3Val);
    // FRONT
    glVertex3d(pmin.x, pmin.y, pmin.z);
    glVertex3d(pmax.x, pmin.y, pmin.z);
    glVertex3d(pmax.x, pmax.y, pmin.z);
    glVertex3d(pmin.x, pmax.y, pmin.z);
    // BACK
    glVertex3d(pmax.x, pmax.y, pmax.z);
    glVertex3d(pmin.x, pmax.y, pmax.z);
    glVertex3d(pmin.x, pmin.y, pmax.z);
    glVertex3d(pmax.x, pmin.y, pmax.z);
    // RIGHT
    glVertex3d(pmax.x, pmax.y, pmax.z);
    glVertex3d(pmax.x, pmax.y, pmin.z);
    glVertex3d(pmax.x, pmin.y, pmin.z);
    glVertex3d(pmax.x, pmin.y, pmax.z);
    // LEFT
    glVertex3d(pmin.x, pmin.y, pmin.z);
    glVertex3d(pmin.x, pmax.y, pmin.z);
    glVertex3d(pmin.x, pmax.y, pmax.z);
    glVertex3d(pmin.x, pmin.y, pmax.z);
    // TOP
    glVertex3d(pmax.x, pmax.y, pmax.z);
    glVertex3d(pmin.x, pmax.y, pmax.z);
    glVertex3d(pmin.x, pmax.y, pmin.z);
    glVertex3d(pmax.x, pmax.y, pmin.z);
    // BOTTOM
    glVertex3d(pmin.x, pmin.y, pmin.z);
    glVertex3d(pmin.x, pmin.y, pmax.z);
    glVertex3d(pmax.x, pmin.y, pmax.z);
    glVertex3d(pmax.x, pmin.y, pmin.z);
}

void Box::After(TimeStep time_step, EntityInstance* handle_renderer)
{
    glEnd();
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glPopMatrix();
}

}
}
}
