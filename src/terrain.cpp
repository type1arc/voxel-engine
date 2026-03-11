#include "../include/terrain.hpp"
#include <cmath>

terrain::terrain(int32_t width, int32_t height, int32_t depth)
  : width(width), height(height), depth(depth)
{
  voxels.resize(width, std::vector<std::vector<int>>(height, std::vector<int>(depth, 0)));
}

void terrain::generate()
{
  for (int x = 0; x < width; x++)
{
    for (int z = 0; z < depth; z++)
    {
      int h = static_cast<int>((height / 2) + sin(x * 0.2f) * cos(z * 0.2f) * (height / 4)); 
      if (h < 0) h = 0;
      if (h >= height) h = height-1;

      for (int y = 0; y <= h; y++)
        voxels[x][y][z] = 1;
    }
  }
}

void terrain::build_mesh()
{
  vertices.clear();
  indices.clear();

  auto is_empty = [&](int x, int y, int z) {
    if (x < 0 || x >= width || 
        y < 0 || y >= height ||
        z < 0 || z >= depth) return true; 
    return voxels[x][y][z] == 0;
  };

  for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            for (int z = 0; z < depth; z++) {
                if (voxels[x][y][z] == 1) {
                    glm::vec3 pos(x, y, z);

                    if (is_empty(x+1,y,z)) add_face(pos, glm::vec3(1,0,0));
                    if (is_empty(x-1,y,z)) add_face(pos, glm::vec3(-1,0,0));
                    if (is_empty(x,y+1,z)) add_face(pos, glm::vec3(0,1,0));
                    if (is_empty(x,y-1,z)) add_face(pos, glm::vec3(0,-1,0));
                    if (is_empty(x,y,z+1)) add_face(pos, glm::vec3(0,0,1));
                    if (is_empty(x,y,z-1)) add_face(pos, glm::vec3(0,0,-1));
                }
            }
        }
    }
}

void terrain::add_face(glm::vec3 pos, glm::vec3 dir) {
    glm::vec3 up, right;

    if (dir == glm::vec3(1,0,0)) {        // +X
        up    = glm::vec3(0,1,0);
        right = glm::vec3(0,0,1);
    } else if (dir == glm::vec3(-1,0,0)) { // -X
        up    = glm::vec3(0,1,0);
        right = glm::vec3(0,0,-1);
    } else if (dir == glm::vec3(0,1,0)) {  // +Y
        up    = glm::vec3(0,0,1);
        right = glm::vec3(1,0,0);
    } else if (dir == glm::vec3(0,-1,0)) { // -Y
        up    = glm::vec3(0,0,-1);
        right = glm::vec3(1,0,0);
    } else if (dir == glm::vec3(0,0,1)) {  // +Z
        up    = glm::vec3(0,1,0);
        right = glm::vec3(-1,0,0);
    } else if (dir == glm::vec3(0,0,-1)) { // -Z
        up    = glm::vec3(0,1,0);
        right = glm::vec3(1,0,0);
    }

    glm::vec3 base = pos + dir * 0.5f;

    glm::vec3 v0 = base - right*0.5f - up*0.5f;
    glm::vec3 v1 = base + right*0.5f - up*0.5f;
    glm::vec3 v2 = base + right*0.5f + up*0.5f;
    glm::vec3 v3 = base - right*0.5f + up*0.5f;

    unsigned int start = vertices.size() / 6; // 6 floats per vertex

    auto push_vertex = [&](glm::vec3 v) {
        vertices.push_back(v.x);
        vertices.push_back(v.y);
        vertices.push_back(v.z);
        vertices.push_back(dir.x);
        vertices.push_back(dir.y);
        vertices.push_back(dir.z);
    };

    push_vertex(v0);
    push_vertex(v1);
    push_vertex(v2);
    push_vertex(v3);

    indices.push_back(start+0);
    indices.push_back(start+1);
    indices.push_back(start+2);
    indices.push_back(start+2);
    indices.push_back(start+3);
    indices.push_back(start+0);
}
