#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 vertexColor;
layout(location = 2) in vec2 TextureCoordinates;

uniform mat4 ModelTrans; // matrix that is responsible for transforming the model itself
uniform mat4 MVP; //matrix that transforms the model so that it is viewable
out vec4 fragmentColor;

void main()
{ 
	//TransformedVector = TranslationMatrix * RotationMatrix * ScaleMatrix * OriginalVector;
	fragmentColor = vertexColor;
	vec4 TransformedVector = ModelTrans * position;//TranslationMatrix * RotationMatrix * ScaleMatrix * OriginalVector;
	gl_Position = MVP * TransformedVector;
}

#shader fragment
#version 330 core
layout(location = 0) out vec4 color;

in vec4 fragmentColor;
uniform vec4 u_color;

void main()
{
	color = fragmentColor * u_color;
}
