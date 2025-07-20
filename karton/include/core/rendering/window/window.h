#ifndef WINDOW_H
#define WINDOW_H

#include <functional>

class Window {
public:
    virtual ~Window() = default;

    virtual void Init(int width, int height, const char* title) = 0;
    virtual void PollEvents() = 0;
    virtual void SwapBuffers() = 0;
    virtual bool ShouldClose() const = 0;
    virtual void Terminate() = 0;

    virtual float GetTime() const = 0;

    // Input
    virtual bool IsKeyPressed(int key) const = 0;

    virtual double GetMouseX() const = 0;
    virtual double GetMouseY() const = 0;
    virtual double GetScrollOffsetX() const = 0;
    virtual double GetScrollOffsetY() const = 0;

    virtual void ResetScrollOffsets() = 0;
    virtual void ResetMouseDelta() = 0;
};


#endif // !WINDOW_H