Background white

dir = ["perylene-BN2-0046",
"perylene-BN2-0064",
"perylene-BN2-0079",
"perylene-BN2-0084",
"perylene-BN2-0086",
"perylene-BN2-0093",
"perylene-BN2-0095",
"perylene-BN2-0097",
"perylene-BN2-0100",
"perylene-BN2-0101",
"perylene-BN2-0110",
"perylene-BN2-0112",
"perylene-BN2-0144",
"perylene-BN2-0152",
"perylene-BN2-0156",
"perylene-BN2-0161",
"perylene-BN2-0162",
"perylene-BN2-0171",
"perylene-BN2-0174",
"perylene-BN2-0221",
"perylene-BN2-0225",
"perylene-BN2-0226",
"perylene-BN2-0228",
"perylene-BN2-0150"]

function loadSO(i){
load @{dir[i]+"/pyrelene_d2h_singlets_S0_casscf_cc-pvdz.molden"}
color carbon [0 200 0]
color bond [200 200 200]
color Hydrogen [120 120 120]
mo 66
mo fill
mo nomesh
mo translucent
mo cutoff 0.02
zoom 80
write IMAGE 2160 1440 PNG 2 @{dir[i]+"HOMO_SO.png"}
mo 67
write IMAGE 2160 1440 PNG 2 @{dir[i]+"LUMO_SO.png"}
zap
}

function loadSOS1(i){
load @{dir[i]+"/pyrelene_d2h_singlets_S0S1_casscf_cc-pvdz.molden"}
color carbon [0 200 0]
color bond [200 200 200]
color Hydrogen [120 120 120]
mo 66
mo fill
mo nomesh
mo translucent
mo cutoff 0.02
zoom 80
write IMAGE 2160 1440 PNG 2 @{dir[i]+"HOMO_SOS1.png"}
mo 67
write IMAGE 2160 1440 PNG 2 @{dir[i]+"LUMO_SOS1.png"}
zap
}

function loadT(i){
load @{dir[i]+"/pyrelene_d2h_triplets_casscf_cc-pvdz.molden"}
color carbon [0 200 0]
color bond [200 200 200]
color Hydrogen [120 120 120]
mo 66
mo fill
mo nomesh
mo translucent
mo cutoff 0.02
zoom 80
write IMAGE 2160 1440 PNG 2 @{dir[i]+"HOMO_T.png"}
mo 67
write IMAGE 2160 1440 PNG 2 @{dir[i]+"LUMO_T.png"}
zap
}

for(var i =dir.length -1; i < dir.length; i++){
    loadSO(i)
    loadSOS1(i)
    loadT(i)
}
