#include "texture.h"
#include <iostream>
#include <cmath>

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
    float uu = std::fmod(u, 1.0f);
    float vv = std::fmod(v, 1.0f);

    // // Clamp the values to the range [0, 1]
    uu = std::max(0.0f, std::min(1.0f, uu));
    vv = std::max(0.0f, std::min(1.0f, vv));

    size_t uPixel = (static_cast<size_t>(uu * m_width));
    size_t vPixel = (static_cast<size_t>(vv * m_height));

    size_t index = vPixel * m_width + uPixel;
    r = m_data.at(4 * index + 0);
    g = m_data.at(4 * index + 1);
    b = m_data.at(4 * index + 2);
}