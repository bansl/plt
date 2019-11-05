uniform float opacity ;
uniform sampler2D texture;

void main()
{
    vec4 color = texture2D(texture, gl_TexCoord[0].xy);
    color.a *= opacity ;
    gl_FragColor = color ;
}