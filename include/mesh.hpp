#ifndef MESH_H
#define MESH_H

#pragma once
#include <vector>
#include <glad/gl.h> 

class Mesh {
public:
    unsigned int vao, vbo, ebo;
    GLsizei index_count;

    Mesh(const std::vector<float>& vertices,
         const std::vector<unsigned int>& indices,
         const std::vector<int>& attribute_sizes) 
    {
        index_count = static_cast<GLsizei>(indices.size());

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);

        // VBO
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, 
                     vertices.size() * sizeof(float), 
                     vertices.data(), 
                     GL_STATIC_DRAW);

        // EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
                     indices.size() * sizeof(unsigned int), 
                     indices.data(), 
                     GL_STATIC_DRAW);

        // Attribute setup
        int stride = 0;
        for (int size : attribute_sizes) stride += size;
        stride *= sizeof(float);

        int offset = 0;
        for (unsigned int i = 0; i < attribute_sizes.size(); ++i) {
            glVertexAttribPointer(i, attribute_sizes[i], GL_FLOAT, GL_FALSE,
                                  stride, (void*)(offset * sizeof(float)));
            glEnableVertexAttribArray(i);
            offset += attribute_sizes[i];
        }

        glBindVertexArray(0);
    }

    void bind() const {
        glBindVertexArray(vao);
    }

    void draw() const {
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    ~Mesh() {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
    }
};


#endif // !MESH_H


