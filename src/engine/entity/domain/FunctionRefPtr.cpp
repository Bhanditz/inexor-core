/*
 * FunctionRefPtr.cpp
 *
 *  Created on: 29.01.2015
 *      Author: aschaeffer
 */

#include "FunctionRefPtr.h"
#include "TypeBase.h"
#include "graph/EntityType.h"
#include "graph/RelationshipType.h"
#include "graph/EntityInstance.h"
#include "graph/EntityAttribute.h"
#include "graph/RelationshipInstance.h"
#include "graph/EntityAttribute.h"
#include "graph/EntityFunction.h"

namespace inexor {
namespace entity {

FunctionRefPtr::FunctionRefPtr() : parent()
{
}

FunctionRefPtr::FunctionRefPtr(EntityFunction* p) : parent(p)
{
}

FunctionRefPtr::FunctionRefPtr(const CefRefPtr<EntityFunction>& r) : parent(r)
{
}

void FunctionRefPtr::operator()(TimeStep time_step)
{
    get()->Execute(time_step);
}

void FunctionRefPtr::operator()(TimeStep time_step, EntityType* type)
{
    get()->Execute(time_step, type);
}

void FunctionRefPtr::operator()(TimeStep time_step, EntityType* type, EntityInstance* inst)
{
    get()->Execute(time_step, type, inst);
}

void FunctionRefPtr::operator()(TimeStep time_step, EntityInstance* inst)
{
    get()->Execute(time_step, inst);
}

void FunctionRefPtr::operator()(TimeStep time_step, EntityInstance* inst, RelationshipType* rel_type)
{
    get()->Execute(time_step, inst, rel_type);
}

void FunctionRefPtr::operator()(TimeStep time_step, EntityInstance* inst, RelationshipInstance* rel_inst)
{
    get()->Execute(time_step, inst, rel_inst);
}

void FunctionRefPtr::operator()(TimeStep time_step, EntityInstance* inst_1, EntityInstance* inst_2)
{
    get()->Execute(time_step, inst_1, inst_2);
}

void FunctionRefPtr::operator()(TimeStep time_step, EntityInstance* inst_1, EntityInstance* inst_2, RelationshipType* rel_type)
{
    get()->Execute(time_step, inst_1, inst_2, rel_type);
}

void FunctionRefPtr::operator()(TimeStep time_step, EntityInstance* inst_1, EntityInstance* inst_2, RelationshipInstance* rel_inst)
{
    get()->Execute(time_step, inst_1, inst_2, rel_inst);
}

void FunctionRefPtr::operator()(TimeStep time_step, RelationshipType* type)
{
    get()->Execute(time_step, type);
}

void FunctionRefPtr::operator()(TimeStep time_step, RelationshipType* type, RelationshipInstance* inst)
{
    get()->Execute(time_step, type, inst);
}

void FunctionRefPtr::operator()(TimeStep time_step, RelationshipInstance* inst)
{
    get()->Execute(time_step, inst);
}

}
}
