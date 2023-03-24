# mesh-viewer

Implements a simple PLY viewer

<img title="" src="README_images/toon_cow.png" alt="">

## How to build

*Windows*

Open git bash to the directory containing this repository.

```
mesh-viewer $ mkdir build
mesh-viewer $ cd build
mesh-viewer/build $ cmake ..
mesh-viewer/build $ start mesh-viewer.sln
```

Your solution file should contain two projects: `mesh-viewer` and `test-ply-mesh`.
To run from the git bash command shell, 

```
mesh-viewer/build $ ../bin/Debug/test-ply-mesh.exe
mesh-viewer/build $ ../bin/Debug/mesh-viewer.exe
```

*macOS*

Open terminal to the directory containing this repository.

```
mesh-viewer $ mkdir build
mesh-viewer $ cd build
mesh-viewer/build $ cmake ..
mesh-viewer/build $ make
```

To run each program from build, you would type

```
mesh-viewer/build $ ../bin/mesh-viewer
```

## Demo of basic features

# Camera movement

<video src='/README_images/Cam.mp4' />

# Read Models from Directory

<video width="window.innerWidth" controls>
    <source src="/README_images/Models.mp4" type="video/mp4">
</video>

# Normal Shader

<video width="window.innerWidth" controls>
    <source src="/README_images/Normal_Shader.mp4" type="video/mp4">
</video>

# Gouraud Shader

<video width="window.innerWidth" controls>
    <source src="/README_images/Gouraud_Shader.mp4" type="video/mp4">
</video>

# Phong Shader

<video width="window.innerWidth" controls>
    <source src="/README_images/Phong_Shader.mp4" type="video/mp4">
</video>

## Unique features

# Wobbly Shader

<video width="window.innerWidth" controls>
    <source src="/README_images/Wobbly_Shader.mp4" type="video/mp4">
</video>

# Toon Shader

<video width="window.innerWidth" controls>
    <source src="/README_images/Toon_Shader.mp4" type="video/mp4">
</video>
