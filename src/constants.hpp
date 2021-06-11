#pragma once

#define pi 3.14
#define SCREEN_HEIGHT 400
#define SCREEN_WIDTH 400

// various conversion ratios
#define box2sfRatio 1000
#define sf2alRatio .001
#define chunkRatio .001

/* resolution ratio is 2 at 2560x1056
 *
 * resolutions scale in both axis so we put a 2 here
 *                             ↓
 */
#define resolutionRatio (4. / (2. / (2560. + 1056.)))

