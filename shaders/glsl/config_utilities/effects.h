// Newb Shader

// Extra effects. Everything here runs inside the existing passes: no extra
// draw calls, no render targets, no extra varyings. The terrain fragment
// already uses almost all of the eight varying slots GLES2 guarantees, so
// anything that would need a new varying is deliberately not in this file.

#ifndef NEWB_EFFECTS
#define NEWB_EFFECTS

/*""*/
/* WIND */

// Toggle - Travelling gust front, so plants do not sway in lockstep
#define GUST_WIND

/*""*/
/* WATER */

// Value - Second high frequency ripple on water vertices (0-1)
#define WATER_DETAIL 0.35

// Toggle - Rain impact dents on the water surface
#define RAIN_RIPPLE

/*""*/
/* LIGHTING */

// Value - Fake one bounce light, overworld (0-1)
#define BOUNCE_LIGHT 0.25

/*""*/
/* SKY */

// Value - Horizon anchored light shafts (0-1)
#define SUN_SHAFTS 0.55

// Value - Milky way band brightness (0-1)
#define MILKY_WAY 0.30

// Value - Star twinkle in the end sky (0-1)
#define STAR_TWINKLE 0.45

/*""*/
/* ENTITIES */

// Value - Rim light strength on entities (0-1)
#define RIM_LIGHT 0.6

/*""*/
/* CLOUDS */

// Toggle - Second cloud layer, gives the flat noise some thickness
#define CLOUD_LAYER

/*""*/

#endif // NEWB_EFFECTS
