 //####################################################################
//# GNU Free Documentation License                                   #
//# Version 1.3, 3 November 2008                                     #
//#                                                                  #
//# Copyright (C) 2021 Lumina Studio                                 #
//# (Paula Garcia Morales, Laura Gil Lopez, Jorge Perez Dominguez,   #
//#  Alba Ruiz Maiques, Javier Sibada Lopez, Miguel Teruel Carvajal) #
//#                                                                  #
//# Everyone is permitted to copy and distribute verbatim copies     #
//# of this license document, but changing it is not allowed.        #
//####################################################################
//#                                                                  #
//#                                                                  #
//#                                                                  #
//#                                                                  #
//#                                                                  #
//####################################################################

#include "MeshLUM.hpp"
 
 
 
MeshLUM::MeshLUM(std::vector<VertexLUM> vertices, std::vector<unsigned int> indices, std::vector<TextureLUM> textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    // now that we have all the required data, set the vertex buffers and its attribute pointers.
    setupMesh();
}
MeshLUM::~MeshLUM()
{   

}

    // render the mesh
void MeshLUM::draw(Shader &shader) 
{    
    for(size_t i {0}; i < static_cast<size_t>(textures.size()); ++i){
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        
        name = textures[i].type;

        if(name == "texture_diffuse")
            number = std::to_string(++diffuseNr);
        else if(name == "texture_specular")
            number = std::to_string(++specularNr); // transfer unsigned int to string
        else if(name == "texture_normal")
            number = std::to_string(++normalNr); // transfer unsigned int to string
         else if(name == "texture_height")
            number = std::to_string(++heightNr); // transfer unsigned int to string

        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
        // draw mesh
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES_ADJACENCY, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        // always good practice to set everything back to defaults once configured.
        glActiveTexture(GL_TEXTURE0);
    }
    // initializes all the buffer objects/arrays
void MeshLUM::setupMesh()
{
    // create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexLUM), &vertices[0], GL_STATIC_DRAW);  
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexLUM), (void*)0);
    
    // vertex normals
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexLUM), (void*)offsetof(VertexLUM, Normal));
    
    // vertex texture coords
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexLUM), (void*)offsetof(VertexLUM, TexCoords));
    
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexLUM), (void*)offsetof(VertexLUM, Tangent));
    
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(VertexLUM), (void*)offsetof(VertexLUM, Bitangent));
	
    // ids
    glEnableVertexAttribArray(5);
	glVertexAttribIPointer(5, 4, GL_INT, sizeof(VertexLUM), (void*)offsetof(VertexLUM, m_BoneIDs));
	// weights
    glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(VertexLUM), (void*)offsetof(VertexLUM, m_Weights));

    glBindVertexArray(0);
}