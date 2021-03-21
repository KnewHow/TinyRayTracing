#include "model.h"

#include <fstream>
#include <iostream>
#include <sstream>

std::optional<IntersectResult> Model::rayIntersect(const vec3f& orig, const vec3f& d) const {
    if(rayIntersectWithAABB(orig, d)) {
        float t = std::numeric_limits<float>::max();
        vec3i face;
        bool isIntersection = false;
        std::array<vec3f,3> tri;
        for(const auto& f: faces) {
            tri[0] = vertices[f.x];
            tri[1] = vertices[f.y];
            tri[2] = vertices[f.z];
            auto r = rayIntersectWithTriangle(orig, d, tri);
            if(r.has_value() && r.value() < t) {
                t = r.value();
                isIntersection = true;
                face = f;
            }
        }
        
        if(isIntersection) {
            vec3f hitPoint = orig + t * d;
            vec3f normal = cross((vertices[face.y] - vertices[face.x]), (vertices[face.z] - vertices[face.x])).normalize();
            return IntersectResult{t, hitPoint, material, normal};
        }
    }
    return std::nullopt;
}

std::optional<float> Model::rayIntersectWithTriangle(const vec3f& orig, const vec3f& d, const std::array<vec3f, 3>& tri) const {
    vec3f E1 = tri[1] - tri[0];
    vec3f E2 = tri[2] - tri[0];
    vec3f S = orig - tri[0];
    vec3f S1 = cross(d, E2);
    vec3f S2 = cross(S, E1);
    vec3f v = vec3f(S2 * E2, S1 * S, S2 * d);
    vec3f r = 1 / (S1 * E1) * v;
    if(r.x > 0 && r.y > 0 && r.z > 0 && (1 - r.y - r.z) > 0) {
        return r.x;
    } else {
        return std::nullopt;
    }
}


bool Model::rayIntersectWithAABB(const vec3f& orig, const vec3f& d) const {
     float t_min_x = (box.min.x - orig.x) / d.x;
     float t_min_y = (box.min.y - orig.y) / d.y;
     float t_min_z = (box.min.z - orig.z) / d.z;

     float t_max_x = (box.max.x - orig.x) / d.x;
     float t_max_y = (box.max.y - orig.y) / d.y;
     float t_max_z = (box.max.z - orig.z) / d.z;

     if(d.x < 0) {
         std::swap(t_max_x, t_min_x);
     }
     if(d.y < 0) {
         std::swap(t_max_y, t_min_y);
     }
     if(d.z < 0) {
         std::swap(t_max_z, t_min_z);
     }

    float t_enter = std::max(t_min_x, std::max(t_min_y, t_min_z));
    float t_exit = std::min(t_max_x, std::min(t_max_y, t_max_z));
    return t_exit > t_enter && t_exit >= 0;
 }

Model::Model(const std::string& p, const Material& m)
    :filepath(p), vertices(), faces(), material(m)
{
    box.min = vec3f(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
    box.max = vec3f(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max(), -std::numeric_limits<float>::max());
    std::ifstream in;
    in.open(filepath, std::ifstream::in);
    if(!in.is_open()) {
        std::cerr << "Open file failure, filepath is: " << filepath << std::endl;
        return;
    }
    std::string line;
    while (!in.eof())
    {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if(!line.compare(0, 2, "v ")) {
            iss >> trash;
            vec3f v;
            for(int i = 0; i < 3; i++) {
                iss >> v[i];
                if(v[i] < box.min[i]) {
                    box.min[i] = v[i];
                }
                if(v[i] > box.max[i]) {
                    box.max[i] = v[i];
                }
            }
            vertices.push_back(v);
        } else if(!line.compare(0, 2, "f ")) {
            iss >> trash;
            int idx, cnt = 0;
            vec3i f;
            while (iss >> idx)
            {
                idx--; // face index in object start with 1, let it - 1 will corresponding with vertices index
                f[cnt++] = idx;
            }

            if(cnt == 3)
                faces.push_back(f);
            
        }

    }
    std::cout << "load model completion, vertices is: " << vertices.size() << ", faces is: " << faces.size() << std::endl;
}

Model::~Model() {

}