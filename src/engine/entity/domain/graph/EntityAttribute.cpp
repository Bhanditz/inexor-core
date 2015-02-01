/*
 * EntityAttribute.cpp
 *
 *  Created on: 16.01.2015
 *      Author: aschaeffer
 */

#include "EntityAttribute.h"

EntityAttribute::EntityAttribute() : type(ENTATTR_NULL), initialized(false), name(""), intVal(0), floatVal(0.0f), doubleVal(0.0), stringVal(""), functionVal(0) { }
EntityAttribute::EntityAttribute(bool value) : type(value), initialized(false), name(""), intVal(0), floatVal(0.0f), doubleVal(0.0), stringVal(""), functionVal(0) { }
EntityAttribute::EntityAttribute(int value) : type(ENTATTR_INT), initialized(false), name(""), intVal(value), floatVal(0.0f), doubleVal(0.0), stringVal(""), functionVal(0) { }
EntityAttribute::EntityAttribute(float value) : type(ENTATTR_FLOAT), initialized(false), name(""), intVal(0), floatVal(value), doubleVal(0.0), stringVal(""), functionVal(0) { }
EntityAttribute::EntityAttribute(double value) : type(ENTATTR_DOUBLE), initialized(false), name(""), intVal(0), floatVal(0.0f), doubleVal(value), stringVal(""), functionVal(0) { }
EntityAttribute::EntityAttribute(std::string value) : type(ENTATTR_STRING), initialized(false), name(""), intVal(0), floatVal(0.0f), doubleVal(0.0), stringVal(value), functionVal(0) { }
EntityAttribute::EntityAttribute(FunctionRefPtr value) : type(ENTATTR_FUNCTION), initialized(false), name(""), intVal(0), floatVal(0.0f), doubleVal(0.0), stringVal(""), functionVal(value) { }
EntityAttribute::EntityAttribute(FunctionRefPtr *value) : type(ENTATTR_FUNCTION), initialized(false), name(""), intVal(0), floatVal(0.0f), doubleVal(0.0), stringVal(""), functionVal(*value) { }
EntityAttribute::~EntityAttribute() { }

void EntityAttribute::SetType(int type)
{
    this->type = type;
};
int EntityAttribute::GetType()
{
    return type;
};
void EntityAttribute::SetValue(bool value)
{
    this->type = value;
};
void EntityAttribute::SetValue(int value)
{
    this->type = ENTATTR_INT;
    this->intVal = value;
};
void EntityAttribute::SetValue(float value)
{
    this->type = ENTATTR_FLOAT;
    this->floatVal = value;
};
void EntityAttribute::SetValue(double value)
{
    this->type = ENTATTR_DOUBLE;
    this->doubleVal = value;
};
void EntityAttribute::SetValue(std::string value)
{
    this->type = ENTATTR_STRING;
    this->stringVal = value;
};
void EntityAttribute::SetValue(FunctionRefPtr value)
{
    this->type = ENTATTR_FUNCTION;
    this->functionVal = value;
};
bool EntityAttribute::GetBool()
{
    if (this->type == ENTATTR_TRUE) {
        return ENTATTR_TRUE;
    } else {
        return ENTATTR_FALSE;
    }
};
int EntityAttribute::GetInteger()
{
    if (this->type == ENTATTR_INT) {
        return intVal;
    } else {
        return 0;
    }
};
double EntityAttribute::GetFloat()
{
    if (this->type == ENTATTR_FLOAT) {
        return floatVal;
    } else {
        return 0.0f;
    }
};
double EntityAttribute::GetDouble()
{
    if (this->type == ENTATTR_DOUBLE) {
        return doubleVal;
    } else {
        return 0.0;
    }
};
std::string EntityAttribute::GetString()
{
    if (this->type == ENTATTR_STRING) {
        return stringVal;
    } else {
        return "";
    }
};
FunctionRefPtr EntityAttribute::GetFunction()
{
    if (this->type == ENTATTR_FUNCTION) {
        return functionVal;
    } else {
        return 0;
    }
};

EntityAttribute& EntityAttribute::operator=(const EntityAttribute &attribute) {
    type = attribute.type;
    name = attribute.name;
    intVal = attribute.intVal;
    floatVal = attribute.floatVal;
    doubleVal = attribute.doubleVal;
    stringVal = attribute.stringVal;
    functionVal = attribute.functionVal;
    initialized = true;
    return *this;
};

EntityAttribute& EntityAttribute::operator=(bool* value) {
    this->type = *value;
    return *this;
};

EntityAttribute& EntityAttribute::operator=(int* value) {
    this->type = ENTATTR_INT;
    this->intVal = *value;
    return *this;
};

EntityAttribute& EntityAttribute::operator=(float* value) {
    this->type = ENTATTR_FLOAT;
    this->floatVal = *value;
    return *this;
};

EntityAttribute& EntityAttribute::operator=(double* value) {
    this->type = ENTATTR_DOUBLE;
    this->doubleVal = *value;
    return *this;
};

EntityAttribute& EntityAttribute::operator=(std::string* value) {
    this->type = ENTATTR_STRING;
    this->stringVal = *value;
    return *this;
};

EntityAttribute& EntityAttribute::operator=(FunctionRefPtr* value) {
    this->type = ENTATTR_FUNCTION;
    this->functionVal = *value;
    return *this;
};

EntityAttribute& EntityAttribute::operator=(FunctionRefPtr value) {
    this->type = ENTATTR_FUNCTION;
    this->functionVal = value;
    return *this;
};

void EntityAttribute::operator()(TimeStep time_step)
{
    if (this->type == ENTATTR_FUNCTION) {
        functionVal(time_step);
    }
}

void EntityAttribute::operator()(TimeStep time_step, EntityType* type)
{
    if (this->type == ENTATTR_FUNCTION) {
        functionVal(time_step, type);
    }
}

void EntityAttribute::operator()(TimeStep time_step, EntityType* type, EntityInstance* inst)
{
    if (this->type == ENTATTR_FUNCTION) {
        functionVal(time_step, type, inst);
    }
}

void EntityAttribute::operator()(TimeStep time_step, EntityInstance* inst)
{
    if (this->type == ENTATTR_FUNCTION) {
        functionVal(time_step, inst);
    }
}

void EntityAttribute::operator()(TimeStep time_step, EntityInstance* inst, RelationshipType* rel_type)
{
    if (this->type == ENTATTR_FUNCTION) {
        functionVal(time_step, inst, rel_type);
    }
}

void EntityAttribute::operator()(TimeStep time_step, EntityInstance* inst, RelationshipInstance* rel_inst)
{
    if (this->type == ENTATTR_FUNCTION) {
        functionVal(time_step, inst, rel_inst);
    }
}

void EntityAttribute::operator()(TimeStep time_step, EntityInstance* inst_1, EntityInstance* inst_2)
{
    if (this->type == ENTATTR_FUNCTION) {
        functionVal(time_step, inst_1, inst_2);
    }
}

void EntityAttribute::operator()(TimeStep time_step, EntityInstance* inst_1, EntityInstance* inst_2, RelationshipType* rel_type)
{
    if (this->type == ENTATTR_FUNCTION) {
        functionVal(time_step, inst_1, inst_2, rel_type);
    }
}

void EntityAttribute::operator()(TimeStep time_step, EntityInstance* inst_1, EntityInstance* inst_2, RelationshipInstance* rel_inst)
{
    if (this->type == ENTATTR_FUNCTION) {
        functionVal(time_step, inst_1, inst_2, rel_inst);
    }
}

void EntityAttribute::operator()(TimeStep time_step, RelationshipType* type)
{
    if (this->type == ENTATTR_FUNCTION) {
        functionVal(time_step, type);
    }
}

void EntityAttribute::operator()(TimeStep time_step, RelationshipType* type, RelationshipInstance* inst)
{
    if (this->type == ENTATTR_FUNCTION) {
        functionVal(time_step, type, inst);
    }
}

void EntityAttribute::operator()(TimeStep time_step, RelationshipInstance* inst)
{
    if (this->type == ENTATTR_FUNCTION) {
        functionVal(time_step, inst);
    }
}
