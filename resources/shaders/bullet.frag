uniform sampler2D texture;
uniform float renderCounter;
uniform vec2 speed;

void main() {
    vec2 coord = gl_TexCoord[0].xy;
    gl_FragColor = gl_Color * texture2D(texture, coord);
}
