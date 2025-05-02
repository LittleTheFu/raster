#include "fragmentShader.h"

FragmentShader::FragmentShader(FrameBuffer &frameBuffer, const Light &light)
    : light_(light),
      frameBuffer_(frameBuffer)
{
}

void FragmentShader::setTexture(const std::shared_ptr<Texture>& texture)
{
    texture_ = texture; // 设置纹理
}

void FragmentShader::apply(const Vertex &vertex, const ShadowMapCamera &shadowMapCamera)
{
    if(!frameBuffer_.getZBuffer().test(vertex.position.x(), vertex.position.y(), vertex.position.z()))
    {
        return; // 如果深度测试失败，则返回
    }
    
    // Eigen::Vector4f worldPos{vertex.worldPosition.x(), vertex.worldPosition.y(), vertex.worldPosition.z(), 1.0f};
    Vertex tmp_v{vertex};
    tmp_v.position.x() = vertex.worldPosition.x();
    tmp_v.position.y() = vertex.worldPosition.y();
    tmp_v.position.z() = vertex.worldPosition.z();
    tmp_v.position.w() = 1.0f; // 设置齐次坐标

    //测试片段是否在阴影贴图中
    Eigen::Vector4f shadowMapPos = shadowMapCamera.getScreenVertex(tmp_v).position; // 获取阴影贴图坐标
    Eigen::Vector3f shadowMapPos3 = {shadowMapPos.x(), shadowMapPos.y(), shadowMapPos.z() - 0.0001f};
    if(!shadowMapCamera.testZBuffer(shadowMapPos3))
    {
        frameBuffer_.testAndUpdate(vertex.position.x(), vertex.position.y(), vertex.position.z(),
                                    0, 0, 0, 255); // 更新帧缓冲区
        return; // 如果片段在阴影贴图中，则返回
    }

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

    if(texture_)
    {
        uint8_t texture_r, texture_g, texture_b;
        texture_->getColor(u, v, texture_r, texture_g, texture_b); // 获取纹理颜色

        r *= texture_r;
        g *= texture_g;
        b *= texture_b;
    }
    else
    {
        r *= 255;
        g *= 255;
        b *= 255; // 如果没有纹理，则使用颜色值
    }
    
    Eigen::Vector3f ambient = light_.ambient();
    Eigen::Vector3f diffuse = light_.diffuse(vertex.worldPosition, vertex.normal);
    Eigen::Vector3f specular = light_.specular(vertex.viewDir, vertex.worldPosition, vertex.normal);
    Eigen::Vector3f finalColor = ambient + diffuse + specular; // 计算最终颜色

    finalColor = finalColor.cwiseProduct(Eigen::Vector3f{static_cast<float>(r), static_cast<float>(g), static_cast<float>(b)});
    finalColor = finalColor.cwiseMax(0.0f).cwiseMin(255.0f); // 限制颜色范围在 0-255 之间

    if (!frameBuffer_.testAndUpdate(vertex.position.x(), vertex.position.y(), vertex.position.z(),
                                    finalColor.x(), finalColor.y(), finalColor.z(), 255)) // 更新帧缓冲区
    {
        return; // 更新失败，返回
    }
}