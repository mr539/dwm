/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {
	"mono:style=regular:size=10", 
	"NotoColorEmoji:size=10:pixelsize=10:antialias=true:autohint=true", 
	"Nerd Fonts:size=10:antialias=true:autohint=true"
};
static const char dmenufont[]       = "mono:size=10:style=regular";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1): 
	 WM_CLASS(STRING) = instance, class
	 WM_NAME(STRING) = xsetroot -name "some text"
	*/
/*	class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ NULL,       NULL,      "termfloat", 0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *volume_mute[] = { "pactl", "set-sink-mute",   "0",  "toggle", NULL };
static const char *volume_up[]   = { "pactl", "set-sink-volume", "0",  "+5%",    NULL };
static const char *volume_down[] = { "pactl", "set-sink-volume", "0",  "-5%",    NULL };
static const char *mic_mute[]    = { "pactl", "set-source-mute", "52", "toggle", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,                      spawn,          {.v = dmenucmd } },
	{ 0,                            XK_Menu,                   spawn,          SHCMD("flameshot gui") },
	{ 0,                            XK_Print,                  spawn,          SHCMD("flameshot gui") },
	{ MODKEY,                       XK_BackSpace,              spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_BackSpace,              spawn,          SHCMD("st -T 'termfloat'") },
	{ MODKEY,                       XK_Return,                 spawn,          SHCMD("tmaster") },
	{ MODKEY|ShiftMask,             XK_Return,                 spawn,          SHCMD("st -T 'termfloat' tmux a -t master") },
	{ MODKEY,                       XK_x,                      spawn,          SHCMD("keepassxc") },
	{ MODKEY|ShiftMask,             XK_a,                      spawn,          SHCMD("slock") },
	{ MODKEY,                       XK_t,                      spawn,          SHCMD("thunderbird") },
	{ MODKEY,                       XK_w,                      spawn,          SHCMD("firefox") },
	{ MODKEY|ShiftMask,             XK_w,                      spawn,          SHCMD("firefox --private-window") },
	{ MODKEY,                       XK_b,                      spawn,          SHCMD("brave") },
	{ MODKEY|ShiftMask,             XK_b,                      spawn,          SHCMD("brave --incognito") },
	{ MODKEY,                       XK_a,                      spawn,          SHCMD("anki -b ~/.config/Anki2") },
	{ MODKEY,                       XK_g,                      spawn,          SHCMD("geogebra") },
	{ MODKEY,                       XF86XK_AudioMute,          spawn,          {.v = volume_mute } },
	{ MODKEY,                       XF86XK_AudioRaiseVolume,   spawn,          {.v = volume_up   } },
	{ MODKEY,                       XF86XK_AudioLowerVolume,   spawn,          {.v = volume_down } },
	{ MODKEY,                       XF86XK_AudioMicMute,       spawn,          {.v = mic_mute    } },
	{ MODKEY,                       XK_l,                      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_h,                      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,                      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,                      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_j,                      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_k,                      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_f,                      togglefullscr,  {0} },
	{ MODKEY,                       XK_z,                      zoom,           {0} },
	{ MODKEY,                       XK_Tab,                    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,                      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_t,                      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,                      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,                      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,                  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,                  togglefloating, {0} },
	{ MODKEY,                       XK_0,                      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,                 focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                 tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_parenleft,                              0)
	TAGKEYS(                        XK_parenright,                             1)
	TAGKEYS(                        XK_braceright,                             2)
	TAGKEYS(                        XK_plus,                                   3)
	TAGKEYS(                        XK_braceleft,                              4)
	TAGKEYS(                        XK_bracketright,                           5)
	TAGKEYS(                        XK_bracketleft,                            6)
	TAGKEYS(                        XK_exclam,                                 7)
	TAGKEYS(                        XK_equal,                                  8)

	{ MODKEY|ShiftMask,             XK_Delete,                  quit,          {0} },
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

