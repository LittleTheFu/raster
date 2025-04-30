#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <string>
#include <vector>
#include <lodepng/lodepng.h>

class Texture {
public:
    Texture(const std::string& fileName); // 补充构造函数声明
    void getColor(float u, float v, uint8_t& r, uint8_t& g, uint8_t& b) const; // 补充getColor方法声明

private:
    std::vector<unsigned char> m_data;
    unsigned m_width;
    unsigned m_height;
};

#endif // _TEXTURE_H_