#pragma once

#include <algorithm>

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/dataview.h>
#include <wx/settings.h>

#include "theme.hpp"

namespace pt::UI
{
    // Flat progress bar drawn with the user-selected colour. Replaces
    // wxDataViewProgressRenderer, whose native drawing looks wrong in
    // the dark and gray themes.
    class ColoredProgressRenderer : public wxDataViewCustomRenderer
    {
    public:
        ColoredProgressRenderer()
            : wxDataViewCustomRenderer("long", wxDATAVIEW_CELL_INERT, wxALIGN_NOT),
            m_value(0)
        {
        }

        bool SetValue(const wxVariant& value) override
        {
            m_value = static_cast<int>(std::clamp(value.GetLong(), 0L, 100L));
            return true;
        }

        bool GetValue(wxVariant& value) const override
        {
            value = static_cast<long>(m_value);
            return true;
        }

        wxSize GetSize() const override
        {
            return GetView()
                ? GetView()->FromDIP(wxSize(50, 14))
                : wxSize(50, 14);
        }

        bool Render(wxRect rect, wxDC* dc, int) override
        {
            int const margin = GetView() ? GetView()->FromDIP(2) : 2;
            rect.Deflate(margin, margin + 1);

            if (rect.width <= 2 || rect.height <= 2)
            {
                return true;
            }

            bool const dark = IsDarkTheme();
            wxColour const bg = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW);

            wxColour const track = dark ? bg.ChangeLightness(135) : wxColour(0xe6, 0xe6, 0xe6);
            wxColour const border = dark ? bg.ChangeLightness(165) : wxColour(0xbc, 0xbc, 0xbc);

            dc->SetPen(wxPen(border));
            dc->SetBrush(wxBrush(track));
            dc->DrawRectangle(rect);

            int const inner = rect.width - 2;
            int const filled = inner * m_value / 100;

            if (filled > 0)
            {
                wxColour const fill = ProgressColors::Get();
                dc->SetPen(*wxTRANSPARENT_PEN);
                dc->SetBrush(wxBrush(fill));
                dc->DrawRectangle(rect.x + 1, rect.y + 1, filled, rect.height - 2);
            }

            return true;
        }

    private:
        int m_value;
    };
}
