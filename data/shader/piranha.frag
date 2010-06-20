uniform sampler2D Texture1;
uniform sampler2D Texture2;
uniform float time;

void main (void)
{
	gl_FragColor = texture2D (Texture1, gl_TexCoord[0].st);
	if (time < 4.0)
	{
        vec4 Color = vec4 (0, 0, 0, 1);
        Color += texture2D (Texture2, gl_TexCoord[0] + vec2 (time, 0.0f)) / 2;
        Color += texture2D (Texture2, gl_TexCoord[0] - vec2 (time, 0.0f)) / 2;
        gl_FragColor += Color * 0.5f;
//		gl_FragColor *= texture2D (Texture2, gl_TexCoord[0] + vec2 (time, 0.0f)) / 2;
//		gl_FragColor *= texture2D (Texture2, gl_TexCoord[0] - vec2 (time, 0.0f)) / 2;
//		gl_FragColor += texture2D (Texture2, gl_TexCoord[0] + vec2 (0.0f, time)) / 4;
//		gl_FragColor += texture2D (Texture2, gl_TexCoord[0] - vec2 (0.0f, time)) / 4;
	}
	else if (time < 6.0)
	{
		gl_FragColor += texture2D (Texture2, gl_TexCoord[0].st) * 0.5f;
	}
	else
	{
		gl_FragColor += texture2D (Texture2, gl_TexCoord[0].st) * (1.0f + (time - 6.0f) * 4.f) * 0.5f;
	}    
}

