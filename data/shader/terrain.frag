uniform sampler2D ColorMapGood;
uniform sampler2D ColorMapEvil;
uniform sampler2D DetailMap;
uniform sampler2D Lightmap;

varying float FinalDistortion;
varying float FinalDistance;

const vec4 FogColor = vec4 (0.627, 0.875, 1.0, 1.0);

void main (void)
{
	vec4 TexColor = texture2D (ColorMapGood, gl_TexCoord[0].st) * (1.0 - FinalDistortion);
	TexColor += texture2D (ColorMapEvil, gl_TexCoord[1].st) * FinalDistortion;
	TexColor *= texture2D (Lightmap, gl_TexCoord[3].st);
	TexColor *= texture2D (DetailMap, gl_TexCoord[2].st);
	gl_FragColor = TexColor;
}

