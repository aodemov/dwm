// Constants
#define TERMINAL "st"
#define TERMCLASS "St"


static unsigned int borderpx  = 3;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */

static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */

// Systray
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */

// Gaps
static unsigned int gappih    = 16;       /* horiz inner gap between windows */
static unsigned int gappiv    = 16;       /* vert inner gap between windows */
static unsigned int gappoh    = 16;       /* horiz outer gap between windows and screen edge */
static unsigned int gappov    = 16;       /* vert outer gap between windows and screen edge */
static int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */

static int swallowfloating    = 0;        /* 1 means swallow floating windows by default */

// Fonts
static char *fonts[] = {
	"monospace:size=10.5",
	"FontAwesome 5 Free Solid:pixelsize=15:antialias=true:autohint=true",
};

// Colors
static char normbgcolor[]    	= "#222222";
static char normbordercolor[]	= "#555277";
static char normfgcolor[]    	= "#bbbbbb";
static char selfgcolor[]     	= "#eeeeee";
static char selbordercolor[] 	= "#6689F2"; //#FE9697
// static char selbgcolor[]     	= "#31316C";
static char selbgcolor[]     	= "#d179a1";

static const unsigned int baralpha = 0xdf;

static char *colors[][3] = {
       /*               		fg           	bg           	border   */
       	[SchemeNorm]  		= { normfgcolor, 	normbgcolor, 	normbordercolor },
       	[SchemeSel]   		= { selfgcolor,  	selbgcolor,  	selbordercolor  },

	   	[SchemeStatus] 		= { normfgcolor, 	normbgcolor,  	"#000000"  }, // Statusbar right

   		[SchemeTagsNorm]	= { normfgcolor, 	normbgcolor,  	"#000000"  }, // Tagbar left
		[SchemeTagsSel]  	= { selfgcolor, 	selbgcolor,  	"#000000"  }, // Tagbar left selected
	    [SchemeInfoNorm]  	= { normfgcolor, 	normbgcolor,  	"#000000"  }, // Titlebar
    	[SchemeInfoSel]  	= { selfgcolor,		normbgcolor,  	"#000000"  }, // Titlebar selected
};

static const unsigned int alphas[][3] = {
	/*               		fg      bg        border     */
	[SchemeNorm]  		= { OPAQUE, baralpha, OPAQUE },
	[SchemeSel]   		= { OPAQUE, baralpha, OPAQUE },

	[SchemeStatus] 		= { OPAQUE, baralpha, OPAQUE  }, // Statusbar right

	[SchemeTagsNorm] 	= { OPAQUE, baralpha, OPAQUE  }, // Tagbar left
	[SchemeTagsSel] 	= { OPAQUE, baralpha, OPAQUE  }, // Tagbar left selected
	[SchemeInfoNorm]  	= { OPAQUE, baralpha, OPAQUE  }, // Titlebar
	[SchemeInfoSel]  	= { OPAQUE,	baralpha, OPAQUE  }, // Titlebar selected

};

// Scratchpads
typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {TERMINAL, "-n", "spcalc", "-f", "monospace:size=16", "-g", "50x20", "-e", "bc", "-lq", NULL };
static Sp scratchpads[] = {
	{"spterm",      spcmd1},
	{"spcalc",      spcmd2},
};

// Tagging
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

// Rules

/* xprop(1):
 *	WM_CLASS(STRING) = instance, class
 *	WM_NAME(STRING) = title
*/

static const Rule rules[] = {
	/* class        		instance    	title       	 	tags mask       iscentered	isfloating  isterminal  noswallow 	monitor */
	{ TERMCLASS,  			NULL,       	NULL,       	    0,            	0,			0,          1,          0,        	-1 },
	{ NULL,       			"spterm",   	NULL,       	    SPTAG(0),     	0,			1,          1,          0,        	-1 },
	{ NULL,       			"spcalc",   	NULL,       	    SPTAG(1),     	0,			1,          1,          0,        	-1 },
	{ "Spotify",			"spotify",		NULL,				1 << 8,			0,			0,			0,			0,			-1 },
	{ "VK", 				"vk",			NULL,				1 << 7,			0,			0,			0,			0,			-1 },
	{ "TelegramDesktop", 	NULL, 			NULL,				1 << 7, 		0,			0, 			0,			0,			-1 },
	{ "discord",	 		"discord",		NULL,				1 << 8,			0,			0,			0,			0,			-1 },
	{ TERMCLASS,			TERMINAL,		"pulsemixer", 		0,				1,			1,			1,			0,			-1 },
	{ TERMCLASS,			TERMINAL,		"htop", 			0,				1,			1,			1,			0,			-1 },
	{ TERMCLASS,			TERMINAL,		"nmtui", 			0,				1,			1,			1,			0,			-1 },
};


// Layouts
static float mfact     = 0.55; // factor of master area size [0.05..0.95]
static int nmaster     = 1;    // number of clients in master area
static int resizehints = 1;    // 1 means respect size hints in tiled resizals
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol   arrange function */
 	{ "[]=",	tile },			// Default: Master on left, slaves on right
	{ "TTT",	bstack },		// Master on top, slaves on bottom

	{ "[@]",	spiral },		// Fibonacci spiral
	{ "[\\]",	dwindle },		// Decreasing in size right and leftward

	{ "[D]",	deck },			// Master on left, slaves in monocle-like mode on right
 	{ "[M]",	monocle },		// All windows on top of eachother

	{ "|M|",	centeredmaster },		// Master in middle, slaves on sides
	{ ">M>",	centeredfloatingmaster },	// Same but master floats

	{ "><>",	NULL },			// Floating
	{ NULL,		NULL },
};


// XResources
ResourcePref resources[] = {
		{ "color0",				STRING,		&normbordercolor },
		{ "color8",				STRING,		&selbordercolor },
		{ "color0",				STRING,		&normbgcolor },
		{ "color4",				STRING,		&normfgcolor },
		{ "color0",				STRING,		&selfgcolor },
		{ "color4",				STRING,		&selbgcolor },
		{ "borderpx",			INTEGER, 	&borderpx },
		{ "snap",				INTEGER, 	&snap },
		{ "showbar",			INTEGER, 	&showbar },
		{ "topbar",				INTEGER, 	&topbar },
		{ "nmaster",			INTEGER, 	&nmaster },
		{ "resizehints",		INTEGER, 	&resizehints },
		{ "mfact",				FLOAT,		&mfact },
		{ "gappih",				INTEGER, 	&gappih },
		{ "gappiv",				INTEGER, 	&gappiv },
		{ "gappoh",				INTEGER, 	&gappoh },
		{ "gappov",				INTEGER, 	&gappov },
		{ "swallowfloating",	INTEGER, 	&swallowfloating },
		{ "smartgaps",			INTEGER, 	&smartgaps },
};

// Helper for pawning shell
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
static const char *termcmd[]  = { TERMINAL, NULL };

#include <X11/XF86keysym.h>
#include "shiftview.c"

// Keys
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_j,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \
	{ MOD,  XK_v,   ACTION##stack,  {.i = 0 } }, \
	// { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \
	// { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \
	// { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \
	// { MOD, XK_x,     ACTION##stack, {.i = -1 } },

static Key keys[] = {
	/* modifier			key        function        argument */

	/// Tagging
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)

	TAGKEYS(			XK_1,			0)
	TAGKEYS(			XK_2,			1)
	TAGKEYS(			XK_3,			2)
	TAGKEYS(			XK_4,			3)
	TAGKEYS(			XK_5,			4)
	TAGKEYS(			XK_6,			5)
	TAGKEYS(			XK_7,			6)
	TAGKEYS(			XK_8,			7)
	TAGKEYS(			XK_9,			8)

	{ MODKEY,			XK_b,			togglebar,	{0} },

	{ MODKEY,			XK_Tab,			view,		{0} },
	{ MODKEY,			XK_backslash,	view,		{0} },
	{ MODKEY,			XK_0,			view,		{.ui = ~0 } },

	{ MODKEY,			XK_t,			setlayout,	{.v = &layouts[0]} }, /* tile */
	{ MODKEY|ShiftMask,	XK_t,			setlayout,	{.v = &layouts[1]} }, /* bstack */
	{ MODKEY,			XK_y,			setlayout,	{.v = &layouts[2]} }, /* spiral */
	{ MODKEY|ShiftMask,	XK_y,			setlayout,	{.v = &layouts[3]} }, /* dwindle */
	{ MODKEY,			XK_u,			setlayout,	{.v = &layouts[4]} }, /* deck */
	{ MODKEY|ShiftMask,	XK_u,			setlayout,	{.v = &layouts[5]} }, /* monocle */
	{ MODKEY,			XK_i,			setlayout,	{.v = &layouts[6]} }, /* centeredmaster */
	{ MODKEY|ShiftMask,	XK_i,			setlayout,	{.v = &layouts[7]} }, /* centeredfloatingmaster */
	{ MODKEY|ShiftMask,	XK_f,			setlayout,	{.v = &layouts[8]} },

	{ MODKEY,			XK_g,			shiftview,	{ .i = -1 } },
	{ MODKEY|ShiftMask,	XK_g,			shifttag,	{ .i = -1 } },
	{ MODKEY,			XK_semicolon,	shiftview,	{ .i = 1 } },
	{ MODKEY|ShiftMask,	XK_semicolon,	shifttag,	{ .i = 1 } },

	// { MODKEY,			XK_space,		zoom,		{0} },
     { MODKEY,			XK_space,		spawn,		SHCMD("xkb-switch -n; kill -54 $(pidof dwmblocks)") },

	{ MODKEY,			XK_Left,		focusmon,	{.i = -1 } },
	{ MODKEY|ShiftMask,	XK_Left,		tagmon,		{.i = -1 } },
	{ MODKEY,			XK_Right,		focusmon,	{.i = +1 } },
	{ MODKEY|ShiftMask,	XK_Right,		tagmon,		{.i = +1 } },

	// { MODKEY,			XK_Page_Up,		shiftview,	{ .i = -1 } },
	// { MODKEY|ShiftMask,	XK_Page_Up,		shifttag,	{ .i = -1 } },
	// { MODKEY,			XK_Page_Down,	shiftview,	{ .i = +1 } },
	// { MODKEY|ShiftMask,	XK_Page_Down,	shifttag,	{ .i = +1 } },

	{ MODKEY,			XK_o,			incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,	XK_o,			incnmaster,     {.i = -1 } },
	{ MODKEY,			XK_h,			setmfact,	{.f = -0.05} },
	{ MODKEY,			XK_l,			setmfact,      	{.f = +0.05} },


	/// Windows
	{ MODKEY,			XK_q,			killclient,	{0} },

	{ MODKEY,			XK_s,			togglesticky,	{0} },
	{ MODKEY,			XK_f,			togglefullscr,	{0} },
	{ MODKEY|ShiftMask,	XK_space,		togglefloating,	{0} },


	/// Gaps
	{ MODKEY,			XK_c,			togglegaps,		{0} },
	{ MODKEY|ShiftMask,	XK_c,			defaultgaps,	{0} },

	{ MODKEY,			XK_z,			incrgaps,	{.i = +2 } },
	{ MODKEY,			XK_x,			incrgaps,	{.i = -2 } },


	/// Applications
	{ MODKEY,			XK_d,			spawn,	SHCMD("rofi -show drun") },
	{ MODKEY|ShiftMask,	XK_d,			spawn,	SHCMD("rofi -show run") },
	{ MODKEY,			XK_Return,		spawn,	{.v = termcmd } },

	{ MODKEY,			XK_BackSpace,	spawn,	SHCMD("sysact") },

	{ MODKEY,			XK_w,			spawn,	SHCMD("$BROWSER") },
	{ MODKEY,			XK_e,			spawn,	SHCMD(TERMINAL " -e lf") },
	{ MODKEY|ShiftMask,	XK_e,			spawn,	SHCMD(TERMINAL " -g 80x30 -e pulsemixer; kill -44 $(pidof dwmblocks)") },
	{ MODKEY,			XK_r,			spawn,	SHCMD(TERMINAL " -g 80x30 -e htop") },
	{ MODKEY|ShiftMask,	XK_r,			spawn,	SHCMD(TERMINAL " -g 80x30 -e nmtui") },


	// Volume
	{ MODKEY,			XK_minus,		spawn,	SHCMD("pamixer --allow-boost -d 5; kill -44 $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask,	XK_minus,		spawn,	SHCMD("pamixer --allow-boost -d 15; kill -44 $(pidof dwmblocks)") },
	{ MODKEY,			XK_equal,		spawn,	SHCMD("pamixer --allow-boost -i 5; kill -44 $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask,	XK_equal,		spawn,	SHCMD("pamixer --allow-boost -i 15; kill -44 $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask,	XK_m,			spawn,	SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
    { MODKEY,           XK_m,           spawn,  SHCMD("switchport; kill -44 $(pidof dwmblocks)") },

	// Peripherals
	{ MODKEY,			XK_F9,			spawn,	SHCMD("dmenumount") },
	{ MODKEY,			XK_F10,			spawn,	SHCMD("dmenuumount") },
	{ MODKEY,			XK_F12,			spawn,	SHCMD("remaps & notify-send \\\"⌨️ Keyboard remapping...\\\" \\\"Re-running keyboard defaults for any newly plugged-in keyboards.\\\"") },
	{ MODKEY,			XK_F3,			spawn,	SHCMD("displayselect") },

	// Screen recording
	{ 0,				XK_Print,		spawn,	SHCMD("flameshot full -c") },
	{ ShiftMask,		XK_Print,		spawn,	SHCMD("flameshot gui") },
	{ MODKEY,			XK_slash,			spawn,	SHCMD("flameshot gui") },

    /// Networking
    { MODKEY,           XK_comma,       spawn, SHCMD("togglewg wg0") },
    { MODKEY|ShiftMask, XK_comma,       spawn, SHCMD("togglewg a2seven") },


	// { MODKEY,			XK_Print,		spawn,	SHCMD("dmenurecord") },
	// { MODKEY|ShiftMask,	XK_Print,		spawn,	SHCMD("dmenurecord kill") },
	// { MODKEY,			XK_Delete,		spawn,	SHCMD("dmenurecord kill") },
	// { MODKEY,			XK_Scroll_Lock,	spawn,	SHCMD("killall screenkey || screenkey &") },
	// { MODKEY,			XK_F11,			spawn,	SHCMD("mpv --no-cache --no-osc --no-input-default-bindings --profile=low-latency --input-conf=/dev/null --title=webcam $(ls /dev/video[0,2,4,6,8] | tail -n 1)") },

	// Torrenting
	{ MODKEY,			XK_F6,			spawn,	SHCMD("torwrap") },
	{ MODKEY,			XK_F7,			spawn,	SHCMD("td-toggle") },

	// Scratchpads
	{ MODKEY|ShiftMask,	XK_Return,		togglescratch,	{.ui = 0} },
	{ MODKEY,			XK_apostrophe,	togglescratch,	{.ui = 1} },

	// MPC
	//{ MODKEY,			XK_comma,		spawn,	SHCMD("mpc prev") },
	//{ MODKEY|ShiftMask,	XK_comma,		spawn,	SHCMD("mpc seek 0%") },
	//{ MODKEY,			XK_period,		spawn,	SHCMD("mpc next") },
	//{ MODKEY|ShiftMask,	XK_period,		spawn,	SHCMD("mpc repeat") },
	//{ MODKEY,			XK_p,			spawn,	SHCMD("mpc toggle") },
	//{ MODKEY|ShiftMask,	XK_p,			spawn,	SHCMD("mpc pause ; pauseallmpv") },
	//{ MODKEY,			XK_bracketleft,	spawn,	SHCMD("mpc seek -10") },
	//{ MODKEY|ShiftMask,	XK_bracketleft,	spawn,	SHCMD("mpc seek -60") },
	//{ MODKEY,			XK_bracketright,spawn,	SHCMD("mpc seek +10") },
	//{ MODKEY|ShiftMask,	XK_bracketright,spawn,	SHCMD("mpc seek +60") },

	/// XF86 Keys
	{ 0, XF86XK_AudioMute,			spawn,		SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD("pamixer --allow-boost -i 3; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD("pamixer --allow-boost -d 3; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioPrev,			spawn,		SHCMD("mpc prev") },
	{ 0, XF86XK_AudioNext,			spawn,		SHCMD("mpc next") },
	{ 0, XF86XK_AudioPause,			spawn,		SHCMD("mpc pause") },
	{ 0, XF86XK_AudioPlay,			spawn,		SHCMD("mpc play") },
	{ 0, XF86XK_AudioStop,			spawn,		SHCMD("mpc stop") },
	{ 0, XF86XK_AudioRewind,		spawn,		SHCMD("mpc seek -10") },
	{ 0, XF86XK_AudioForward,		spawn,		SHCMD("mpc seek +10") },
	{ 0, XF86XK_AudioMedia,			spawn,		SHCMD(TERMINAL " -e ncmpcpp") },
	{ 0, XF86XK_AudioMicMute,		spawn,		SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
	{ 0, XF86XK_PowerOff,			spawn,		SHCMD("sysact") },
	{ 0, XF86XK_Calculator,			spawn,		SHCMD(TERMINAL " -e bc -l") },
	{ 0, XF86XK_Sleep,				spawn,		SHCMD("sudo -A zzz") },
	{ 0, XF86XK_WWW,				spawn,		SHCMD("$BROWSER") },
	{ 0, XF86XK_DOS,				spawn,		SHCMD(TERMINAL) },
	{ 0, XF86XK_ScreenSaver,		spawn,		SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
	{ 0, XF86XK_TaskPane,			spawn,		SHCMD(TERMINAL " -e htop") },
	{ 0, XF86XK_Mail,				spawn,		SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks") },
	{ 0, XF86XK_MyComputer,			spawn,		SHCMD(TERMINAL " -e lf /") },
	// { 0, XF86XK_Battery,			spawn,		SHCMD("") },
	{ 0, XF86XK_Launch1,			spawn,		SHCMD("xset dpms force off") },
	{ 0, XF86XK_TouchpadToggle,		spawn,		SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOff,		spawn,		SHCMD("synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOn,			spawn,		SHCMD("synclient TouchpadOff=0") },
	{ 0, XF86XK_MonBrightnessUp,	spawn,		SHCMD("xbacklight -inc 1") },
	{ 0, XF86XK_MonBrightnessDown,	spawn,		SHCMD("xbacklight -dec 1") },


	/// Etc.
	{ MODKEY,			XK_grave,		spawn,	SHCMD("dmenuunicode") },
	// { MODKEY,			XK_Insert,		spawn,	SHCMD("xdotool type $(cat ~/.local/share/larbs/snippets | dmenu -i -l 50 | cut -d' ' -f1)") },
};

// Mouse buttons
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* target               event mask      button          function        argument */
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
	{ ClkStatusText,        ShiftMask,      Button3,        spawn,          SHCMD(TERMINAL " -e nvim ~/.local/src/dwmblocks/config.h") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        defaultgaps,	{0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,			MODKEY,			Button4,		incrgaps,	{.i = +1} },
	{ ClkClientWin,			MODKEY,			Button5,		incrgaps,	{.i = -1} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTagBar,			0,				Button4,		shiftview,	{.i = -1} },
	{ ClkTagBar,			0,				Button5,		shiftview,	{.i = 1} },
	{ ClkRootWin,			0,				Button2,		togglebar,	{0} },
};

