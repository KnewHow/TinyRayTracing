# TinyRayTracer
A Demo of Ray Tracer, refer:https://github.com/ssloy/tinyraytracer/wiki/Part-1:-understandable-raytracing. In this branch, I add BVH accelerator to prompt effective, you can read [this](http://www.pbr-book.org/3ed-2018/Primitives_and_Intersection_Acceleration/Bounding_Volume_Hierarchies.html#sec:sah) to get more about BVH.


# Effective test
bvh: 256 * 256 took 21 seconds
     512 * 512 took 87 seconds
     1366 * 768 took 243 seconds

origial: 256 * 256 took 43 seconds
         512 * 512 took 180 seconds
          1366 * 768 took 443 seconds