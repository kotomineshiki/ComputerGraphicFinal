#version 330 core
#define NUM_TAPS 8

uniform vec4 timeColor;
uniform sampler2D modelTexture;

in vec2 vTexCoord;

out vec4 color;


uniform sampler2D tSource;
uniform sampler2D tSourceLow;

vec2 poisson[NUM_TAPS];

vec2 pixelSizeHigh;
vec2 pixelSizeLow;

vec2 vMaxCoC = vec2(5.0, 10.0);

float radiusScale = 0.4;


vec4 PoissonDOFFilter(vec2 texCoord){
	vec4 cOut;
	float discRadius, discRadiusLow, centerDepth;

	cOut = texture2D(tSource, texCoord);
	centerDepth = cOut.a;

	discRadius = abs(cOut.a * vMaxCoC.y - vMaxCoC.x);
	discRadiusLow = discRadius * radiusScale;
	cOut = vec4(0., 0., 0., 0.);

	for(int t = 0; t < NUM_TAPS; t++){
		vec2 coordLow = texCoord + (pixelSizeLow * poisson[t] * discRadiusLow);
		vec2 coordHigh = texCoord + (pixelSizeHigh * poisson[t] * discRadius);

		vec4 tapLow = texture2D(tSource, coordLow);
		vec4 tapHigh = texture2D(tSource, coordHigh);

		float tapBlur = abs(tapHigh.a * 2.0 - 1.0);
		vec4 tap = mix(tapHigh, tapLow, tapBlur);

		tap.a = (tap.a >= centerDepth) ? 1.0 : abs(tap.a * 2.0 - 1.0);

		cOut.rgb += tap.rgb * tap.a;
		cOut.a += tap.a;
	}
	return (cOut / cOut.a);
}

float near = 0.1; 
float far  = 100.0; 
  
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main()
{ 
	//color = texture(modelTexture, vTexCoord);
	float depth = LinearizeDepth(gl_FragCoord.z) / far;
	color = vec4(vec3(depth), 1.0);
	//color = vec4(1.0, 1.0, 0.0, 1.0);
	//color = vec4(vTexCoord.x, vTexCoord.y, 1.0, 1.0);//texture(churchTexture, vTexCoord); 
}