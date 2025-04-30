#include "texture.h"
#include <iostream>

Texture::Texture(const std::string &fileName) : m_width(0), m_height(0)
{
     // decode
     unsigned error = lodepng::decode(m_data, m_width, m_height, fileName.c_str());

     // if there's an error, display it
     if (error)
         std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
}

void Texture::getColor(float u, float v, uint8_t& r, uint8_t& g, uint8_t& b) const
{
    //something wrong here, uv passed was out of range
    //should be fixed later
    float uu = u - (int)u;
    float vv = v - (int)v;

    uint8_t uPixel = (static_cast<uint8_t>(uu * m_width));
    uint8_t vPixel = (static_cast<uint8_t>(vv * m_height));

    uint8_t index = vPixel * m_width + uPixel;

    r = m_data.at(4 * index + 0) / 255.0f;
    g = m_data.at(4 * index + 1) / 255.0f;
    b = m_data.at(4 * index + 2) / 255.0f;
}