#include "StarAnimationControl.h"

#include "CUIControls.h"
#include "CUIDrawUtil.h"

#include "../util/Logger.h"
#include "../util/OptionsDB.h"

#include <GG/GUI.h>
#include <GG/Texture.h>


std::vector<std::shared_ptr<GG::Texture>>& GetCoronaLayerMaskTextures() {
    static std::vector<std::shared_ptr<GG::Texture>> retval;
    if (retval.empty()) {
        retval = ClientUI::GetClientUI()->GetPrefixedTextures(
            ClientUI::ArtDir() / "stars_sidepanel" / "layer_mask", "lm_", false);
    }
    return retval;
}


LayerMaskRenderer StarAnimationControl::s_layermask_shader;


StarAnimationControl::StarAnimationControl(GG::X x, GG::Y y, GG::X w, GG::Y h, int system_id, StarType star_type) :
    GG::Control(x, y, w, h, GG::NO_WND_FLAGS),
    m_system_id(system_id),
    m_star_type(star_type),
    m_layer_mask_textures(GetCoronaLayerMaskTextures())
{
    Refresh();
}


void StarAnimationControl::Refresh() {
    // ScopedTimer timer("StarAnimationControl::Refresh", true);
    m_FPS = 20;

    // load corona and core
    std::string core_name = "yellow_00_core"; // ClientUI::StarTypeFilePrefixes()[system->GetStarType()] + "_00_core";  // yellow_core_00
    std::string corona_name = "yellow_00_corona"; // ClientUI::StarTypeFilePrefixes()[system->GetStarType()] + "_00_corona";

    m_core_texture = ClientUI::GetClientUI()->GetModuloTexture(ClientUI::ArtDir() / "stars_sidepanel", core_name, m_system_id);
    m_corona_texture = ClientUI::GetClientUI()->GetModuloTexture(ClientUI::ArtDir() / "stars_sidepanel", corona_name, m_system_id);

    m_layer_mask_textures = GetCoronaLayerMaskTextures();
}


void StarAnimationControl::Render() {
    GG::Pt ul = UpperLeft(), lr = LowerRight();

    int ms_per_frame = int(std::round(1000 / m_FPS));
    int frame_count = m_layer_mask_textures.size();
    int frame = (int)std::round(GG::GUI::GetGUI()->Ticks() / ms_per_frame) % frame_count;

    DebugLogger() << "Frame: " << frame;

    m_core_texture->OrthoBlit(ul, lr);
    if (GetOptionsDB().Get<bool>("UI.sidepanel.animated-star")) {
        s_layermask_shader.RenderTextureWithLayerMask(ul, lr, m_corona_texture, m_layer_mask_textures[frame]);
    }
    else {
        m_corona_texture->OrthoBlit(ul, lr);
    }
}
