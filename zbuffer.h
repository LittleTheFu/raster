#ifndef _ZBUFFER_H_
#define _ZBUFFER_H_

#include <vector>
#include <limits>

class ZBuffer {
public:
    ZBuffer(int width, int height);

    bool testAndUpdate(int x, int y, float depth);
    bool test(int x, int y, float depth) const;
    float getDepth(int x, int y) const;

    int width() const;
    int height() const;

    void clear();

private:
    int width_, height_;
    std::vector<float> buffer_;  // 存储每个像素的深度值
};

#endif // _ZBUFFER_H_