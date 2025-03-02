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

#include "Texture2D.hpp"

Texture2D::Texture2D() : 
    Width           {0        },
    Height          {0        },
    Internal_Format {GL_RGBA  },
    Image_Format    {GL_RGBA  },
    Wrap_S          {GL_REPEAT},
    Wrap_T          {GL_REPEAT},
    Filter_Min      {GL_LINEAR},
    Filter_Max      {GL_LINEAR}
{
    glGenTextures(1, &ID);
}

Texture2D::~Texture2D()
{
    //stbi_image_free(data_);
}

void Texture2D::Generate(uint32_t width, uint32_t height, uint8_t* data)
{
    Width = width;
    Height = height;
    data_ = data;
    // create Texture
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexImage2D(GL_TEXTURE_2D, 0, Internal_Format, width, height, 0, Image_Format, GL_UNSIGNED_BYTE, data);
    // set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Filter_Max);
    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);
}
void Texture2D::loadTexture (const std::string & path)
{
    path_ = std::string(path);
    int w, h, nchannels;
    uint8_t *data { stbi_load(path.c_str(), &w, &h, &nchannels, STBI_rgb_alpha) };
    if (!data)
    {
        std::cerr<<"texture loading not worked TEXTURE2D.CPP:38:\nTEXTURE:" << path << "\n";
    }
    this->Generate(w,h,data);
}
void Texture2D::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, ID);
}