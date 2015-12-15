/// @file fl_enteditor.h
/// @author Johannes Schneider
/// @brief 3D Visual Scripting System's entity editor

#ifndef INEXOR_VSCRIPT_ENTITYMANAGER_HEADER
#define INEXOR_VSCRIPT_ENTITYMANAGER_HEADER

#include "inexor/engine/engine.h"
#include "inexor/flowgraph/node/fl_nodebase.h"


namespace inexor {
namespace vscript {

    class CEntityManager
    {
        protected:

            bool dragging_node;
            bool dragging_new_relation;

            bool moving_entity;
            bool last_mouse_key_state;

            vec move_pos_start;
            vec node_pos_start;

            virtual void process_change(int, bool) = 0;

        public:

            CEntityManager();
            ~CEntityManager();

            bool selection_blocked_by_geometry;

            CScriptNode* selected_node;
            CScriptNode* hovered_node;

            void update_mouse(int, bool);
    };

};
};

#endif
