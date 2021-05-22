uniform vec2 pos;
uniform vec2 size;

#define grid 256.

void main() {
    vec2 coord = (gl_TexCoord[0].xy ) + pos;
    vec3 color = vec3(0.0);
    if (coord.x > 100. || coord.x < -100.) {
        color.r = 1.0;
    }
    if (coord.y > 100. || coord.y < -100.) {
        color.g = .5;
    }
    if (mod(coord.x, 1000.0) < 10. || mod(coord.y, 1000.0) < 10.) {
        color.b = 1.0;
        color.r = sin((coord.x + coord.y) / 50.) / 2.0 + .5;
    }

    gl_FragColor = vec4(color, 1.0);
}
