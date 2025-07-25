#include "transformation_matrices.h"

glm::mat4 transformations::model(const glm::vec3& translationVector){
    return glm::translate(glm::mat4(1.0f), translationVector);
}

glm::mat4 transformations::view(const glm::vec3& translationVector){
    return glm::translate(glm::mat4(1.0f), translationVector);
}

glm::mat4 transformations::projectionOrthographic(const float& leftSide, const float& rightSide, const float& bottomSide, const float& topSide, const float& nearPlane, const float& farPlane){
    return glm::ortho(leftSide, rightSide, bottomSide, topSide, nearPlane, farPlane);
}

glm::mat4 transformations::projectionPerspective(const float& fov, const float& aspectRatio, const float& nearPlane, const float& farPlane){
    return glm::perspective(fov, aspectRatio, nearPlane, farPlane);
}
