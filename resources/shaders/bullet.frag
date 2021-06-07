uniform sampler2D texture;
uniform float renderCounter;
uniform vec2 speed;

// deformation strength
#define z 0.8

void main() {
    vec2 uv = gl_TexCoord[0].xy;
    vec2 samplerVec = vec2(0.);
    // calculate deformation
    if (speed.x > 0.5) {
        samplerVec.x = max(
            (speed.x + z) / (1. + z - speed.x) * (uv.x - 1.) + 1.,
            (1. + z - speed.x) / (speed.x + z) * uv.x
        );
    }
    else {
        samplerVec.x = min(
            (speed.x + z) / (1. + z - speed.x) * (uv.x - 1.) + 1.,
            (1. + z - speed.x) / (speed.x + z) * uv.x
        );
    }
    if (speed.y > 0.5) {
        samplerVec.y = max(
            (speed.y + z) / (1. + z - speed.y) * (uv.y - 1.) + 1.,
            (1. + z - speed.y) / (speed.y + z) * uv.y
        );
    }
    else {
        samplerVec.y = min(
            (speed.y + z) / (1. + z - speed.y) * (uv.y - 1.) + 1.,
            (1. + z - speed.y) / (speed.y + z) * uv.y
        );
    }
    // flip deformation
    samplerVec = vec2(1.) - samplerVec;

    // add some wiggle
    samplerVec.x += sin(renderCounter * 50.) / 40.;
    samplerVec.y += cos(renderCounter * 50.) / 40.;

    // sample texture
    vec4 color = texture2D(texture, samplerVec);

    // do some brightness hijinks
    color.r *= 1. + sin(1. + (renderCounter + uv.x / 20.) * 11.) / 3.;
    color.g *= 1. + sin(2. + (renderCounter + uv.x / 20.) * 11.) / 3.1;
    color.b *= 1. + sin((renderCounter + uv.x / 20.) * 11.) / 3.5;
    gl_FragColor = color;
}
