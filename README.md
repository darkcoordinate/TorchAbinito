# TorchAbinito
This script is to be used for visualizing molecule on jmol
```
Background white
color carbon [0 200 0]
color bond [200 200 200]
color Hydrogen [120 120 120]
```
```
write image pngj filename.png
```
```
connect (atomno=1) (atomno=2) DELETE
```

Read and write the file in xyz
```
import ase.io as asi
file = asi.read("file.xyz","index=300")
asi.write("test.xyz", file, "xyz")
```
```
Background white
color carbon [0 200 0]
color bond [200 200 200]
color Hydrogen [120 120 120]
write IMAGE 2160 1440 PNG 2 "perylene-BN2-0046.png"
```

```
Background white
color carbon [0 200 0]
color bond [200 200 200]
color Hydrogen [120 120 120]
mo 66
mo fill
mo nomesh
mo translucent
mo cutoff 0.02
```
```
write IMAGE 2160 1440 PNG 2 "perylene-BN2-0046.png"
```
```
vec3 turbo(in float x) {
  const vec4 kRedVec4 = vec4(0.13572138, 4.61539260, -42.66032258, 132.13108234);
  const vec4 kGreenVec4 = vec4(0.09140261, 2.19418839, 4.84296658, -14.18503333);
  const vec4 kBlueVec4 = vec4(0.10667330, 12.64194608, -60.58204836, 110.36276771);
  const vec2 kRedVec2 = vec2(-152.94239396, 59.28637943);
  const vec2 kGreenVec2 = vec2(4.27729857, 2.82956604);
  const vec2 kBlueVec2 = vec2(-89.90310912, 27.34824973);
  
  x = clamp(x, 0.0, 1.0);
  vec4 v4 = vec4( 1.0, x, x * x, x * x * x);
  vec2 v2 = v4.zw * v4.z;
  return vec3(
    dot(v4, kRedVec4)   + dot(v2, kRedVec2),
    dot(v4, kGreenVec4) + dot(v2, kGreenVec2),
    dot(v4, kBlueVec4)  + dot(v2, kBlueVec2)
  );
}
```
```
vec3 firePalette(float i) {   float T = 1000. * (3.-i);   vec3 L = vec3(7.4, 5.6, 4.4);   L = pow(L, vec3(5.0)) * (exp(1.43876719683e5 / (T * L)) - 1.0);  return 1.0 - exp(-5e8 / (L/1.)); }
```
