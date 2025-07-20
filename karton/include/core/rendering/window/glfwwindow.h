#ifndef GLFWWINDOW_H
#define GLFWWINDOW_H

#include <rendering/window/window.h>
#include <GLFW/glfw3.h>

class GLFWWindow : public Window {
public:
    void Init(int width, int height, const char* title) override {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        glfwMakeContextCurrent(m_window);

        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        glfwSetWindowUserPointer(m_window, this);

        // Optional: set callbacks
        glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow*, int w, int h) {
            glViewport(0, 0, w, h);
            });

        // Glad must be loaded *after* context creation
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        m_lastX = width / 2.0f;
        m_lastY = height / 2.0f;

        glfwSetCursorPos(m_window, m_lastX, m_lastY);

        glfwSetCursorPosCallback(m_window, cursorPosCallback);
        glfwSetScrollCallback(m_window, scrollCallback);
    }

    void PollEvents() override {
        glfwPollEvents();
    }

    void SwapBuffers() override {
        glfwSwapBuffers(m_window);
    }

    bool ShouldClose() const override {
        return glfwWindowShouldClose(m_window);
    }

    void Terminate() override {
        glfwTerminate();
    }

    float GetTime() const override {
        return static_cast<float>(glfwGetTime());
    }

    bool IsKeyPressed(int key) const override {
        return glfwGetKey(m_window, key) == GLFW_PRESS;
    }

    double GetMouseX() const override { return m_mouseDeltaX; }
    double GetMouseY() const override { return m_mouseDeltaY; }
    double GetScrollOffsetX() const override { return m_scrollX; }
    double GetScrollOffsetY() const override { return m_scrollY; }

    void ResetScrollOffsets() override {
        m_scrollX = 0.0;
        m_scrollY = 0.0;
    }

    void ResetMouseDelta() override {
        m_mouseDeltaX = 0.0;
        m_mouseDeltaY = 0.0;
    }

    GLFWwindow* GetGLFWWindow() const { return m_window; }

private:
    GLFWwindow* m_window = nullptr;

    double m_mouseDeltaX = 0.0;
    double m_mouseDeltaY = 0.0;
    double m_lastX = 0.0;
    double m_lastY = 0.0;
    double m_scrollX = 0.0;
    double m_scrollY = 0.0;

    static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
        GLFWWindow* self = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        if (self) {
            self->m_mouseDeltaX = xpos - self->m_lastX;
            self->m_mouseDeltaY = self->m_lastY - ypos;

            self->m_lastX = xpos;
            self->m_lastY = ypos;
        }
    }

    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
        GLFWWindow* self = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        if (self) {
            self->m_scrollX += xoffset;
            self->m_scrollY += yoffset;
        }
    }
};

#endif // !GLFWWINDOW_H