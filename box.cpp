#include "box.h"
#include <Eigen/Dense>

Box::Box(float scale)
{
    init(scale);
}

void Box::flipNormals()
{
    for (auto& vertex : m_vertices) {
        vertex.normal = -vertex.normal; // 将法线向量的每个分量乘以 -1
    }
}

void Box::init(float scale)
{
    // l: left, r: right, t: top, b: bottom, f: front, b: back
    Eigen::Vector4f ltf{-1.0f * scale, 1.0f * scale, 1.0f * scale, 1.0f};
    Eigen::Vector4f rtf{1.0f * scale, 1.0f * scale, 1.0f * scale, 1.0f};
    Eigen::Vector4f lbf{-1.0f * scale, -1.0f * scale, 1.0f * scale, 1.0f};
    Eigen::Vector4f rbf{1.0f * scale, -1.0f * scale, 1.0f * scale, 1.0f};

    Eigen::Vector4f ltb{-1.0f * scale, 1.0f * scale, -1.0f * scale, 1.0f};
    Eigen::Vector4f rtb{1.0f * scale, 1.0f * scale, -1.0f * scale, 1.0f};
    Eigen::Vector4f lbb{-1.0f * scale, -1.0f * scale, -1.0f * scale, 1.0f};
    Eigen::Vector4f rbb{1.0f * scale, -1.0f * scale, -1.0f * scale, 1.0f};
    //----------------------------------------------------------------

    Eigen::Vector3f color_front{1.0f, 0.0f, 0.0f};
    Eigen::Vector3f color_back{0.0f, 1.0f, 0.0f};
    Eigen::Vector3f color_left{0.0f, 0.0f, 1.0f};
    Eigen::Vector3f color_right{1.0f, 1.0f, 0.0f};
    Eigen::Vector3f color_top{1.0f, 0.0f, 1.0f};
    Eigen::Vector3f color_bottom{0.0f, 1.0f, 1.0f};

    // front face (+z) - A-B-C and D-C-B (ltf-lbf-rtf and rbf-rtf-lbf)
    Vertex f_v0{ltf, color_front, Eigen::Vector2f{0.0f, 0.0f}, Eigen::Vector3f{0.0f, 0.0f, 1.0f}}; // A
    Vertex f_v1{lbf, color_front, Eigen::Vector2f{0.0f, 1.0f}, Eigen::Vector3f{0.0f, 0.0f, 1.0f}}; // B
    Vertex f_v2{rtf, color_front, Eigen::Vector2f{1.0f, 0.0f}, Eigen::Vector3f{0.0f, 0.0f, 1.0f}}; // C

    Vertex f_v3{rbf, color_front, Eigen::Vector2f{1.0f, 1.0f}, Eigen::Vector3f{0.0f, 0.0f, 1.0f}}; // D
    Vertex f_v4{rtf, color_front, Eigen::Vector2f{1.0f, 0.0f}, Eigen::Vector3f{0.0f, 0.0f, 1.0f}}; // C
    Vertex f_v5{lbf, color_front, Eigen::Vector2f{0.0f, 1.0f}, Eigen::Vector3f{0.0f, 0.0f, 1.0f}}; // B

    // back face (-z) - 需要注意逆时针方向，从背面看是逆时针，但我们定义顶点时要保持一致的“正面”朝向
    Vertex ba_v0{rtb, color_back, Eigen::Vector2f{0.0f, 0.0f}, Eigen::Vector3f{0.0f, 0.0f, -1.0f}}; // 对应背面的 A
    Vertex ba_v1{rbb, color_back, Eigen::Vector2f{0.0f, 1.0f}, Eigen::Vector3f{0.0f, 0.0f, -1.0f}}; // 对应背面的 B
    Vertex ba_v2{ltb, color_back, Eigen::Vector2f{1.0f, 0.0f}, Eigen::Vector3f{0.0f, 0.0f, -1.0f}}; // 对应背面的 C

    Vertex ba_v3{lbb, color_back, Eigen::Vector2f{1.0f, 1.0f}, Eigen::Vector3f{0.0f, 0.0f, -1.0f}}; // 对应背面的 D
    Vertex ba_v4{ltb, color_back, Eigen::Vector2f{1.0f, 0.0f}, Eigen::Vector3f{0.0f, 0.0f, -1.0f}}; // 对应背面的 C
    Vertex ba_v5{rbb, color_back, Eigen::Vector2f{0.0f, 1.0f}, Eigen::Vector3f{0.0f, 0.0f, -1.0f}}; // 对应背面的 B

    // left face (-x)
    Vertex l_v0{ltb, color_left, Eigen::Vector2f{0.0f, 0.0f}, Eigen::Vector3f{-1.0f, 0.0f, 0.0f}}; // A
    Vertex l_v1{lbb, color_left, Eigen::Vector2f{0.0f, 1.0f}, Eigen::Vector3f{-1.0f, 0.0f, 0.0f}}; // B
    Vertex l_v2{ltf, color_left, Eigen::Vector2f{1.0f, 0.0f}, Eigen::Vector3f{-1.0f, 0.0f, 0.0f}}; // C

    Vertex l_v3{lbb, color_left, Eigen::Vector2f{0.0f, 1.0f}, Eigen::Vector3f{-1.0f, 0.0f, 0.0f}}; // B
    Vertex l_v4{lbf, color_left, Eigen::Vector2f{1.0f, 1.0f}, Eigen::Vector3f{-1.0f, 0.0f, 0.0f}}; // D
    Vertex l_v5{ltf, color_left, Eigen::Vector2f{1.0f, 0.0f}, Eigen::Vector3f{-1.0f, 0.0f, 0.0f}}; // C

    // right face (+x)
    Vertex r_v0{rtf, color_right, Eigen::Vector2f{0.0f, 0.0f}, Eigen::Vector3f{1.0f, 0.0f, 0.0f}}; // A
    Vertex r_v1{rbf, color_right, Eigen::Vector2f{0.0f, 1.0f}, Eigen::Vector3f{1.0f, 0.0f, 0.0f}}; // B
    Vertex r_v2{rtb, color_right, Eigen::Vector2f{1.0f, 0.0f}, Eigen::Vector3f{1.0f, 0.0f, 0.0f}}; // C

    Vertex r_v3{rbf, color_right, Eigen::Vector2f{0.0f, 1.0f}, Eigen::Vector3f{1.0f, 0.0f, 0.0f}}; // B
    Vertex r_v4{rbb, color_right, Eigen::Vector2f{1.0f, 1.0f}, Eigen::Vector3f{1.0f, 0.0f, 0.0f}}; // D
    Vertex r_v5{rtb, color_right, Eigen::Vector2f{1.0f, 0.0f}, Eigen::Vector3f{1.0f, 0.0f, 0.0f}}; // C

    // top face (+y)
    Vertex t_v0{ltf, color_top, Eigen::Vector2f{0.0f, 1.0f}, Eigen::Vector3f{0.0f, 1.0f, 0.0f}}; // A
    Vertex t_v1{ltb, color_top, Eigen::Vector2f{0.0f, 0.0f}, Eigen::Vector3f{0.0f, 1.0f, 0.0f}}; // B
    Vertex t_v2{rtf, color_top, Eigen::Vector2f{1.0f, 1.0f}, Eigen::Vector3f{0.0f, 1.0f, 0.0f}}; // C

    Vertex t_v3{ltb, color_top, Eigen::Vector2f{0.0f, 0.0f}, Eigen::Vector3f{0.0f, 1.0f, 0.0f}}; // B
    Vertex t_v4{rtb, color_top, Eigen::Vector2f{1.0f, 0.0f}, Eigen::Vector3f{0.0f, 1.0f, 0.0f}}; // D
    Vertex t_v5{rtf, color_top, Eigen::Vector2f{1.0f, 1.0f}, Eigen::Vector3f{0.0f, 1.0f, 0.0f}}; // C

    // bottom face (-y)
    Vertex bo_v0{lbf, color_bottom, Eigen::Vector2f{0.0f, 0.0f}, Eigen::Vector3f{0.0f, -1.0f, 0.0f}}; // A
    Vertex bo_v1{rbf, color_bottom, Eigen::Vector2f{1.0f, 0.0f}, Eigen::Vector3f{0.0f, -1.0f, 0.0f}}; // B
    Vertex bo_v2{lbb, color_bottom, Eigen::Vector2f{0.0f, 1.0f}, Eigen::Vector3f{0.0f, -1.0f, 0.0f}}; // C

    Vertex bo_v3{rbf, color_bottom, Eigen::Vector2f{1.0f, 0.0f}, Eigen::Vector3f{0.0f, -1.0f, 0.0f}}; // B
    Vertex bo_v4{rbb, color_bottom, Eigen::Vector2f{1.0f, 1.0f}, Eigen::Vector3f{0.0f, -1.0f, 0.0f}}; // D
    Vertex bo_v5{lbb, color_bottom, Eigen::Vector2f{0.0f, 1.0f}, Eigen::Vector3f{0.0f, -1.0f, 0.0f}}; // C

    // 将创建的顶点存入 m_vertices 数组
    m_vertices[0] = f_v0;
    m_vertices[1] = f_v1;
    m_vertices[2] = f_v2;
    m_vertices[3] = f_v3;
    m_vertices[4] = f_v4;
    m_vertices[5] = f_v5;
    m_vertices[6] = ba_v0;
    m_vertices[7] = ba_v1;
    m_vertices[8] = ba_v2;
    m_vertices[9] = ba_v3;
    m_vertices[10] = ba_v4;
    m_vertices[11] = ba_v5;
    m_vertices[12] = l_v0;
    m_vertices[13] = l_v1;
    m_vertices[14] = l_v2;
    m_vertices[15] = l_v3;
    m_vertices[16] = l_v4;
    m_vertices[17] = l_v5;
    m_vertices[18] = r_v0;
    m_vertices[19] = r_v1;
    m_vertices[20] = r_v2;
    m_vertices[21] = r_v3;
    m_vertices[22] = r_v4;
    m_vertices[23] = r_v5;
    m_vertices[24] = t_v0;
    m_vertices[25] = t_v1;
    m_vertices[26] = t_v2;
    m_vertices[27] = t_v3;
    m_vertices[28] = t_v4;
    m_vertices[29] = t_v5;
    m_vertices[30] = bo_v0;
    m_vertices[31] = bo_v1;
    m_vertices[32] = bo_v2;
    m_vertices[33] = bo_v3;
    m_vertices[34] = bo_v4;
    m_vertices[35] = bo_v5;
}

const std::array<Vertex, 36>& Box::getVertices() const
{
    return m_vertices;
}