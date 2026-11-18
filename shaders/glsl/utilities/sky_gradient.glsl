// Newb shader

// 3 colour sky gradient shared by the sky dome (sky.fragment) and by everything
// that needs the same gradient: mist, fog, water reflection, wet reflection.
// Single source of truth - terrain and sky must never diverge again.

vec3 renderSky(vec3 reddishTint, vec3 horizonColor, vec3 zenithColor, float h){

	h = 1.0-h*h;

	float hsq = h*h;

	// gradient 1  h^16
	// gradient 2  h^8 mix h^2
	float gradient1 = hsq*hsq*hsq*hsq;
	float gradient2 = 0.6*gradient1 + 0.4*hsq;
	gradient1 *= gradient1;

	horizonColor = mix(horizonColor, reddishTint, gradient1);
	return mix(zenithColor,horizonColor, gradient2 );

}
