/*
 * File CameraController.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_CAMERACONTROLLER_H
#define THREEENGINE_CAMERACONTROLLER_H

#include "../../Engine/Engine.h"

namespace ThreeEngine {

    class FreeCameraController {
        private:
            Engine* engine;

            bool inPerspective;

            Vector2 previousMouseLocation, yawPitch;

            Matrix translation, rotation;

        public:

            FreeCameraController();

            virtual ~FreeCameraController();

            void Update();
    };

} /* namespace Divisaction */

#endif //THREEENGINE_CAMERACONTROLLER_H
