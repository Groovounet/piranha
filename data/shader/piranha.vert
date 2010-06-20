// 15/10/2004 - Les variables déclarées "varying" servent à la communication avec le code C++.
uniform float time;

vec4 oscilation (vec4 v);

void main (void)
{
	vec4 v = vec4 (gl_Vertex.x, gl_Vertex.y, gl_Vertex.z, 1.0);
	vec4 v1 = oscilation (v);

	gl_Position = gl_ModelViewProjectionMatrix * v1;
	gl_TexCoord[0] = gl_MultiTexCoord0;
}

vec4 oscilation (vec4 v)
{
	v.z  = sin (gl_Vertex.x + time * 8) / (time / 5);
	v.z += cos (gl_Vertex.y + time * 8) / (time / 5);

	return v;
}

