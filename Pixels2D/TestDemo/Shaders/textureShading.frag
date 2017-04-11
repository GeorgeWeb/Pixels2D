#version 330

// the fragment shader operates on each pixel in a given polygon

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

// this is the 3 component float vector that gets outputted to the screen
// for each pixel.

out vec4 color;

uniform sampler2D mySampler;

void main()
{
    // cos(x) returns a number between -1 and 1, to convert it into the range 0 to 1
    // you simply do (cos(x) + 1.0) * 0.5
    
    vec4 textureColor = texture(mySampler, fragmentUV);
    
    // make crazy colors using time and position
    color = fragmentColor * textureColor;
}