// Newb shader

/*""""""""""""""""""""""""""""""""""""""*/
/* SKY */

// color - Night sky color
const vec3 nightSkyCol = vec3(0.01,0.06,0.1);

// color - Sky base color
const vec3 skyBaseCol = vec3(0.15,0.45,1.0);

// value - Day sky clarity (0-1)
const float daySkyClarity = 0.3;

// color - Sunrise base color
const vec3 horizonBaseCol = vec3(1.0,0.4,0.3);

// color - Sunrise edge color
const vec3 horizonEdgeCol = vec3(1.0,0.4,0.2);

// color - Underwater fog color
const vec3 underwaterBaseCol = vec3(0.0,0.6,1.0);


/*""""""""""""""""""""""""""""""""""""""*/


// Code starts here - Users shouldn't mess down here
// functions related to sky

// uniform FOG_COLOR is used

const vec3 horizonEdgeAbsCol = 1.0-horizonEdgeCol;

// sky colors - needs more tweaking

vec3 getUnderwaterCol(){
	return underwaterBaseCol*FOG_COLOR.b;
}

vec3 getZenithCol(float rainFactor){

	// value needs tweaking
	float val = max(FOG_COLOR.r*0.6,max(FOG_COLOR.g,FOG_COLOR.b));

	// zenith color
	vec3 zenithCol = (0.77*val*val + 0.33*val)*skyBaseCol;
	zenithCol += nightSkyCol*(0.4-0.4*FOG_COLOR.b);

	// rain sky
	float brightness = min(FOG_COLOR.g,0.26);
	brightness *= brightness*13.2;
	zenithCol = mix(zenithCol*(1.0+0.5*rainFactor),vec3(0.85,0.9,1.0)*brightness,rainFactor);

	return zenithCol;
}

vec3 getHorizonCol(float rainFactor){

	// value needs tweaking
	float val = max(FOG_COLOR.r*0.65,max(FOG_COLOR.g*1.1,FOG_COLOR.b));

	float sun = max(FOG_COLOR.r-FOG_COLOR.b,0.0);

	// horizon color
	vec3 horizonCol = horizonBaseCol*(((0.7*val*val) + (0.4*val) + sun)*2.4);

	horizonCol += nightSkyCol;

	horizonCol = mix(
		horizonCol,
		2.0*val*mix(vec3(0.7,1.0,0.9),skyBaseCol,daySkyClarity),
		val*val);

	// rain horizon
	float brightness = min(FOG_COLOR.g,0.26);
	brightness *= brightness*19.6;
	horizonCol = mix(horizonCol,vec3(brightness),rainFactor);

	return horizonCol;
}

vec3 getHorizonEdgeCol(vec3 horizonCol, float rainFactor){
	float val = (1.1-FOG_COLOR.b)*FOG_COLOR.g*2.1;
	val *= 1.0-rainFactor;

	vec3 tint = vec3(1.0)-val*horizonEdgeAbsCol;
	return horizonCol*tint;
}


// sunlight tinting
vec3 sunLightTint(vec3 night_color,vec3 morning_color,vec3 day_color,float dayFactor,float rain){

	float tintFactor = FOG_COLOR.g + 0.1*FOG_COLOR.r;
	float noon = clamp((tintFactor-0.37)/0.45,0.0,1.0);
	float morning = clamp((tintFactor-0.05)*3.125,0.0,1.0);

	float r = 1.0-rain;
	r *= r;

	return mix(vec3(0.65,0.65,0.75),mix(
		mix(night_color,morning_color,morning),
		mix(morning_color,day_color,noon),
		dayFactor),r*r);
}

// Colors end


// 1D sky gradient: moved to utilities/sky_gradient.glsl so the sky dome
// (sky.fragment) and the fog/reflection users share one implementation.


