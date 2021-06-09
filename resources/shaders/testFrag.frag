uniform sampler2D texture;
uniform float renderCount;

void main() {
    vec2 uv = gl_TexCoord[0].xy;
    // pixalate if under 5 sec
    if (renderCount < 5.) {
        float factor = pow(2., floor(renderCount));
        uv = floor(uv * factor) / factor;
    } else {
        // move after 5 sec
        uv.x += sin(renderCount - 5.) / 30.;
    }
    gl_FragColor = texture2D(texture, uv) * gl_Color;
}
