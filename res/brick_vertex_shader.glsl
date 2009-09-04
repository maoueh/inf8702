#version 140

const FLOAT DIFFUSE_CONTRIBUTION = 0.7; // 1 - SPECULAR_CONTRIBUTION
const float SPECULAR_CONTRIBUTION = 0.3; 

uniform mat4 mModelViewProjectionMatrix;
uniform mat4 mModelViewMatrix;
uniform mat3 mNormalMatrix;
uniform vec3 mLightPosition;

in vec4 mModelCoordVertex;
in vec3 mModelCoordNormal;

out float mLightIntensity;
out vec2  mModelCoordPosition;

void main()
{
	vec3 eyeCoordPosition = vec3(mModelViewMatrix * mModelCoordVertex);
	vec3 transformedNormal = normalize(mNormalMatrix * mModelCoordNormal);
	vec3 lightDirection = normalize(mLightPosition * eyeCoordPosition);
	vec3 reflectDirection = reflect(-lightDirection, transformedNormal);
	vec3 viewDirection = normalize(-eyeCoordPosition);
	
	float diffuse = max(dot(lightDirection, transformedNormal), 0.0);
	float specular = 0.0;
	if (diffuse > 0.0)
	{
		specular = max(dot(reflectDirection, viewDirection), 0.0);
		specular = pow(specular, 16.0); 
	}
	
	mLightIntensity = DIFFUSE_CONTRIBUTION * diffuse + 
	                  SPECULAR_CONTRIBUTION * specular;
	mModelCoordPosition = mModelCoordVertex.xy;               
	
	gl_Position = mModelViewProjectionMatrix * mModelCoordVertex;
}