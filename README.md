# TorchAbinito
In quantum Mechanics we try to solve schordinger equations. This project is approach to incorporate machinel learning systems to quantum chemistry
### Time-independent Schordinger equation

$$ \hat{H} |\Psi \rangle = E|\Psi \rangle $$

$$ \left [ \frac{-\hbar}{2m} \nabla^{2}  + V(\mathbf{r})\right ] \Psi (\mathbf{r}) = E\Psi (\mathbf{r}) $$
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
