attribute float Distortion;
attribute float Distance;

varying float FinalDistortion;
varying float FinalDistance;

void main (void)
{
	FinalDistortion = Distortion != 0.f ? 1.0f : 0.0f;
	FinalDistance = Distance / 512.f;// > 0.f ? 1.0f : 0.0f;

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

	gl_FogFragCoord = gl_FogCoord;
	
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_TexCoord[1] = gl_MultiTexCoord1;
	gl_TexCoord[2] = gl_MultiTexCoord2;
	gl_TexCoord[3] = gl_MultiTexCoord3;
}

