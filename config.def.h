/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "Ubuntu:size=9", "monospace:size=9" };
static const char dmenufont[]       = "Ubuntu:size=11";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class                instance     title       tags mask     isfloating   monitor */
    { "Gimp",               NULL,        NULL,       1 << 7,       0,           -1 },
    { "Inkscape",           NULL,        NULL,       1 << 7,       0,           -1 },
    { "VirtualBox Manager", NULL,        NULL,       1 << 7,       0,           -1 },
    { "Keepassx2",          NULL,        NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.6;  /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "><>",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
    { "|M|",      centeredmaster },
    { ">M>",      centeredfloatingmaster },
    { "TTT",      bstack },
    { "===",      bstackhoriz },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", selbordercolor, "-nf", normbgcolor, "-sb", normbgcolor, "-sf", selbordercolor, "-p", "Run this", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *managesessioncmd[] = { "manage_session_dwm", "-nb", normbgcolor, "-nf", selbordercolor, "-sb", selbordercolor, "-sf", normbgcolor, "-fn", dmenufont, NULL };
static const char *editconfs[] = { "edit_configs", "-nb", normbgcolor, "-nf", selbordercolor, "-sb", selbordercolor, "-sf", normbgcolor, "-fn", dmenufont, NULL };
static const char *nmdmenu[] = {"networkmanager_dmenu","-fn", dmenufont, "-nf", selbordercolor, "-nb", normbgcolor, "-sf", normbgcolor, "-sb", selbordercolor, NULL};

/**
 * The keycodes and names can be found using the `xev` command and the
 * `keysymdef.h` header file (here, located at /usr/include/X11/keysymdef.h).
 */
static Key keys[] = {
    /* modifier                     key                         function        argument */
    { MODKEY,                       XK_Menu,                    spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_Return,                  spawn,          {.v = termcmd } },
    { MODKEY,                       XK_b,                       togglebar,      {0} },
    { MODKEY,                       XK_j,                       focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,                       focusstack,     {.i = -1 } },
    { False,                        XF86XK_AudioLowerVolume,    spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -5%; pkill -RTMIN+10 dwmblocks") },
    { False,                        XF86XK_AudioRaiseVolume,    spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +5%; pkill -RTMIN+10 dwmblocks") },
    { False,                        XF86XK_AudioMute,           spawn,          SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle; pkill -RTMIN+10 dwmblocks") },
    { False,                        XF86XK_MonBrightnessDown,   spawn,          SHCMD("xbacklight -dec 10; pkill -RTMIN+11 dwmblocks") },
    { False,                        XF86XK_MonBrightnessUp,     spawn,          SHCMD("xbacklight -inc 10; pkill -RTMIN+11 dwmblocks") },
    { False,                        XK_Print,                   spawn,          SHCMD("capture_screenshot") },
    { Mod1Mask,                     XK_Print,                   spawn,          SHCMD("capture_screenshot --selection") },
    { MODKEY,                       XK_e,                       spawn,          {.v = editconfs} },
    { MODKEY,                       XK_n,                       spawn,          {.v = nmdmenu} },
    { MODKEY,                       XK_semicolon,               spawn,          SHCMD("pidof keynav 1> /dev/null || keynav ") },
    { MODKEY|ShiftMask,             XK_semicolon,               spawn,          SHCMD("pkill keynav") },
    { MODKEY|ShiftMask,             XK_j,                       pushdown,       {0} },
    { MODKEY|ShiftMask,             XK_k,                       pushup,         {0} },
    { MODKEY,                       XK_h,                       setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,                       setmfact,       {.f = +0.05} },
    { MODKEY,                       XK_z,                       zoom,           {0} },
    { MODKEY,                       XK_Tab,                     view,           {0} },
    { MODKEY|ShiftMask,             XK_q,                       killclient,     {0} },
    { MODKEY,                       XK_t,                       setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_space,                   setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_m,                       setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_c,                       setlayout,      {.v = &layouts[3]} },
    { MODKEY|ShiftMask,             XK_c,                       setlayout,      {.v = &layouts[4]} },
    { MODKEY,                       XK_u,                       setlayout,      {.v = &layouts[5]} },
    { MODKEY|ShiftMask,             XK_u,                       setlayout,      {.v = &layouts[6]} },
    { MODKEY|ShiftMask,             XK_space,                   togglefloating, {0} },
    { MODKEY,                       XK_f,                       togglefullscr,  {0} },
    { MODKEY,                       XK_0,                       view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,                       tag,            {.ui = ~0 } },
    { MODKEY,                       XK_KP_Insert,               view,           {.ui = ~0 } },  // Keypad
    { MODKEY|ShiftMask,             XK_KP_Insert,               tag,            {.ui = ~0 } },  // Keypad
    { MODKEY,                       XK_comma,                   focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period,                  focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,                   tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period,                  tagmon,         {.i = +1 } },
    { MODKEY,                       XK_F5,                      xrdb,           {.v = NULL } },
    TAGKEYS(                        XK_1,                       0)
    TAGKEYS(                        XK_2,                       1)
    TAGKEYS(                        XK_3,                       2)
    TAGKEYS(                        XK_4,                       3)
    TAGKEYS(                        XK_5,                       4)
    TAGKEYS(                        XK_6,                       5)
    TAGKEYS(                        XK_7,                       6)
    TAGKEYS(                        XK_8,                       7)
    TAGKEYS(                        XK_9,                       8)
    TAGKEYS(                        XK_KP_End,                  0)  // Keypad
    TAGKEYS(                        XK_KP_Down,                 1)  // Keypad
    TAGKEYS(                        XK_KP_Next,                 2)  // Keypad
    TAGKEYS(                        XK_KP_Left,                 3)  // Keypad
    TAGKEYS(                        XK_KP_Begin,                4)  // Keypad
    TAGKEYS(                        XK_KP_Right,                5)  // Keypad
    TAGKEYS(                        XK_KP_Home,                 6)  // Keypad
    TAGKEYS(                        XK_KP_Up,                   7)  // Keypad
    TAGKEYS(                        XK_KP_Prior,                8)  // Keypad
    { Mod1Mask|ControlMask,         XK_Delete,                  spawn,          {.v = managesessioncmd} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

