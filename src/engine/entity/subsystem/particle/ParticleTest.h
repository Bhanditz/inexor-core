/*
 * ParticleTest.h
 *
 *  Created on: 14.02.2015
 *      Author: aschaeffer
 */

#ifndef SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_PARTICLETEST_H_
#define SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_PARTICLETEST_H_

#include "ParticleSubsystem.h"
#include "emitter/Point.h"
#include "initializer/RandomPosition.h"
#include "initializer/RandomVelocity.h"
#include "modifier/DensityFadeout.h"
#include "modifier/GeometryCollide.h"
#include "modifier/GravityPoint.h"
#include "modifier/SimpleGravity.h"
#include "modifier/Rolling.h"
#include "modifier/VelocityTransformation.h"
#include "modifier/VectorField.h"
#include "renderer/Billboard.h"
#include "renderer/Cube.h"
#include "renderer/Model.h"
#include "renderer/Origin.h"

namespace inexor {
namespace entity {
namespace particle {

class ParticleTest
{
    public:
        ParticleTest();
        virtual ~ParticleTest();

    private:

        FunctionRefPtr point_emitter_function;
        FunctionRefPtr random_position_function;
        FunctionRefPtr random_velocity_function;
        FunctionRefPtr density_fadeout_function;
        FunctionRefPtr geometry_collide_function;
        FunctionRefPtr gravity_point_function;
        FunctionRefPtr velocity_transformation_function;
        FunctionRefPtr vector_field_function;
        FunctionRefPtr simple_gravity_function;
        FunctionRefPtr rolling_function;
        FunctionRefPtr billboard_renderer_function;
        FunctionRefPtr cube_renderer_function;
        FunctionRefPtr model_renderer_function;
        FunctionRefPtr origin_renderer_function;

        TypeRefPtr<EntityType> default_particle_type;
        TypeRefPtr<EntityType> point_emitter;
        TypeRefPtr<EntityType> random_position_initializer_type;
        TypeRefPtr<EntityType> random_velocity_initializer_type;
        TypeRefPtr<EntityType> density_fadeout_modifier_type;
        TypeRefPtr<EntityType> geometry_collide_modifier_type;
        TypeRefPtr<EntityType> gravity_point_modifier_type;
        TypeRefPtr<EntityType> velocity_transformation_modifier_type;
        TypeRefPtr<EntityType> vector_field_modifier_type;
        TypeRefPtr<EntityType> simple_gravity_modifier_type;
        TypeRefPtr<EntityType> rolling_modifier_type;
        TypeRefPtr<EntityType> billboard_renderer_type;
        TypeRefPtr<EntityType> cube_renderer_type;
        TypeRefPtr<EntityType> model_renderer_type;
        TypeRefPtr<EntityType> origin_renderer_type;

        InstanceRefPtr<EntityInstance> point_emitter_1;
        InstanceRefPtr<EntityInstance> point_emitter_2;
        InstanceRefPtr<EntityInstance> point_emitter_3;
        InstanceRefPtr<EntityInstance> point_emitter_4;

        InstanceRefPtr<EntityInstance> random_velocity_initializer_1;
        InstanceRefPtr<EntityInstance> random_velocity_initializer_2;
        InstanceRefPtr<EntityInstance> random_position_initializer_1;
        InstanceRefPtr<EntityInstance> random_position_initializer_2;

        InstanceRefPtr<EntityInstance> velocity_transformation_modifier_1;
        InstanceRefPtr<EntityInstance> vector_field_modifier_1;
        InstanceRefPtr<EntityInstance> simple_gravity_modifier_1;
        InstanceRefPtr<EntityInstance> rolling_modifier_1;
        InstanceRefPtr<EntityInstance> geometry_collide_modifier_1;
        InstanceRefPtr<EntityInstance> gravity_point_modifier_1;
        InstanceRefPtr<EntityInstance> gravity_point_modifier_2;
        // InstanceRefPtr<EntityInstance> gravity_point_modifier_3;
        // InstanceRefPtr<EntityInstance> gravity_point_modifier_4;

        InstanceRefPtr<EntityInstance> billboard_renderer_1;
        InstanceRefPtr<EntityInstance> billboard_renderer_2;
        InstanceRefPtr<EntityInstance> billboard_renderer_3;
        InstanceRefPtr<EntityInstance> model_renderer_1;
        InstanceRefPtr<EntityInstance> cube_renderer_1;
        InstanceRefPtr<EntityInstance> origin_renderer_1;

        // InstanceRefPtr<RelationshipInstance> rel_point_emitter_random_velocity_1;
        InstanceRefPtr<RelationshipInstance> rel_point_emitter_random_position_1;
        InstanceRefPtr<RelationshipInstance> rel_point_emitter_random_velocity_2;
        InstanceRefPtr<RelationshipInstance> rel_point_emitter_random_velocity_3;
        InstanceRefPtr<RelationshipInstance> rel_point_emitter_random_velocity_4;
        InstanceRefPtr<RelationshipInstance> rel_point_emitter_random_position_4;

        InstanceRefPtr<RelationshipInstance> rel_point_emitter_velocity_transformation_1;
        InstanceRefPtr<RelationshipInstance> rel_point_emitter_vector_field_1;
        InstanceRefPtr<RelationshipInstance> rel_point_emitter_velocity_transformation_2;
        InstanceRefPtr<RelationshipInstance> rel_point_emitter_gravity_point_modifier_2_1;
        InstanceRefPtr<RelationshipInstance> rel_point_emitter_gravity_point_modifier_2_2;
        // InstanceRefPtr<RelationshipInstance> rel_point_emitter_gravity_point_modifier_2_3;
        // InstanceRefPtr<RelationshipInstance> rel_point_emitter_gravity_point_modifier_2_4;
        InstanceRefPtr<RelationshipInstance> rel_point_emitter_velocity_transformation_3;
        InstanceRefPtr<RelationshipInstance> rel_point_emitter_rolling_1;
        InstanceRefPtr<RelationshipInstance> rel_point_emitter_simple_gravity_1;
        InstanceRefPtr<RelationshipInstance> rel_point_emitter_geometry_collide_modifier_1;
        InstanceRefPtr<RelationshipInstance> rel_point_emitter_velocity_transformation_4;

        InstanceRefPtr<RelationshipInstance> rel_point_emitter_billboard_renderer_1;
        InstanceRefPtr<RelationshipInstance> rel_point_emitter_billboard_renderer_2;
        // InstanceRefPtr<RelationshipInstance> rel_point_emitter_origin_renderer_1;
        InstanceRefPtr<RelationshipInstance> rel_point_emitter_model_renderer_1;
        // InstanceRefPtr<RelationshipInstance> rel_point_emitter_cube_renderer_1;
        InstanceRefPtr<RelationshipInstance> rel_point_emitter_billboard_renderer_3;

        // Include the default reference counting implementation.
        IMPLEMENT_REFCOUNTING(ParticleTest);

};

}
}
}

#endif /* SRC_ENGINE_ENTITY_SUBSYSTEM_PARTICLE_PARTICLETEST_H_ */
