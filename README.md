# The-ray-tracer++

A complete C++ rewrite of the ray tracer I wrote previously in C

# Specifications

- Shapes Supported
    - Sphere
    - Triangles
    - Cubes
    - Cylinders
    - Planes
- Shading and lighting
    - triangles support normal smoothing
    - realistic dielectric support
      - refraction
      - reflection
      - schlicks approximation
      - only isolated transparent object
    
- Shadows
    - only sharp shadows
    - no support for smooth shadows nor antialiasing
    
- Acceleration Structures
    - Kd Trees
- Model Loading
    - only wavefront obj through [tinyobjloader](https://github.com/tinyobjloader/tinyobjloader)
- Running
    - CPU
        - Single thread
        - Multi-threading through OpenMP
    - GPU
        - NVIDIA-CUDA ( to be added )
    

# Some Screenshots

## Reflective Stanford Dragon

<img src=screenshots/stanford-dragon-reflective.png />

## Metal Stanford Lucy Statue

<img src=screenshots/lucy.png />

## Glass Stanford Bunny

<img src= screenshots/glass_bunny.png />

# Some Notes
Some objects seem to have weird pixel colors at some regions,
I don't think its due to self intersection.