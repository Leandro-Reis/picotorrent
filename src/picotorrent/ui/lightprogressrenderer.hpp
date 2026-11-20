#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/dataview.h>

#include <windows.h>
#include <uxtheme.h>
#include <vssym32.h>

#pragma comment(lib, "uxtheme.lib")

#include "theme.hpp"

namespace pt::UI
{
    // The stock progress renderer, unchanged in the light theme. In the dark
    // and gray themes the list window carries the Windows dark theme, which
    // turns the native bar white. There we draw the very same native bar
    // (same size, same parts) but with the regular, light Windows theme, so
    // it looks exactly like it does in light mode (green).
    class LightProgressRenderer : public wxDataViewProgressRenderer
    {
    public:
        LightProgressRenderer(wxDataViewCellMode mode = wxDATAVIEW_CELL_INERT)
            : wxDataViewProgressRenderer(wxEmptyString, "long", mode)
        {
        }

        bool Render(wxRect rect, wxDC* dc, int state) override
        {
            if (!IsDarkTheme())
            {
                return wxDataViewProgressRenderer::Render(rect, dc, state);
            }

            // nullptr window => default (light) theme, not the dark one.
            HTHEME theme = ::OpenThemeData(nullptr, L"PROGRESS");

            if (!theme)
            {
                return wxDataViewProgressRenderer::Render(rect, dc, state);
            }

            wxVariant v;
            GetValue(v);
            long value = v.GetLong();
            if (value < 0) { value = 0; }
            if (value > 100) { value = 100; }

            wxDC::TempHDC tempHdc = dc->GetTempHDC();
            HDC hdc = static_cast<HDC>(tempHdc.GetHDC());

            wxPoint const origin = dc->GetDeviceOrigin();

            RECT r;
            r.left = rect.x + origin.x;
            r.top = rect.y + origin.y;
            r.right = r.left + rect.width;
            r.bottom = r.top + rect.height;

            ::DrawThemeBackground(theme, hdc, PP_BAR, 0, &r, nullptr);

            RECT content;
            ::GetThemeBackgroundContentRect(theme, hdc, PP_BAR, 0, &r, &content);

            content.right = content.left
                + ::MulDiv(content.right - content.left, static_cast<int>(value), 100);

            ::DrawThemeBackground(theme, hdc, PP_CHUNK, 0, &content, nullptr);
            ::CloseThemeData(theme);

            return true;
        }
    };
}
