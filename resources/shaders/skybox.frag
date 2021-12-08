#version 330 core

out vec4 FragColor;

in vec3 texCoords;
uniform samplerCube skybox;
uniform vec3 skyColor;

float linearizeDepth(float depth){
	float near = 0.03f;
	float far = 100.0f;
	return (2.0*near*far) / (far + near - (depth * 2.0 - 1.0) * (far -near));
}
float logisticDepth(float depth){
	float steepness = 0.006f;
	float offset = 40.0f;
	float zVal = linearizeDepth(depth);
	return (1/ (1+exp(-steepness * (zVal - offset ))));
}


void main()
{
	
	float depth = 1-logisticDepth(gl_FragCoord.z);
	FragColor = texture(skybox,texCoords)*depth + vec4(logisticDepth(gl_FragCoord.z) * skyColor,1.0);
}