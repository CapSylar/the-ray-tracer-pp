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
    

## Some Screenshots

### reflective Stanford Dragon
<img src=screenshots/stanford-dragon-reflective.png />