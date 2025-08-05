#type vertex
#version 300 es
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;

// out vec3 FragPos;
out vec2 TexCoords;


uniform mat4 uModelViewProjection;

void main()
{
  gl_Position = uModelViewProjection * vec4(a_Position, 1.0);
  TexCoords = a_TexCoord;
}

#type fragment
#version 300 es
precision mediump float;

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_normal1;

uniform bool u_UseNormalMap;
uniform bool u_UseDiffuseMap;

void main()
{
  vec3 normal;
  if(u_UseNormalMap){
    normal = texture(texture_normal1, TexCoords).rgb;
    normal = normalize(normal * 2.0 - 1.0);
  }
  else{
    normal = vec3(0.0,0.0,1.0);
  }

  vec3 color;
  if(u_UseDiffuseMap){
    color = texture(texture_diffuse1, TexCoords).rgb;
    if(color == vec3(0))
      color = vec3(0.5, 0.1, 0.6);
  }
  else{
    color = vec3(0.5, 0.1, 0.6);
  }
  FragColor = vec4(color, 1.0);
}
