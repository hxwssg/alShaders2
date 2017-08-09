#pragma once

#include "bsdf.hpp"
#include "util.hpp"
#include <ai.h>

namespace a2 {
class BsdfMicrofacet : public Bsdf {
    AtVector2 _roughness;
    float _eta;
    AtRGB _weight;
    uint8_t _distribution;
    AtShaderGlobals* _sg;
    AtVector _omega_o;

public:
    const AtBSDFMethods* arnold_methods;
    AtBSDF* arnold_bsdf;
    AtVector N;
    AtVector U;

    static AtBSDF* create(AtShaderGlobals* sg, AtRGB weight, AtVector N,
                          AtVector U, float medium_ior, float ior, float rx,
                          float ry);

    static BsdfMicrofacet* get(const AtBSDF* bsdf) {
        return reinterpret_cast<BsdfMicrofacet*>(AiBSDFGetData(bsdf));
    }

    void init(const AtShaderGlobals* sg) override;
    AtBSDFLobeMask sample(const AtVector u, const float wavelength,
                          const AtBSDFLobeMask lobe_mask, const bool need_pdf,
                          AtVectorDv& out_wi, int& out_lobe_index,
                          AtBSDFLobeSample out_lobes[],
                          AtRGB& transmission) override;
    AtBSDFLobeMask eval(const AtVector& wi, const AtBSDFLobeMask lobe_mask,
                        const bool need_pdf, AtBSDFLobeSample out_lobes[],
                        AtRGB& transmission) override;
    const AtBSDFLobeInfo* get_lobes() override;
    int get_num_lobes() override;
};
} // namespace a2
