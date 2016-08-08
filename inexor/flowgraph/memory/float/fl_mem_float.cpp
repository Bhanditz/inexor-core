#include "inexor/flowgraph/memory/float/fl_mem_float.hpp"

namespace inexor {
namespace vscript {

    CMemFloatNode::CMemFloatNode(vec position, bool null_allowed, bool negative_allowed, int value, bool const_value)
    {
        type = INEXOR_VSCRIPT_NODE_TYPE_MEMORY_FLOAT;
        pos = position;   
        block.type = INEXOR_VSCRIPT_DATA_TYPE_FLOATING_POINT;
        block.data.double_value = value;
        block.constant_value = const_value;
    }

    CMemFloatNode::~CMemFloatNode()
    {
    }

    void CMemFloatNode::render_additional()
    {
        // render the current integer value
        vec p = pos;
        p.add(vec(boxsize/2));
        p.add(vec(0,0,4));
        // this is a great C++11 feature!
        additional_particle_text = std::to_string(block.data.double_value);
        particle_text(p + vec(0,0,2.0f), additional_particle_text.c_str(), PART_TEXT, 1, INEXOR_VSCRIPT_COLOR_TRIGGERED, 1.0f);
        if(block.constant_value)
        {
            particle_text(p + vec(0,0,3.0f), "constant value", PART_TEXT, 1, INEXOR_VSCRIPT_COLOR_PENDING, 1.0f);
        }
    }

    void CMemFloatNode::increment()
    {
        last_time = this_time;
        if(block.constant_value)
        {
            triggered_color = INEXOR_VSCRIPT_COLOR_PENDING;
            conoutf(CON_DEBUG, "[3DVS-float-increment] can't increment a constant float value!");
        }
        else block.data.double_value += 1.0;
    }

    void CMemFloatNode::decrement()
    {
        last_time = this_time;
        if(block.constant_value)
        {
            triggered_color = INEXOR_VSCRIPT_COLOR_PENDING;
            conoutf(CON_DEBUG, "[3DVS-float-decrement] can't decrement a constant float value!");
        }
        else block.data.double_value -= 1.0;
    }

    void CMemFloatNode::set_value(double set_value)
    {
        last_time = this_time;
        if(block.constant_value)
        {
            triggered_color = INEXOR_VSCRIPT_COLOR_PENDING;
            conoutf(CON_DEBUG, "[3DVS-float-setvalue] can't change constant float value!");
        }
        else block.data.double_value = set_value;
    }

    double CMemFloatNode::get_value()
    {
        return block.data.double_value;
    }

};
};
