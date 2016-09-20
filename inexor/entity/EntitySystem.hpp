/*
 * EntitySystem.h
 *
 *  Created on: 17.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_ENTITYSYSTEM_H_
#define SRC_ENGINE_ENTITY_ENTITYSYSTEM_H_

#include <typeinfo>

#include "inexor/entity/EntitySystemBase.hpp"
#include "inexor/entity/domain/InstanceBase.hpp"
#include "inexor/entity/domain/TimeStep.hpp"
#include "inexor/entity/domain/TypeBase.hpp"
#include "inexor/entity/domain/graph/EntityInstance.hpp"
#include "inexor/entity/domain/graph/EntityType.hpp"
#include "inexor/entity/domain/graph/RelationshipType.hpp"
#include "inexor/entity/domain/graph/RelationshipInstance.hpp"
#include "inexor/entity/manager/EntityInstanceManager.hpp"
#include "inexor/entity/manager/EntityTypeManager.hpp"
#include "inexor/entity/manager/RelationshipInstanceManager.hpp"
#include "inexor/entity/manager/RelationshipTypeManager.hpp"
#include "inexor/entity/subsystem/SubsystemBase.hpp"
// #include "inexor/entity/subsystem/HandleSubsystem.hpp"
// #include "inexor/entity/subsystem/TeleportSubsystem.hpp"
// #include "inexor/entity/subsystem/particle/ParticleSubsystem.hpp"

namespace inexor {
namespace entity {

    struct type_info_less
    {
        bool operator() (const std::type_info* lhs, const std::type_info* rhs) const
        {
            return lhs->before(*rhs) != 0;
        }
    };

    class EntitySystem;

    typedef std::map<std::type_info const*, void *, type_info_less> TypenameToObject;
    typedef std::map<std::type_info const*, void *, type_info_less>::iterator TypeMapIterator;

    class TypeMap
    {
        friend class EntitySystem;

        TypenameToObject ObjectMap;

        public:
            template <typename T>
            T *Get () const
            {
                TypenameToObject::const_iterator iType = ObjectMap.find(&typeid(T));
                if (iType == ObjectMap.end())
                    return NULL;
                return reinterpret_cast<T *>(iType->second);
            }
            template <typename T>
            void Set(T *value)
            {
                ObjectMap[&typeid(T)] = reinterpret_cast<void *>(value);
            }
    };

    class EntitySystem
    {
        public:
            EntitySystem();
            virtual ~EntitySystem();

            /**
             * Initializes the providers.
             */
            void InitProviders();

            /**
             * Initializes the subsystems.
             */
            void InitSubsystems();

            /**
             * Frame update (main thread).
             */
            void Update();

            /**
             * Cleanup at shutdown.
             */
            void Cleanup();

            /**
             * Called on a GFX reset. Each subsystem's Reset() method is called
             * for cleanup purposes.
             */
            void Reset();

            /**
             * Returns a typed reference to the concrete subsystem. You can
             * retrieve the subsystem with it's original type from everywhere.
             */
            template <typename T>
            T *GetSubsystem () const
            {
                return subsystemTypeMap.Get<T>();
            }

            /**
             * Save the current entity system.
             * TODO: export to JSON
             */
            void Save(std::string filename);

            /**
             * Loads a entity system from file.
             // TODO: import from JSON
             */
            void Load(std::string filename);

            /**
             * Reset timer.
             */
            void ResetTimer();

            /**
             * Sets the time unit.
             */
            void SetTimeUnit(double time_unit);

            /**
             * Returns the entity type manager which is responsible for
             * managing the entity types.
             */
            std::shared_ptr<EntityTypeManager> GetEntityTypeManager();

            /**
             * Returns the relationship type manager which is responsible for
             * managing the relationship types.
             */
            std::shared_ptr<RelationshipTypeManager> GetRelationshipTypeManager();

            /**
             * Returns the entity instance manager which is responsible for
             * managing the entity instances.
             */
            std::shared_ptr<EntityInstanceManager> GetEntityInstanceManager();

            /**
             * Returns the relationship instance manager which is responsible for
             * managing the relationship instances.
             */
            std::shared_ptr<RelationshipInstanceManager> GetRelationshipInstanceManager();

            /**
             * Adds a subsystem.
             */
            template<typename T, typename = std::enable_if<std::is_base_of<SubsystemBase, T>::value>> void RegisterSubsystem(std::shared_ptr<T> subsystem_ref_ptr) {
                subsystemTypeMap.Set<T>(subsystem_ref_ptr.get());
                subsystems.push_back(subsystem_ref_ptr);
            };

        private:

            /**
             * Frame calculation: The current frame millis.
             */
            int frame_millis;

            /**
             * Frame calculation: The last frame millis.
             */
            int frame_last_millis;

            /**
             * Frame calculation: The elapsed millis since the last frame.
             */
            int elapsed_millis;

            /**
             * The time unit in milliseconds. Normally set to 1000 for one
             * second.
             *
             * The time unit is used for timing calculations. In the particle
             * system a rate of 10 would mean to spawn 10 particles per time
             * unit. If the time unit is 1000 millis, 10 particles would be
             * spawned within a second. If the gamespeed is lowered the time
             * unit should be reduced, too.
             */
            double time_unit;

            /**
             * The entity type manager.
             */
            std::shared_ptr<EntityTypeManager> entity_type_manager;

            /**
             * The relationship type manager.
             */
            std::shared_ptr<RelationshipTypeManager> relationship_type_manager;

            /**
             * The entity instance manager.
             */
            std::shared_ptr<EntityInstanceManager> entity_instance_manager;

            /**
             * The relationship instance manager.
             */
            std::shared_ptr<RelationshipInstanceManager> relationship_instance_manager;

            /**
             * The list of subsystems to iterate over. Only the common API
             * provided by SubsystemBase is available.
             */
            std::vector<std::shared_ptr<SubsystemBase>> subsystems;

            /**
             * The subsystem type map grants access to the real type of the
             * implemented subsystem.
             */
            TypeMap subsystemTypeMap;

    };

}
}

/**
 * Provide the entity system as global reference.
 */
extern std::shared_ptr<inexor::entity::EntitySystem> entity_system;

#endif /* SRC_ENGINE_ENTITY_ENTITYSYSTEM_H_ */
