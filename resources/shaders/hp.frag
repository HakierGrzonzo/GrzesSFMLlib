uniform sampler2D texture;
uniform float renderCounter;
uniform float hp;
uniform vec2 scale;

#define VERY_LOW 0.33

void main() {
    vec2 uv = gl_TexCoord[0].xy / scale;
    uv.x += sin(uv.y *20. + renderCounter * 10.) / 40.;
    uv.y += cos(uv.x + renderCounter) / 40.;
    vec4 color = texture2D(texture, uv);
    //color.a = min(1. - hp, color.a);
    color.a *= 1. - hp;
    if (hp < VERY_LOW) {
        color.a += (1. - hp) / 2.;
    }
    gl_FragColor = color * gl_Color;
}
