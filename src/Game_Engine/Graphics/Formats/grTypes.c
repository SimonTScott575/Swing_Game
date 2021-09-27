#include <Game_Engine/Graphics/Formats/grTypes.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct grTypes grTypes;

void grInit_Types() {

  if (sizeof(unsigned int) == 2) {
    grTypes._uint = GL_UNSIGNED_SHORT;
  } else if (sizeof(unsigned int) == 4) {
    grTypes._uint = GL_UNSIGNED_INT;
  }
  grTypes._uint8_t = GL_UNSIGNED_BYTE;
  grTypes._uint16_t = GL_UNSIGNED_SHORT;
  grTypes._uint32_t = GL_UNSIGNED_INT;
  grTypes._uint64_t *= -1;

  if (sizeof(int) == 2) { //? compile time checks ?
    grTypes._int = GL_SHORT;
  } else if (sizeof(int) == 4) {
    grTypes._int = GL_INT;
  }
  grTypes._int8_t = GL_BYTE;
  grTypes._int16_t = GL_SHORT;
  grTypes._int32_t = GL_INT;
  grTypes._int64_t *= -1;

  grTypes._float = GL_FLOAT;
  grTypes._double = GL_DOUBLE;

  grTypes._bool = GL_UNSIGNED_BYTE;

  if (sizeof(size_t) == 4) {
    grTypes._size_t = GL_UNSIGNED_INT;
  }
  if (sizeof(size_t) == 8) {
    grTypes._size_t *= -1;
  }

  grTypes._dType = GL_INT;
  // grTypes._dPtr = grTypes._size_t;

}
