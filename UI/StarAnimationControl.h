#ifndef _StarAnimationControl_h_
#define _StarAnimationControl_h_

#include "CUIControls.h"
#include "CUIDrawUtil.h"

#include "../universe/Enums.h"

#include <GG/Texture.h>

class StarAnimationControl : public GG::Control {
public:
    StarAnimationControl(GG::X x, GG::Y y, GG::X w, GG::Y h, int system_id, StarType star_type);

    void Refresh();
    void Render() override;

private:
    int                                            m_system_id;
    int                                            m_FPS;
    StarType                                       m_star_type;
    std::vector<std::shared_ptr<GG::Texture>>&     m_layer_mask_textures;
    std::shared_ptr<GG::Texture>                   m_core_texture;
    std::shared_ptr<GG::Texture>                   m_corona_texture;

    static LayerMaskRenderer                       s_layermask_shader;
};





#endif _StarAnimationControl_h_