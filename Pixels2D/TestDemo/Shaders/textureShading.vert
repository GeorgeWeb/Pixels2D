#version 330

// the vertex shader operates on each vertex

// input data from the VBO, each vertex is 2 floats
in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;

out vec2 fragmentPosition;
out vec4 fragmentColor;
out vec2 fragmentUV;

uniform mat4 P;

void main()
{
    // set the x,y position on the screen
    gl_Position.xy = (P * vec4(vertexPosition, 0.0, 1.0)).xy;
    
	// the z position is zero since we are in 2D
    gl_Position.z = 0.0;
    
    // indicate that the coordinates are normalized
    gl_Position.w = 1.0;
    
    fragmentPosition = vertexPosition;
    
    fragmentColor = vertexColor;
    
    fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
}