# Newb Shader MCPE - reviewed + extra effects

![Language](https://img.shields.io/badge/GLSL-8A2BE2)
![License](https://img.shields.io/github/license/devendrn/newb-shader-mcbe)

A vanilla styled lightweight shader for Minecraft PE: it keeps the default art style and adds lighting, plant waves, water, sky, fog and clouds on top of it.

**Only works for MCPE 1.18.12 and below (Android / iOS).** This is the GLSL generation, from before RenderDragon. For MCPE 1.20+ use [Newb X Legacy](https://github.com/devendrn/newb-x-mcbe) instead.

This repository is based on [devendrn/newb-shader-mcbe](https://github.com/devendrn/newb-shader-mcbe) (MIT), with a performance review pass and a set of additional effects on top. All original design and code credit belongs to devendrn.

## Changes against upstream

### Optimisation

| what | where | why it mattered |
| --- | --- | --- |
| `pow(color, 0.75)` replaced by `sqrt(sqrt(x^3))` | `config_utilities/color.h` | three pow calls (exp2+log2 each) ran on every terrain, entity, sky and banner pixel |
| vertex texture fetch guarded by `isColored` | `terrain.vertex` | glass, bars, ladders, torches and chains paid for a VTF they never read |
| `windStrength` evaluated lazily | `terrain.vertex` | `noise1D` used to run on every alpha tested vertex, now only inside the wave branches |
| sin/cos free hash | `terrain.vertex` (`fastRand`) | one `fract` instead of a transcendental per water vertex |
| `renderMist` no longer computes a dead `exp` | `config_utilities/global.h` | underwater overwrote the value anyway |
| `wetRefl` lowp raised to mediump | terrain and entity | 8 bit fresnel caused banding in wet reflections |
| `shadowIntensity` renamed `softShadowBase` | `terrain.vertex` | the old name was the inverse of the `shadow_intensity` config macro |

### New effects

Every effect is a compile time switch in `shaders/glsl/config_utilities/effects.h` (colour grading sits in `color.h`). Comment the define out and the code is not compiled at all, so turning an effect off is genuinely free.

| effect | define | runs in | cost |
| --- | --- | --- | --- |
| split toning, cool shadows warm highlights | `SPLIT_TONE` | fragment, all surfaces | one dot plus two mixes |
| per channel gain separation | `CHROMA_SHIFT` | fragment, all surfaces | two multiplies |
| travelling gust front for plants | `GUST_WIND` | terrain vertex | one sine |
| second water ripple | `WATER_DETAIL` | terrain vertex, water only | one sine |
| rain impact dents on water | `RAIN_RIPPLE` | terrain vertex, water only | one sine plus one hash |
| fake one bounce light | `BOUNCE_LIGHT` | terrain vertex | a few ALU, overworld and nether |
| horizon anchored light shafts | `SUN_SHAFTS` | sky fragment | about ten ALU |
| milky way band | `MILKY_WAY` | sky fragment | two sines, gated by sky brightness |
| star twinkle | `STAR_TWINKLE` | end sky fragment | one sine |
| entity rim light | `RIM_LIGHT` | entity vertex | two matrix multiplies per entity vertex |
| second cloud layer | `CLOUD_LAYER` | cloud vertex | one extra cloud noise sample |
| moving cloud shadows on the ground | `CLOUD_SHADOW`, `CLOUD_SHADOW_DIST` | terrain vertex | four fract hashes, not sampled past 48 blocks |
| light passing through tree leaves | `LEAF_TRANSMIT` | terrain vertex, leaves only | two ops |
| sun band on rain wet ground | `WET_SUN` | terrain vertex, rain only | reuses the water sun maths |
| vertical shafts underwater | `UNDERWATER_SHAFTS` | terrain vertex, underwater only | one sine pair |
| shooting stars | `SHOOTING_STARS` | sky fragment | two segment tests per meteor |
| sunrise tint on clouds | `CLOUD_SUN` | cloud vertex | a few ops |
| smooth ambient occlusion | `AO_SHARPEN` | terrain vertex | three ops, replaces a two step multiply |

The cloud shadow is the expensive one: it samples noise on every terrain vertex within 48 blocks. If a low end device struggles, comment `CLOUD_SHADOW` out first, it is the only new effect that touches all terrain vertices.

### Not implemented on purpose

- real bloom, SSAO, SSR, depth of field, screen space rain: this pipeline has no depth texture and no post process pass. A fake bloom would need a second additive pass on the terrain materials, which doubles the draw batches.
- fragment side water sparkle: it needs another varying, and the terrain fragment already uses almost all of the eight varying slots GLES2 guarantees. The vertex ripple plus reflection path covers it instead.
- concentric rain rings: a water face is four vertices, so there is no geometry to shape a ring with.

## Install

Same as upstream: patched Minecraft (YssPatch or DracoPatch) on Android or iOS, import the pack, enable it in global resources, restart the game. See the [installation guide](https://newb-shader.devendrn.com/guide/).

## Configure

`shaders/glsl/config_utilities/` holds the user facing values:

- `global.h` sun intensity, fog type, mist density
- `terrain.h` shadow edge, torch and cave brightness, wave intensities, water colours
- `sky.h` sky and sunrise colours
- `clouds.h` cloud size, speed, aurora
- `color.h` tonemapping, contrast, split toning
- `effects.h` every new effect above
- `extra.h` sun rotation, glow textures

## Licence

Source code: MIT, inherited from devendrn. Compiled resource packs: CC BY-ND 4.0, credit "Newb Shader" and the variant creator. This repository is not associated with Mojang or Microsoft.
