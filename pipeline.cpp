// #include "pipeline.h"

// Pipeline::Pipeline(int width, int height, FrameBuffer &frameBuffer, const Light &light, const ShadowMapCamera &shadowMapCamera)
//     : fragmentShader_(frameBuffer, light),
//       shadowMapCamera_(shadowMapCamera)
// {
//     screenWidth_ = width;
//     screenHeight_ = height;

//     // 初始化模型矩阵、视图矩阵和投影矩阵
//     modelMatrix_ = Eigen::Matrix4f::Identity();
//     viewMatrix_ = Eigen::Matrix4f::Identity();
//     projectionMatrix_ = Eigen::Matrix4f::Identity();
//     mvpMatrix_ = Eigen::Matrix4f::Identity();

//     calculateNDCMatrix(); // 计算NDC矩阵

//     isDirty_ = true; // 初始时需要更新MVP矩阵
// }

// void Pipeline::setTexture(const std::shared_ptr<Texture> &texture)
// {
//     fragmentShader_.setTexture(texture); // 设置纹理
// }

// void Pipeline::setModelMatrix(const Eigen::Matrix4f &modelMatrix)
// {
//     // vertexShader_.setModelMatrix(modelMatrix); // 设置模型矩阵
// }

// void Pipeline::setViewMatrix(const Eigen::Matrix4f &viewMatrix)
// {
//     // vertexShader_.setViewMatrix(viewMatrix); // 设置视图矩阵
// }

// void Pipeline::setProjectionMatrix(const Eigen::Matrix4f &projectionMatrix)
// {
//     // vertexShader_.setProjectionMatrix(projectionMatrix);
// }

// Vertex Pipeline::getScreenVertex(const Vertex &vertex)
// {
//     Vertex vertexNdc = vertexShader_.apply(vertex); // 应用顶点着色器
//     vertexNdc.position /= vertexNdc.position.w();
//     vertexNdc.position = ndcMatrix_ * vertexNdc.position; // 转换到NDC坐标系

//     return vertexNdc; // 返回x, y, z坐标
// }

// void Pipeline::drawScreenTriangle(const Vertex &v0, const Vertex &v1, const Vertex &v2)
// {
//     // 对顶点按 y 坐标排序
//     std::array<Vertex, 3> vertices = {v0, v1, v2};
//     std::sort(vertices.begin(), vertices.end(), [](const Vertex &a, const Vertex &b)
//               { return a.position.y() < b.position.y(); });

//     const Vertex &top = vertices[0];
//     const Vertex &middle = vertices[1];
//     const Vertex &bottom = vertices[2];

//     for (int y = static_cast<int>(top.position.y()); y <= static_cast<int>(bottom.position.y()); ++y)
//     {
//         Vertex leftVertex, rightVertex;
//         float t_segment; // 插值比例

//         if (y <= middle.position.y())
//         {
//             float y_top_mid = middle.position.y() - top.position.y();
//             if (std::abs(y_top_mid) < 1e-6)
//                 t_segment = 0.0f;
//             else
//                 t_segment = (y - top.position.y()) / y_top_mid;
//             leftVertex = top.interpolate(middle, t_segment);

//             float y_top_bottom = bottom.position.y() - top.position.y();
//             if (std::abs(y_top_bottom) < 1e-6)
//                 t_segment = 0.0f;
//             else
//                 t_segment = (y - top.position.y()) / y_top_bottom;
//             rightVertex = top.interpolate(bottom, t_segment);
//         }
//         else
//         {
//             float y_mid_bottom = bottom.position.y() - middle.position.y();
//             if (std::abs(y_mid_bottom) < 1e-6)
//                 t_segment = 0.0f;
//             else
//                 t_segment = (y - middle.position.y()) / y_mid_bottom;
//             leftVertex = middle.interpolate(bottom, t_segment);

//             float y_top_bottom = bottom.position.y() - top.position.y();
//             if (std::abs(y_top_bottom) < 1e-6)
//                 t_segment = 0.0f;
//             else
//                 t_segment = (y - top.position.y()) / y_top_bottom;
//             rightVertex = top.interpolate(bottom, t_segment);
//         }

//         if (leftVertex.position.x() > rightVertex.position.x())
//         {
//             std::swap(leftVertex, rightVertex);
//         }

//         for (int x = static_cast<int>(leftVertex.position.x()); x <= static_cast<int>(rightVertex.position.x()); ++x)
//         {
//             float alpha = (x - leftVertex.position.x()) / (rightVertex.position.x() - leftVertex.position.x());

//             if (alpha < 0.0f || alpha > 1.0f || std::isnan(alpha))
//             {
//                 continue;
//             }

//             Vertex interpolatedVertex = leftVertex.interpolate(rightVertex, alpha);
//             interpolatedVertex.position.x() = static_cast<float>(x);
//             interpolatedVertex.position.y() = static_cast<float>(y);
//             interpolatedVertex.position.w() = 1.0f;

//             fragmentShader_.apply(interpolatedVertex, shadowMapCamera_); // 应用片段着色器
//         }
//     }
// }

// // void Pipeline::calculateNDCMatrix()
// // {
// //     ndcMatrix_ = Eigen::Matrix4f::Identity();

// //     // 设置齐次坐标的缩放和平移
// //     ndcMatrix_(0, 0) = 0.5f * screenWidth_;  // x轴的缩放
// //     ndcMatrix_(1, 1) = 0.5f * screenHeight_; // y轴的缩放
// //     ndcMatrix_(0, 3) = 0.5f * screenWidth_;  // x轴的平移
// //     ndcMatrix_(1, 3) = 0.5f * screenHeight_; // y轴的平移

// //     // y轴翻转的处理
// //     ndcMatrix_(1, 1) *= -1.0f;
// // }