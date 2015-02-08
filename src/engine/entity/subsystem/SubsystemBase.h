/*
 * Subsystem.h
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_SUBSYSTEMBASE_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_SUBSYSTEMBASE_H_

#include "../EntitySystemBase.h"
#include "../domain/TimeStep.h"
#include "../manager/EntityTypeManager.h"
#include "../manager/EntityInstanceManager.h"
#include "../manager/RelationshipTypeManager.h"
#include "../manager/RelationshipInstanceManager.h"

/**
 * Base class for subsystem managers.
 */
class SubsystemBase
{
    public:
        SubsystemBase(std::string name);
        SubsystemBase(
            std::string name,
            CefRefPtr<EntityTypeManager> entity_type_manager,
            CefRefPtr<EntityInstanceManager> entity_instance_manager,
            CefRefPtr<RelationshipTypeManager> relationship_type_manager,
            CefRefPtr<RelationshipInstanceManager> relationship_instance_manager
        );
        virtual ~SubsystemBase() {};

        virtual void Update(TimeStep time_step);
        virtual void Cleanup();
        virtual void Reset();

        std::string GetName() { return name; };
        void SetName(std::string) { this->name = name; };

        void SetEntityTypeManager(CefRefPtr<EntityTypeManager> entity_type_manager) { this->entity_type_manager = entity_type_manager; };
        void SetEntityInstanceManager(CefRefPtr<EntityInstanceManager> entity_instance_manager) { this->entity_instance_manager = entity_instance_manager; };
        void SetRelationshipTypeManager(CefRefPtr<RelationshipTypeManager> relationship_type_manager) { this->relationship_type_manager = relationship_type_manager; };
        void SetRelationshipInstanceManager(CefRefPtr<RelationshipInstanceManager> relationship_instance_manager) { this->relationship_instance_manager = relationship_instance_manager; };

    protected:

        std::string name;

        CefRefPtr<EntityTypeManager> entity_type_manager;
        CefRefPtr<RelationshipTypeManager> relationship_type_manager;

        CefRefPtr<EntityInstanceManager> entity_instance_manager;
        CefRefPtr<RelationshipInstanceManager> relationship_instance_manager;

    private:
        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(SubsystemBase);
};

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_SUBSYSTEMBASE_H_ */
