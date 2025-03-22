#ifndef RENDERER_H
#define RENDERER_H

#include "glm/glm.hpp"
#include "glad/glad.h"
#include "shader.h"
#include "player.h"
#include "window.h"

class Renderer {
public:
  Renderer() = default;

  bool init();

  void draw(Player& player, Window& window, std::vector<glm::vec2> drawableChunks);

private:
  Shader shader;
  unsigned int VBO{}, VAO{};
};



#endif //RENDERER_H
