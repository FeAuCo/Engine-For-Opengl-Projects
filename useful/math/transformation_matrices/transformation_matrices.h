#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace transformations
{
  glm::mat4 model(const glm::vec3& translationVector);
  
  glm::mat4 view(const glm::vec3& translationVector);
  
  glm::mat4 projectionOrthographic(const float& leftSide, const float& rightSide, const float& bottomSide, const float& topSide, const float& nearPlane, const float& farPlane);

  glm::mat4 projectionPerspective(const float& fov, const float& aspectRatio, const float& nearPlane, const float& farPlane);
} 
