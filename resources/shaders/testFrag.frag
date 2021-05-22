uniform sampler2D texture;
uniform float renderCount;

void main() {
    vec2 coord = gl_TexCoord[0].xy;
    coord.x = coord.x + sin(coord.y * 2.0 + renderCount) / 16.;
    vec4 pixel = texture2D(texture, coord);
    pixel.r = sin(gl_TexCoord[0].x + renderCount) / 2.0 + 0.5;
    pixel.g = sin(gl_TexCoord[0].y + renderCount / 10.0) / 2.0 + 0.5;
    gl_FragColor = gl_Color * pixel;
}
