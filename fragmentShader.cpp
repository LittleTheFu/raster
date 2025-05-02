#include "fragmentShader.h"

FragmentShader::FragmentShader(FrameBuffer &frameBuffer, const Light &light, const Texture &texture)
    : texture_(texture),
      light_(light),
      frameBuffer_(frameBuffer)
{
}

void FragmentShader::apply(const Vertex &vertex)
{
    int x = static_cast<int>(vertex.position.x());
    int y = static_cast<int>(vertex.position.y());

    if (x < 0 || x >= frameBuffer_.getColorBuffer().width() ||
        y < 0 || y >= frameBuffer_.getColorBuffer().height())
    {
        return; // 超出范围，返回
    }

    float u = vertex.texCoord.x();
    float v = vertex.texCoord.y();

    float r = vertex.color.x();
    float g = vertex.color.y();
    float b = vertex.color.z();

    uint8_t texture_r, texture_g, texture_b;
    texture_.getColor(u, v, texture_r, texture_g, texture_b); // 获取纹理颜色
    
    Eigen::Vector3f ambient = light_.ambient();
    Eigen::Vector3f diffuse = light_.diffuse(vertex.worldPosition, vertex.normal);
    Eigen::Vector3f specular = light_.specular(vertex.viewDir, vertex.worldPosition, vertex.normal);
    Eigen::Vector3f finalColor = ambient + diffuse + specular; // 计算最终颜色

    finalColor = finalColor.cwiseProduct(Eigen::Vector3f{static_cast<float>(r), static_cast<float>(g), static_cast<float>(b)});
    finalColor = finalColor.cwiseProduct(Eigen::Vector3f{static_cast<float>(texture_r), static_cast<float>(texture_g), static_cast<float>(texture_b)}); // 乘以纹理颜色
    finalColor = finalColor.cwiseMax(0.0f).cwiseMin(255.0f); // 限制颜色范围在 0-255 之间

    if (!frameBuffer_.testAndUpdate(vertex.position.x(), vertex.position.y(), vertex.position.z(),
                                    finalColor.x(), finalColor.y(), finalColor.z(), 255)) // 更新帧缓冲区
    {
        return; // 更新失败，返回
    }
}