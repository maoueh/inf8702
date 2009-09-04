#version 140

uniform vec3 mBrickColor, mMortarColor;
uniform vec2 mBrickSize;
uniform vec2 mBrickProportion;

in vec2  mModelCoordPosition;
in float mLightIntensity;

out vec4 mFragmentColor;

void main()
{
	vec2 position = mModelCoordPosition / mBrickSize;
	if ( fract(position.y * 0.5) > 0.5 )
		position.x += 0.5;
		
	position = fract(position);
	
	float useBrick = step(position, mBrickProportion);
	vec4 color = mix(mMortarColor, mBrickColor, useBrick.x * useBrick.y);
	mFragmentColor = vec4(color * mLightIntensity, 1.0);