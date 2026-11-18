// Newb shader

/*""""""""""""""""""""""""""""""""""""""*/
/* COLOR CORRECTION */


// Type - Tone mapping type 
// 1 - Exponential
// 2 - Simple Reinhard
// 3 - Extended Reinhard (Default)
// 4 - ACES
#define TONEMAPPING_TYPE 3

// Toggle + Value - Exposure
//#define EXPOSURE 1.3

// Value - Contrast
// 0.75 is the fast path (two sqrt instead of three pow per pixel).
// If you change this to any other value, also enable CONTRAST_EXACT below.
#define CONTRAST 0.75

// Toggle - Use exact pow(CONTRAST) instead of the sqrt approximation
//#define CONTRAST_EXACT

// Toggle + Value - Saturation
//#define SATURATION 1.4

// Toggle + Color - Tinting
//#define TINT vec3(1.0,0.75,0.5)

// Value - Split toning, cool shadows and warm highlights (0-1)
#define SPLIT_TONE 0.35

// Value - Per channel gain separation, a cheap lens character (0-0.1)
#define CHROMA_SHIFT 0.02


/*""""""""""""""""""""""""""""""""""""""*/


// Code starts here - Users shouldn't mess down here
// Color correction and tone mapping

// see https://64.github.io/tonemapping/

#if TONEMAPPING_TYPE==3
// extended reinhard tonemapping
vec3 tonemap(vec3 x){
	//float white = 4.0;
	//float white_scale = 1.0/(white*white);
	float white_scale = 0.063;

	x = (x*(1.0+(x*white_scale)))/(1.0+x);

	//x = (x*1.32)/(1.0+x);

	return x;
}

#elif TONEMAPPING_TYPE==4
// aces tone mapping
vec3 tonemap(vec3 x){
	x *= 0.85;
	const float a = 1.04;
	const float b = 0.03;
	const float c = 0.93;
	const float d = 0.56;
	const float e = 0.14;
	return clamp((x * (a * x + b)) / (x * (c * x + d) + e), 0.0, 1.0);
}

#elif TONEMAPPING_TYPE==2
// simple reinhard tonemapping
vec3 tonemap(vec3 x){
	return x/(1.0 + x);
}

#elif TONEMAPPING_TYPE==1
// exponential tonemapping
vec3 tonemap(vec3 x){
	return 1.0-exp(-x*0.8);
}

#endif

// Contrast lift.
// x^0.75 == sqrt(sqrt(x^3)): two sqrt instructions instead of a pow
// (exp2+log2) per channel, and this runs on every terrain/entity/sky/banner
// pixel of the screen. Enable CONTRAST_EXACT for any other CONTRAST value.
vec3 contrastLift(vec3 color){
#ifdef CONTRAST_EXACT
	return pow(color, vec3(CONTRAST));
#else
	color = color*color*color;
	return sqrt(sqrt(color));
#endif
}

vec3 colorCorrection(vec3 color){
	#ifdef EXPOSURE
		color *= EXPOSURE;
	#endif

	color = tonemap(color);

	// actually supposed to be gamma correction
	color = contrastLift(color);

	#ifdef SPLIT_TONE
		// graded after the tonemap so it survives highlight compression:
		// one luminance dot and two mixes
		float lum = dot(color, vec3(0.21,0.71,0.08));
		vec3 grade = mix(vec3(0.92,1.0,1.10), vec3(1.08,1.0,0.92), clamp(lum*1.4,0.0,1.0));
		color *= mix(vec3(1.0), grade, SPLIT_TONE);
	#endif

	#ifdef CHROMA_SHIFT
		// red and blue gain apart by a hair - free, and reads as lens character
		color.r *= 1.0+CHROMA_SHIFT;
		color.b *= 1.0-CHROMA_SHIFT;
	#endif

	#ifdef SATURATION
		color = mix(vec3(dot(color,vec3(0.21, 0.71, 0.08))), color, SATURATION);
	#endif

	#ifdef TINT
		color *= TINT;
	#endif

	return color;
}

