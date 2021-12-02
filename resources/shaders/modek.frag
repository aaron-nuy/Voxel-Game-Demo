#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;


// Imports from Vertex Shader
in vec3 color;
in vec2 texCoord;
in vec3 Normal;
in vec3 crntPos;

// Gets the Texture Unit from the main function
uniform sampler2D diffuse0;
uniform sampler2D specular0;
// Gets the color of the light from the main function
uniform vec4 lightColor;
// Gets the position of the light from the main function
uniform vec3 lightPos;
// Gets the position of the camera from the main function
uniform vec3 camPos;

vec4 directionalLight(float ambientIntensity,int power){

	// ambient lighting
	float ambient = ambientIntensity;
	
	vec3 lightVector = normalize(lightPos);

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVector);
	float diffuse = max(dot(normal, lightVector), 0.0f);

	// specular lighting
	float specularLight = 0.25f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), power);
	float specular = specAmount * specularLight;

	return (texture(diffuse0, texCoord) * lightColor * (diffuse + ambient)  + texture(specular0,texCoord).r*specular);
}
vec4 pointLight(float ambientIntensity,int power, float distanceModifier){

	// Light vector direction relative to the object
	vec3 lightVector = lightPos - crntPos;

	// Distance between the light source and the object
	float Distance = length(lightVector); 

	// ambient lighting
	float ambient = ambientIntensity;
	
	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVector);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.5f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), power);
	float specular = specAmount * specularLight;

	// Distance formula 
	Distance = distanceModifier*pow(Distance,2)+ 0.010f*Distance + 1.00f;

	return (texture(diffuse0, texCoord) * lightColor * (diffuse + ambient)  + texture(specular0,texCoord).r*specular)/(Distance);
}
vec4 spotLight(float distanceModifier){
	
	// Light vector direction relative to the object
	vec3 lightVector = lightPos-  crntPos;

	// Distance between the light source and the object
	float Distance = length(lightVector); 


	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVector);
	float diffuse;
	float innerCone = 0.95f;
	float outerCone = 0.90f;
	// calculates the angle between the normal vector and light then does things
	float angle = dot(normal,lightDirection);
	diffuse = clamp((angle-outerCone)/(innerCone-outerCone),0.0f,1.0f);

	// Distance formula 
	Distance = distanceModifier*pow(Distance,2)+ 0.04f*Distance + 1.0f;

	return (texture(diffuse0, texCoord) * texture(specular0,texCoord).r * lightColor * diffuse)*0.5/Distance;
}
float linearizeDepth(float depth){
	float near = 0.1f;
	float far = 100.0f;
	return (2.0*near*far) / (far + near - (depth * 2.0 - 1.0) * (far -near));
}
float logisticDepth(float depth){
	float steepness = 0.5;
	float offset = 0.8f;
	float zVal = linearizeDepth(depth);
	return (1/ (1+exp(-steepness * (zVal - offset ))));
}

void main()
{
	// outputs final color
	//float depth = logisticDepth(gl_FragCoord.z);
	FragColor = pointLight(0.2f,8,0.0008f);
}