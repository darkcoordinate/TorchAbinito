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
