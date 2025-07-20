#include <memory>

#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <rendering/camera.h>
#include <rendering/model/model.h>
#include <rendering/renderingbackendprovider.h>

#include <rendering/shader/OpenGLShader.h>

#include <utils/filemanager.h>
#include <utils/enums.h>

// Constants
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Global State
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

bool firstMouse = true;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void processInput(Window& window);
void updateMouse(double xposIn, double yposIn);

int main() {
    
    BackendType backend = BackendType::OpenGL;

    std::unique_ptr<Window> window = RenderingBackendProvider::CreateWindow(backend);
    window->Init(SCR_WIDTH, SCR_HEIGHT, "KARTON");

    std::unique_ptr<Renderer> renderer = RenderingBackendProvider::CreateRenderer(backend);
    renderer->Init();

    std::shared_ptr<RenderFactory> renderFactory = RenderingBackendProvider::CreateFactory(backend);

    std::unique_ptr<OpenGLShader> shader = std::make_unique<OpenGLShader>(FileManager::GetShaderPathCStr("default_model.vert"),
        FileManager::GetShaderPathCStr("default_model.frag"));

    std::shared_ptr<Model> model = renderFactory->CreateModel(FileManager::GetModelPath("backpack/backpack.obj"));

    while (!window->ShouldClose()) {
        float currentFrame = window->GetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(*window);

        renderer->Clear();

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),
            (float)SCR_WIDTH / (float)SCR_HEIGHT,
            0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 modelMat = glm::mat4(1.0f);

        renderer->BeginFrame();
        renderer->SetViewProjection(view, projection);
        renderer->RenderModel(modelMat, *model, *shader);
        renderer->EndFrame();

        window->SwapBuffers();
        window->PollEvents();
    }
    window->Terminate();
    return 0;
}

void processInput(Window& window) {
    float cameraSpeed = 2.5f * deltaTime;
    if (window.IsKeyPressed(GLFW_KEY_ESCAPE))
        exit(0);
    if (window.IsKeyPressed(GLFW_KEY_W))
        camera.Position += cameraSpeed * camera.Front;
    if (window.IsKeyPressed(GLFW_KEY_S))
        camera.Position -= cameraSpeed * camera.Front;
    if (window.IsKeyPressed(GLFW_KEY_A))
        camera.Position -= glm::normalize(glm::cross(camera.Front, camera.Up)) * cameraSpeed;
    if (window.IsKeyPressed(GLFW_KEY_D))
        camera.Position += glm::normalize(glm::cross(camera.Front, camera.Up)) * cameraSpeed;

    double mouseX = window.GetMouseX();
    double mouseY = window.GetMouseY();

    updateMouse(mouseX, mouseY);

    camera.Position.y = 0.0f;
    window.ResetMouseDelta();
    window.ResetScrollOffsets();
}

void updateMouse(double xoffset, double yoffset) {
    float sensitivity = 0.13f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camera.Yaw += static_cast<float>(xoffset);
    camera.Pitch += static_cast<float>(yoffset);

    if (camera.Pitch > 89.0f)
        camera.Pitch = 89.0f;
    if (camera.Pitch < -89.0f)
        camera.Pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(camera.Yaw)) * cos(glm::radians(camera.Pitch));
    front.y = sin(glm::radians(camera.Pitch));
    front.z = sin(glm::radians(camera.Yaw)) * cos(glm::radians(camera.Pitch));
    camera.Front = glm::normalize(front);
    };