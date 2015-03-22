/*
 * EntityTypeManager.h
 *
 *  Created on: 24.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_ENTITYTYPEMANAGER_H_
#define SRC_ENGINE_ENTITY_ENTITYTYPEMANAGER_H_

#include "../EntitySystemBase.h"
#include "../domain/TypeRefPtr.h"
#include "../domain/graph/EntityType.h"
#include "../provider/EntityTypeProvider.h"
#include "../factory/EntityTypeFactory.h"

namespace inexor {
namespace entity {

class EntityTypeManager
{
    public:
        EntityTypeManager();
        virtual ~EntityTypeManager();

        TypeRefPtr<EntityType> Create(std::string entity_type_name, bool persist, bool synchronize);
        TypeRefPtr<EntityType> Create(std::string entity_type_name, bool persist, bool synchronize, TypeRefPtr<EntityType> parent_type);
        TypeRefPtr<EntityType> Create(std::string factory_name, std::string entity_type_name_suffix);

        void RegisterType(std::string entity_type_name, TypeRefPtr<EntityType> entity_type);
        void RegisterProvider(CefRefPtr<EntityTypeProvider> entity_type_provider);
        void RegisterFactory(CefRefPtr<EntityTypeFactory> entity_type_factory);

        TypeRefPtr<EntityType> Get(std::string entity_type_name);
        bool Exists(std::string entity_type_name);

        int Size();

    private:
        std::map<std::string, TypeRefPtr<EntityType> > entity_types;

        std::map<std::string, CefRefPtr<EntityTypeFactory> > entity_type_factories;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(EntityTypeManager);

};

}
}

#endif /* SRC_ENGINE_ENTITY_ENTITYTYPEMANAGER_H_ */
