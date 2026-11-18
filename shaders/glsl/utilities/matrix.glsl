// Newb shader

// Shared matrix helpers.
// Kept in one place because entity.vertex and banner.vertex used to carry
// their own copies with different precision, and they drifted apart.
// highp is required: entity and banner vertices live far from the origin.

highp vec3 matmulxyz(highp mat4 w, highp vec4 p){
	return vec3(
		dot(vec4(w[0][0],w[1][0],w[2][0],w[3][0]),p),
		dot(vec4(w[0][1],w[1][1],w[2][1],w[3][1]),p),
		dot(vec4(w[0][2],w[1][2],w[2][2],w[3][2]),p)
	);
}
