/*
 * File Parallelogram.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_PARALLELOGRAM_H
#define THREEENGINE_PARALLELOGRAM_H

#include <GL/glew.h>
#include "Engine/IDrawable.h"
#include "../Shader/ShaderProgram.h"
#include "../OpenGLUtils.h"

namespace ThreeEngine {

    class Parallelogram : public IDrawable {

        public:

            std::shared_ptr<ShaderProgram> shaderProgram;

            Parallelogram();

            explicit Parallelogram(GLfloat RGBA[6][4]);

            ~Parallelogram() override;

            void Init() override;

            void Draw() override;

        private:

            GLuint vaoId, vboId[1];

            Vertex Vertices[6];
    };

} /* namespace Divisaction */

#endif //THREEENGINE_PARALLELOGRAM_H
