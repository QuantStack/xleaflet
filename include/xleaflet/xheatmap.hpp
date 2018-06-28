/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_HEATMAP_HPP
#define XLEAFLET_HEATMAP_HPP

#include <string>
#include <array>
#include <vector>

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xleaflet_config.hpp"
#include "xraster_layer.hpp"

namespace xlf
{
    /***********************
     * heatmap declaration *
     ***********************/

    template <class D>
    class xheatmap : public xraster_layer<D>
    {
    public:

        // Lat, lng, intensity
        using point_type = std::array<double, 3>;
        using locations_type = std::vector<point_type>;

        using base_type = xraster_layer<D>;
        using derived_type = D;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XPROPERTY(locations_type, derived_type, locations);
        XPROPERTY(float, derived_type, min_opacity, 0.05);
        XPROPERTY(int, derived_type, max_zoom, 18);
        XPROPERTY(float, derived_type, max, 1.0);
        XPROPERTY(float, derived_type, radius, 25.0);
        XPROPERTY(float, derived_type, blur, 15.0);
        XPROPERTY(xeus::xjson, derived_type, gradient);

    protected:

        xheatmap();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using heatmap = xw::xmaterialize<xheatmap>;

    using heatmap_generator = xw::xgenerator<xheatmap>;

    /**************************
     * heatmap implementation *
     **************************/

    template <class D>
    inline void xheatmap<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xw::set_patch_from_property(locations, state, buffers);
        xw::set_patch_from_property(min_opacity, state, buffers);
        xw::set_patch_from_property(max_zoom, state, buffers);
        xw::set_patch_from_property(max, state, buffers);
        xw::set_patch_from_property(radius, state, buffers);
        xw::set_patch_from_property(blur, state, buffers);
        xw::set_patch_from_property(gradient, state, buffers);
    }

    template <class D>
    inline void xheatmap<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        xw::set_property_from_patch(locations, patch, buffers);
        xw::set_property_from_patch(min_opacity, patch, buffers);
        xw::set_property_from_patch(max_zoom, patch, buffers);
        xw::set_property_from_patch(max, patch, buffers);
        xw::set_property_from_patch(radius, patch, buffers);
        xw::set_property_from_patch(blur, patch, buffers);
        xw::set_property_from_patch(gradient, patch, buffers);
    }

    template <class D>
    inline xheatmap<D>::xheatmap()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xheatmap<D>::set_defaults()
    {
        this->_model_name() = "LeafletHeatmapModel";
        this->_view_name() = "LeafletHeatmapView";

        this->gradient() = {
            {"0.4", "blue"},
            {"0.6", "cyan"},
            {"0.7", "lime"},
            {"0.8", "yellow"},
            {"1.0", "red"}
        };

        this->options().insert(
            this->options().end(),
            {
                "min_opacity",
                "max_zoom",
                "max",
                "radius",
                "blur",
                "gradient"
            }
        );
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xlf::xheatmap>;
    extern template xw::xmaterialize<xlf::xheatmap>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xlf::xheatmap>>;
    extern template class xw::xgenerator<xlf::xheatmap>;
    extern template xw::xgenerator<xlf::xheatmap>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xlf::xheatmap>>;
#endif

#endif
