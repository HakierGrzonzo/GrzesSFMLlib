uniform sampler2D texture;
uniform float renderCounter;
uniform float hp;
uniform vec2 scale;

void main() {
    vec2 uv = gl_TexCoord[0].xy / scale;
    uv.x += sin(uv.y *20. + renderCounter * 10.) / 20.;
    vec4 color = texture2D(texture, uv);
    color.a = min(1. - hp, color.a);
    gl_FragColor = color * gl_Color;
}
