#ifndef MESH_HEADER
#define MESH_HEADER

#include <string>
#include <vector>
#include <sstream>

struct vec2;
struct vec3;

class Mesh {
public:
    Mesh(std::string fileName);

    const std::vector<vec3> &getVerts() const;
    const std::vector<vec2> &getUVs() const;
    const std::vector<vec3> &getNormals() const;

    void loadObj(std::string fileName);
private:
    std::vector<vec3> verts;
    std::vector<vec2> uvs;
    std::vector<vec3> normals;
    
    void pushVert(std::stringstream &sstr, std::vector<vec3> &verts);
    void pushUV(std::stringstream &sstr, std::vector<vec2> &uv);
    void pushNormal(std::stringstream &sstr, std::vector<vec3> &normals);
    void pushFace(std::stringstream &sstr, std::vector<int> &indices);
};

#endif