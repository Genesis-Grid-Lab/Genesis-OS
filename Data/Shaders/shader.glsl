#type vertex

attribute vec3 aPosition;

uniform mat4 uModelViewProjection;

void main()
{
  gl_Position = uModelViewProjection * vec4(aPosition, 1.0);
}

#type fragment
precision mediump float;

void main()
{
  gl_FragColor = vec4(0.0, 1.0, 1.0, 1.0);
}
