#pragma once

#include <string>
#include <utility>
#include <vector>

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/msw/darkmode.h>
#include <wx/settings.h>

namespace pt::UI
{
    // Palette used when the dark-mode machinery of wxWidgets is enabled.
    // "dark" is a near-black palette, "gray" sits between light and dark.
    class ThemeSettings : public wxDarkModeSettings
    {
    public:
        explicit ThemeSettings(bool gray) : m_gray(gray) { }

        wxColour GetColour(wxSystemColour index) override
        {
            if (m_gray)
            {
                switch (index)
                {
                case wxSYS_COLOUR_BTNSHADOW:
                case wxSYS_COLOUR_ACTIVECAPTION:
                case wxSYS_COLOUR_APPWORKSPACE:
                case wxSYS_COLOUR_INFOBK:
                case wxSYS_COLOUR_LISTBOX:
                case wxSYS_COLOUR_WINDOW:
                case wxSYS_COLOUR_BTNFACE:
                    return wxColour(0x4b, 0x4b, 0x4b);

                case wxSYS_COLOUR_BTNTEXT:
                case wxSYS_COLOUR_CAPTIONTEXT:
                case wxSYS_COLOUR_HIGHLIGHTTEXT:
                case wxSYS_COLOUR_INFOTEXT:
                case wxSYS_COLOUR_LISTBOXHIGHLIGHTTEXT:
                case wxSYS_COLOUR_LISTBOXTEXT:
                case wxSYS_COLOUR_MENUTEXT:
                case wxSYS_COLOUR_WINDOWTEXT:
                    return wxColour(0xf2, 0xf2, 0xf2);

                case wxSYS_COLOUR_HOTLIGHT:
                    return wxColour(0x60, 0x60, 0x60);

                case wxSYS_COLOUR_SCROLLBAR:
                    return wxColour(0x5a, 0x5a, 0x5a);

                case wxSYS_COLOUR_INACTIVECAPTION:
                case wxSYS_COLOUR_MENU:
                    return wxColour(0x55, 0x55, 0x55);

                case wxSYS_COLOUR_MENUBAR:
                    return wxColour(0x6a, 0x6a, 0x6a);

                case wxSYS_COLOUR_MENUHILIGHT:
                    return wxColour(0x62, 0x62, 0x62);

                case wxSYS_COLOUR_BTNHIGHLIGHT:
                case wxSYS_COLOUR_HIGHLIGHT:
                    return wxColour(0x80, 0x80, 0x80);

                case wxSYS_COLOUR_INACTIVECAPTIONTEXT:
                case wxSYS_COLOUR_GRAYTEXT:
                    return wxColour(0xb4, 0xb4, 0xb4);

                default:
                    return BorderColour();
                }
            }

            switch (index)
            {
            // The stock dark palette leaves these undefined, which makes
            // wxWidgets fall back to the (white-ish) light system colours.
            // That is where the white borders and sash lines come from.
            case wxSYS_COLOUR_3DDKSHADOW:
            case wxSYS_COLOUR_3DLIGHT:
            case wxSYS_COLOUR_ACTIVEBORDER:
            case wxSYS_COLOUR_INACTIVEBORDER:
            case wxSYS_COLOUR_WINDOWFRAME:
            case wxSYS_COLOUR_DESKTOP:
            case wxSYS_COLOUR_GRADIENTACTIVECAPTION:
            case wxSYS_COLOUR_GRADIENTINACTIVECAPTION:
                return BorderColour();

            case wxSYS_COLOUR_GRAYTEXT:
                return wxColour(0x8a, 0x8a, 0x8a);

            default:
                return wxDarkModeSettings::GetColour(index);
            }
        }

        wxColour GetMenuColour(wxMenuColour which) override
        {
            if (!m_gray)
            {
                return wxDarkModeSettings::GetMenuColour(which);
            }

            switch (which)
            {
            case wxMenuColour::StandardFg: return wxColour(0xff, 0xff, 0xff);
            case wxMenuColour::StandardBg: return wxColour(0x7a, 0x7a, 0x7a);
            case wxMenuColour::DisabledFg: return wxColour(0x9a, 0x9a, 0x9a);
            case wxMenuColour::HotBg:      return wxColour(0x55, 0x55, 0x55);
            }

            return wxColour();
        }

        wxPen GetBorderPen() override
        {
            return wxPen(BorderColour());
        }

    private:
        wxColour BorderColour() const
        {
            return m_gray ? wxColour(0x5f, 0x5f, 0x5f) : wxColour(0x3a, 0x3a, 0x3a);
        }

        bool m_gray;
    };

    // True when the current UI uses a dark (or gray) background.
    inline bool IsDarkTheme()
    {
        return wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW).GetLuminance() < 0.5;
    }

    // Colour of the progress bars (torrent list, file list, piece bar).
    class ProgressColors
    {
    public:
        // id, translation key
        static std::vector<std::pair<std::string, std::string>> const& Options()
        {
            static std::vector<std::pair<std::string, std::string>> const options =
            {
                { "green",  "progress_color_green" },
                { "blue",   "progress_color_blue" },
                { "red",    "progress_color_red" },
                { "orange", "progress_color_orange" },
                { "yellow", "progress_color_yellow" },
                { "purple", "progress_color_purple" },
                { "pink",   "progress_color_pink" },
            };

            return options;
        }

        static std::string& CurrentId()
        {
            static std::string id = "green";
            return id;
        }

        static void Set(std::string const& id)
        {
            for (auto const& [optId, _] : Options())
            {
                if (optId == id) { CurrentId() = id; return; }
            }

            CurrentId() = "green";
        }

        static wxColour Get()
        {
            auto const& id = CurrentId();

            if (id == "blue")   { return wxColour(0x00, 0x78, 0xd4); }
            if (id == "red")    { return wxColour(0xe8, 0x11, 0x23); }
            if (id == "orange") { return wxColour(0xf7, 0x63, 0x0c); }
            if (id == "yellow") { return wxColour(0xff, 0xb9, 0x00); }
            if (id == "purple") { return wxColour(0x88, 0x64, 0xd8); }
            if (id == "pink")   { return wxColour(0xe3, 0x00, 0x8c); }

            // Windows progress bar green
            return wxColour(0x06, 0xb0, 0x25);
        }
    };
}
