#version 130

uniform float uRedComponent, uGreenComponent, uBlueComponent;

void main()
{
	gl_FragColor = vec4(uRedComponent, uGreenComponent, uBlueComponent, 1.0); 
}