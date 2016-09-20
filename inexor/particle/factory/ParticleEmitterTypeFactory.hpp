/*
 * ParticleProvider.h
 *
 *  Created on: 25.01.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_FACTORY_PARTICLEEMITTERTYPEFACTORY_H_
#define SRC_ENGINE_ENTITY_FACTORY_PARTICLEEMITTERTYPEFACTORY_H_

#include "inexor/entity/factory/EntityTypeFactory.hpp"
#include "inexor/entity/domain/TypeRefPtr.hpp"
#include "inexor/entity/domain/graph/EntityFunction.hpp"
#include "inexor/entity/domain/graph/EntityType.hpp"
#include "inexor/entity/domain/graph/RelationshipType.hpp"
#include "inexor/entity/manager/EntityTypeManager.hpp"
#include "inexor/entity/manager/RelationshipTypeManager.hpp"
#include "inexor/particle/model/ParticleModel.hpp"

namespace inexor {
namespace entity {
namespace particle {

    class ParticleEmitterTypeFactory : public EntityTypeFactory
    {
        public:

            ParticleEmitterTypeFactory(std::shared_ptr<EntityTypeManager> entity_type_manager);
            virtual ~ParticleEmitterTypeFactory();

            TypeRefPtr<EntityType> Create(std::string name_suffix);
            TypeRefPtr<EntityType> Create(std::string name_suffix, FunctionRefPtr function, std::string particle_type_name, int rate, int batch_size, int lifetime, double mass, double density);

    };

}
}
}

#endif /* SRC_ENGINE_ENTITY_FACTORY_PARTICLEEMITTERTYPEFACTORY_H_ */
