# MarchingCloud : Point cloud rendering
This project aims to offer a program capable of rendering point clouds using sphere tracing.
This is a university project on which the students will be graded.

## Members  
Khélian LARVET
Sylvain LECLERC  
(University of Montpellier : M2 IMAGINE, 2022-2023)

## Dependencies
- C++ : v17.0  
- CUDA : v10.1 
- Qt : v5.7  
- libQGLViewer v2.8  
```console
apt install nvidia-cuda-toolkit
apt install qt5-default
apt install libqglviewer-dev-qt5
```

## Execute Commands
```console
qmake
make
./marchingCloud
```

## Project file modification for CUDA
- SYSTEM_TYPE : 32 or 64 depending on your system  
- CUDA_ARCH : sm_30 depending on your type of CUDA architecture, for example 'compute_10', 'compute_11', 'sm_10'