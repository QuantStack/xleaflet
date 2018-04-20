/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XLEAFLET_POLYLINE_HPP
#define XLEAFLET_POLYLINE_HPP

#include <array>

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xpath.hpp"

namespace xlf
{
    /************************
     * polyline declaration *
     ************************/

    template <class D>
    class xpolyline : public xpath<D>
    {
    public:

        using point_type = std::array<double, 2>;

        using base_type = xpath<D>;
        using derived_type = D;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XPROPERTY(std::vector<point_type>, derived_type, locations);
        XPROPERTY(float, derived_type, smooth_factor, 1.0);
        XPROPERTY(bool, derived_type, no_clip, false);

    protected:

        xpolyline();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using polyline = xw::xmaterialize<xpolyline>;

    using polyline_generator = xw::xgenerator<xpolyline>;

    /****************************
     * xpolyline implementation *
     ****************************/

    template <class D>
    inline void xpolyline<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xw::set_patch_from_property(locations, state, buffers);
        xw::set_patch_from_property(smooth_factor, state, buffers);
        xw::set_patch_from_property(no_clip, state, buffers);
    }

    template <class D>
    inline void xpolyline<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        xw::set_property_from_patch(locations, patch, buffers);
        xw::set_property_from_patch(smooth_factor, patch, buffers);
        xw::set_property_from_patch(no_clip, patch, buffers);
    }

    template <class D>
    inline xpolyline<D>::xpolyline()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xpolyline<D>::set_defaults()
    {
        this->_model_name() = "LeafletPolylineModel";
        this->_view_name() = "LeafletPolylineView";

        this->locations() = {};

        this->options().insert(
            this->options().end(),
            {
                "smooth_factor",
                "no_clip"
            }
        );
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xlf::xpolyline>;
    extern template xw::xmaterialize<xlf::xpolyline>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xlf::xpolyline>>;
    extern template class xw::xgenerator<xlf::xpolyline>;
    extern template xw::xgenerator<xlf::xpolyline>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xlf::xpolyline>>;
#endif

#endif
