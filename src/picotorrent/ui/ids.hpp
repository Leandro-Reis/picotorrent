#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

namespace pt
{
namespace UI
{
    enum
    {
        ptID_BEGIN = wxID_HIGHEST,
        ptID_MAIN_SPLITTER,
        ptID_MAIN_TORRENT_DETAILS,
        ptID_MAIN_TORRENT_LIST,

        ptID_EVT_VIEW_HELP,
        ptID_EVT_ABOUT,
        ptID_EVT_ADD_TORRENT,
        ptID_EVT_ADD_MAGNET_LINK,
        ptID_EVT_CHECK_FOR_UPDATE,
        ptID_EVT_CREATE_TORRENT,
        ptID_EVT_EXIT,
        ptID_EVT_SHOW_CONSOLE,
        ptID_EVT_SHOW_DETAILS,
        ptID_EVT_SHOW_STATUS_BAR,
        ptID_EVT_VIEW_PREFERENCES,

        // Must stay contiguous (bound as a range)
        ptID_EVT_THEME_LIGHT,
        ptID_EVT_THEME_GRAY,
        ptID_EVT_THEME_DARK,
        ptID_EVT_THEME_SYSTEM,

        // Must stay contiguous and match ProgressColors::Options() order
        ptID_EVT_PROGRESS_COLOR_FIRST,
        ptID_EVT_PROGRESS_COLOR_LAST = ptID_EVT_PROGRESS_COLOR_FIRST + 31,

        ptID_KEY_ADD_TORRENT,
        ptID_KEY_ADD_MAGNET_LINK,
        ptID_KEY_VIEW_HELP,

        ptID_EVT_FILTERS_NONE,
        ptID_EVT_FILTERS_USER,
    };

    enum
    {
        ptID_EVT_LABELS_EDIT = ptID_EVT_FILTERS_USER + 1000,
        ptID_EVT_LABELS_NONE,
        ptID_EVT_LABELS_USER
    };
}
}
