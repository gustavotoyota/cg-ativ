#include <cg-ativ.h>

#include <fstream>

using namespace std;

Mesh::Mesh(std::string fileName) {
    loadObj(fileName);
}

const std::vector<vec3>& Mesh::getVerts() const {
    return verts;
}

const std::vector<vec2>& Mesh::getUVs() const {
    return uvs;
}

const std::vector<vec3>& Mesh::getNormals() const {
    return normals;
}

void Mesh::loadObj(string fileName) {
    ifstream file(fileName);

    vector<vec3> objVerts;
    vector<vec2> objUVs;
    vector<vec3> objNormals;
    vector<int> objIndices;
 
    string line;
    while (getline(file, line)) {
		stringstream sstr(line);
        
		string type;
		sstr >> type;
        
        if (type == "v")
            pushVert(sstr, objVerts);
        else if (type == "vt")
            pushUV(sstr, objUVs);
        else if (type == "vn")
            pushNormal(sstr, objNormals);
        else if (type == "f")
            pushFace(sstr, objIndices);
    }

    verts.resize(objIndices.size() / 3);
    uvs.resize(objIndices.size() / 3);
    normals.resize(objIndices.size() / 3);

    for (size_t i = 0, j = 0; j < objIndices.size(); ++i, j += 3) {
        verts[i] = objVerts[objIndices[j] - 1];
        uvs[i] = objUVs[objIndices[j + 1] - 1];
        normals[i] = objNormals[objIndices[j + 2] - 1];
    }
}

void Mesh::pushVert(std::stringstream & sstr, vector<vec3> &verts) {
    vec3 vert;
    sstr >> vert.x >> vert.y >> vert.z;
    verts.push_back(vert);
}

void Mesh::pushUV(std::stringstream & sstr, vector<vec2> &uvs) {
    vec2 uv;
    sstr >> uv.x >> uv.y;
    uvs.push_back(uv);
}

void Mesh::pushNormal(std::stringstream & sstr, vector<vec3> &normals) {
    vec3 normal;
    sstr >> normal.x >> normal.y >> normal.z;
    normals.push_back(normal);
}

void Mesh::pushFace(std::stringstream & sstr, vector<int> &indices) {
    for (int i = 0; i < 3; ++i) {
        int index;
        sstr >> index;
        indices.push_back(index);
        sstr.ignore();
        sstr >> index;
        indices.push_back(index);
        sstr.ignore();
        sstr >> index;
        indices.push_back(index);
    }
}
