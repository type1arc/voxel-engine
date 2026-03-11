#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <vector>
#include <glm/glm.hpp>

class terrain {
  private:
    int32_t width, height, depth;
    std::vector<std::vector<std::vector<int32_t>>> voxels;
    std::vector<float> vertices;
    std::vector<uint32_t> indices;

    void add_face(glm::vec3 pos, glm::vec3 dir);
  public:
    terrain(int32_t width, int32_t height, int32_t depth);
    void generate();
    void build_mesh();

    const std::vector<float>& get_vertices() const { return vertices; };
    const std::vector<uint32_t>& get_indices() const { return indices; };
};

#endif
