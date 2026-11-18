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

// Value - Sun band on rain wet ground, so it agrees with the water surface (0-1)
#define WET_SUN 0.55

// Value - Vertical light shafts underwater (0-1)
#define UNDERWATER_SHAFTS 0.45

/*""*/
/* LIGHTING */

// Value - Fake one bounce light, overworld (0-1)
#define BOUNCE_LIGHT 0.25

// Value - Moving cloud shadows on the ground (0-1)
#define CLOUD_SHADOW 0.75

// Value - Distance in blocks where cloud shadows stop being sampled
#define CLOUD_SHADOW_DIST 48.0

// Value - Light passing through tree leaves (0-1)
#define LEAF_TRANSMIT 0.35

// Toggle - Smooth, stretched ambient occlusion instead of a two step multiply
#define AO_SHARPEN

/*""*/
/* SKY */

// Value - Horizon anchored light shafts (0-1)
#define SUN_SHAFTS 0.55

// Value - Milky way band brightness (0-1)
#define MILKY_WAY 0.30

// Value - Star twinkle in the end sky (0-1)
#define STAR_TWINKLE 0.45

// Value - Shooting stars (0-1)
#define SHOOTING_STARS 0.85

/*""*/
/* ENTITIES */

// Value - Rim light strength on entities (0-1)
#define RIM_LIGHT 0.6

/*""*/
/* CLOUDS */

// Toggle - Second cloud layer, gives the flat noise some thickness
#define CLOUD_LAYER

// Value - Sunrise and sunset tint on the clouds (0-1)
#define CLOUD_SUN 0.30

// Toggle - Fade the cloud layer into the night colour. Vanilla keeps clouds pale
// grey after dark, which is what makes them read as a grid of pale pads
#define CLOUD_NIGHT_FADE

/*""*/

#endif // NEWB_EFFECTS
