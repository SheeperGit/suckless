/* See LICENSE file for copyright and license details. */

#define STATUSBAR "dwmblocks"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 15;       /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "DejaVu Mono:size=18:antialias=true:autohint=true", "NotoColorEmoji:size=18:antialias=true:autohint=true" };
static const char dmenufont[]       = "monospace:size=18";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#003a4e";  
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

static const char *const autostart[] = {
	"dwmblocks", NULL,
	"picom", NULL,
	"dunst", NULL,
	"sh", "-c", "discord &", NULL,
	"sh", "-c", "sleep 28 ; firefox &", NULL,  
	"sh", "-c", "sleep 15 ; kill -44 $(pidof dwmblocks)", NULL,	/* Refresh volume block at startup. Ensures correct startup volume display */
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" };
static const int taglayouts[] = { 2, 2, 0, 0, 0 };	/* 0 = tile, 1 = float, 2 = monocle */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,           },
{ "st",      NULL,     NULL,           0,         0,          1,           0,        -1 },
{ "Gimp",    NULL,     NULL,           0,         0,          0,           1,        -1 },
{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
{ "st",      NULL,     "easylora",     0,         0,          0,           1,        -1 }, /* easylora */
{ "mpv",     NULL,     "webcam",       ~0,        1,          0,           0,        -1 }, /* mpv webcam */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int attachbelow = 1;    /* 1 means attach after the currently active window */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define METAKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define KEYPADTAGKEYS(KEY,TAG) \
	{ 0,                     KEY,      view,           {.ui = 1 << TAG} }, \
	{ ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

/* custom commands */
static const char *voldocmd[]  = { "sh", "-c", "wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; kill -44 $(pidof dwmblocks)" };
static const char *volupcmd[]  = { "sh", "-c", "wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+; kill -44 $(pidof dwmblocks)" };
static const char *poofcmd[]   = { "prompt", "Are you sure you want to shutdown?", "shutdown now", NULL };
static const char *rebocmd[]   = { "prompt", "Are you sure you want to reboot?", "reboot", NULL };
static const char *suspcmd[]   = { "prompt", "Are you sure you want to sleep?", "systemctl suspend", NULL };
static const char *htopcmd[]   = { "st", "-e", "htop", NULL };
static const char *nvimcmd[]   = { "st", "-e", "nvim", NULL };
static const char *lfcmd[]     = { "st", "-e", "lf", NULL };
static const char *ptogcmd[]   = { "pia-toggle", NULL };
static const char *emucmd[]    = { "emu", NULL };
static const char *progcmd[]   = { "prog", NULL };
static const char *gamecmd[]   = { "game", NULL };
static const char *bgcmd[]     = { "bg-set", NULL };
static const char *battcmd[]   = { "batt", NULL };
static const char *btcmd[]     = { "bt", NULL };
static const char *scrcmd[]    = { "scrshot", NULL };
static const char *scrselcmd[] = { "scrshot", "-s", NULL };
static const char *camtogcmd[] = { "camtog", NULL };
static const char *clipcmd[]   = { "lora-clip", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
//{ MODKEY,                       XK_space,  setlayout,      {0} }, /* Causes crashes (reason unknown) */
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
  KEYPADTAGKEYS(                  XK_KP_End,                 0) /********************************************/
	KEYPADTAGKEYS(                  XK_KP_Down,                1) /********************************************/
	KEYPADTAGKEYS(                  XK_KP_Next,                2) /********************************************/
	KEYPADTAGKEYS(                  XK_KP_Left,                3) /********************************************/
	KEYPADTAGKEYS(                  XK_KP_Begin,               4) /* Alt (keypad) keybinds for switching tags */
	KEYPADTAGKEYS(                  XK_KP_Right,               5) /********************************************/
	KEYPADTAGKEYS(                  XK_KP_Home,                6) /********************************************/
	KEYPADTAGKEYS(                  XK_KP_Up,                  7) /********************************************/
	KEYPADTAGKEYS(                  XK_KP_Prior,               8) /********************************************/
	{ MODKEY|ShiftMask,             XK_q,      quit,                        {0} },
	{ 0,                       	 XK_KP_Enter,  view,                        {0} },  /* Alt keybind for navigating to prev tag. */
	{ 0,                     	    XK_KP_Add,   focusstack, 	         {.i = +1 } },	/* Alt keybind for shifting focus to next window. */
	{ 0,                       XK_KP_Subtract, focusstack,           {.i = -1 } },	/* Alt keybind for shifting focus to prev window. */
	{ METAKEY,			            XK_Page_Down,  spawn,	         {.v = voldocmd } },  /* Volume -5% */
	{ METAKEY,			              XK_Page_Up,	 spawn,	         {.v = volupcmd } },  /* Volume +5% */
	{ MODKEY|ShiftMask,		          XK_F10,		 spawn,	          {.v = poofcmd } }, 	/* Prompt shutdown. */
	{ MODKEY|ShiftMask,		          XK_r,		   spawn,	          {.v = rebocmd } }, 	/* Prompt reboot. */
	{ MODKEY|ShiftMask,		          XK_s,		   spawn,	          {.v = suspcmd } }, 	/* Prompt sleep. */
  { MODKEY|ShiftMask,		          XK_n,		   spawn,	          {.v = nvimcmd } }, 	/* Launch nvim. */
	{ MODKEY|ShiftMask,		          XK_e,		   spawn,	           {.v = emucmd } }, 	/* Launch an emulator. */
	{ MODKEY|ShiftMask,		          XK_p,		   spawn,	          {.v = progcmd } }, 	/* Launch a program. */
	{ MODKEY|ShiftMask,		          XK_g,		   spawn,	          {.v = gamecmd } }, 	/* Launch a game. */
	{ MODKEY|ShiftMask,		          XK_b,		   spawn,	            {.v = btcmd } }, 	/* Connect/Disconnect bt device. */
	{ MODKEY|ShiftMask,	            XK_f,		   spawn,	            {.v = lfcmd } }, 	/* Launch lf file manager. */
	{ METAKEY,	                  XK_Print,	   spawn,            {.v = scrcmd } }, 	/* Take a full-window screenshot. */
	{ ControlMask,	              XK_Print,	   spawn,         {.v = scrselcmd } }, 	/* Take a select-region screenshot. */
	{ ControlMask|ShiftMask,	    XK_Escape,	 spawn,           {.v = htopcmd } }, 	/* Launch htop. */
	{ ControlMask|ShiftMask,	      XK_b,		   spawn,	          {.v = battcmd } },  /* Display device battery. */
	{ ControlMask|MODKEY,		        XK_p,		   spawn,	          {.v = ptogcmd } }, 	/* Toggle pia-vpn. */
	{ ControlMask|MODKEY,	          XK_c,	     spawn,	        {.v = camtogcmd } }, 	/* Toggle webcam view. */
	{ ControlMask|MODKEY,           XK_g,		   spawn,	            {.v = bgcmd } }, 	/* Change background. */
	{ ControlMask|MODKEY,           XK_l,		   spawn,	          {.v = clipcmd } }, 	/* Various useful LoRA clipboards. */
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

