/*
 * File Tangram.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include <cmath>
#include "LightScene.h"

#include "../../Engine/Shapes/MeshLoader.h"
#include "../../Engine/Shader/TextureLoader.h"
#include "../../Engine/Camera/Perspective.h"
#include "../../Engine/Utilities/Managers.h"
#include "../../Engine/Utilities/Simulation.h"
#include "../../Engine/Actors/SkySphere.h"

#define VERTICES 0
#define COLORS 1

using json = nlohmann::json;

using namespace std;

namespace ThreeEngine {

    class CycleNumber : public IUpdatable {
        public:
            float start{}, step{}, count{}, max{};

            void Update(milliseconds delta) override {
                count += step / delta;
//                if (count > max) {
//                    count = start;
//                }
                if (count > max || count < start) {
                    step = -step;
                }
            }
    };

    class MetallicRoughnessControl : public IUpdatable {
        public:
            float metallic, roughness, step;

            void Update(milliseconds delta) override {
                if (Engine::Instance()->input['q']) {
                    metallic -= step / delta;
                    if (metallic < 0) {
                        metallic = 0;
                    }
                }
                if (Engine::Instance()->input['w']) {
                    metallic += step / delta;
                    if (metallic > 1) {
                        metallic = 1;
                    }
                }
                if (Engine::Instance()->input['e']) {
                    roughness -= step / delta;
                    if (roughness < 0) {
                        roughness = 0;
                    }
                }
                if (Engine::Instance()->input['r']) {
                    roughness += step / delta;
                    if (roughness > 1) {
                        roughness = 1;
                    }
                }
            }
    };


    LightScene::LightScene()
            : Engine(), sceneGraph(new SceneGraph()), controller() { }

    LightScene::~LightScene() = default;

    void LightScene::OnInit() {
        setupShaders();
        setupMeshes();
        setupTextures();
        scene();
    }

    void LightScene::setupShaders() {
        auto defaultProgram = std::make_shared<ShaderProgram>(
                "shaders/Default/program.json");
        defaultProgram->Init();
        ShaderProgramManager::instance()->Add("default", defaultProgram);
        auto cubemapProgram = std::make_shared<ShaderProgram>(
                "shaders/BRDF/program.json");
        cubemapProgram->Init();
        ShaderProgramManager::instance()->Add("cubemap", cubemapProgram);
        auto skysphere = std::make_shared<ShaderProgram>(
                "shaders/SkySphere/program.json");
        skysphere->Init();
        ShaderProgramManager::instance()->Add("skysphere", skysphere);
    }

    void LightScene::setupMeshes() {
        MeshManager::instance()->Add("Horse",
                                     MeshLoader::instance()->LoadFileOBJ(
                                             "assets/Horse-vtn.obj"));
        MeshManager::instance()->Add("Cube",
                                     MeshLoader::instance()->LoadFileOBJ(
                                             "assets/Cube-vtn.obj"));
        MeshManager::instance()->Add("Sphere",
                                     MeshLoader::instance()->LoadFileOBJ(
                                             "assets/Sphere.obj"));
    }

    void LightScene::setupTextures() {
        TextureManager::instance()->Add("Stone",
                                        TextureLoader::instance()->LoadTexture(
                                                "assets/Stone.jpg"));
        TextureManager::instance()->Add("FortPoint",
                                        TextureLoader::instance()->LoadCubemap(
                                                "assets/FortPoint/negz.jpg",
                                                "assets/FortPoint/posz.jpg",
                                                "assets/FortPoint/posy.jpg",
                                                "assets/FortPoint/negy.jpg",
                                                "assets/FortPoint/negx.jpg",
                                                "assets/FortPoint/posx.jpg"
                                        ));
        TextureManager::instance()->Add("GGB3",
                                        TextureLoader::instance()->LoadCubemap(
                                                "assets/GoldenGateBridge3/negz.jpg",
                                                "assets/GoldenGateBridge3/posz.jpg",
                                                "assets/GoldenGateBridge3/posy.jpg",
                                                "assets/GoldenGateBridge3/negy.jpg",
                                                "assets/GoldenGateBridge3/negx.jpg",
                                                "assets/GoldenGateBridge3/posx.jpg"
                                        ));
    }

    void LightScene::scene() {
        actors.push_back(reinterpret_cast<IDrawable*&&>(sceneGraph));

        { // Camera handling
            number width = config["window"]["x"];
            number height = config["window"]["y"];
            number aspect = width / height;
            Camera* camera = new Camera(
                    static_cast<GLuint>(
                            ShaderProgramManager::instance()->Get(
                                    "default")->GetUniformBlockBidingId(
                                    "SharedMatrices")),
                    new Perspective(30, aspect, 1, 1000),
                    new Matrix(Matrix::TranslationMatrix(Vector(0, 0, -100)))
//                    new LookAt({5, 0.5f, 0}, {0, 0.5f, 0}, {0, 1, 0})
            );
            sceneGraph->SetCamera(camera);
            controller.camera = camera;
        }

        auto root = new Actor();
        root->setShaderProgram(
                ShaderProgramManager::instance()->Get("default"));
        sceneGraph->SetRoot(root);

//        {
//            auto horse = new Actor();
//            horse->mesh = MeshManager::instance()->Get("Horse");
//            horse->textures.push_back(TextureManager::instance()->Get("Stone"));
//            auto&& hTransform = horse->transform;
//            hTransform.scale = Vector(0.1f);
//            hTransform.translation.Y = -10;
//            horse->SetParent(root);
//        }
//        {
//            auto cube = new Actor();
//            cube->mesh = MeshManager::instance()->Get("Cube");
//            cube->textures.push_back(TextureManager::instance()->Get("Stone"));
//            auto&& hTransform = cube->transform;
//            hTransform.scale = Vector(10);
//            hTransform.translation = {-10, -10, 10};
//            cube->SetParent(root);
//        }
//        {
//            auto horse = new Actor();
//            horse->setShaderProgram(
//                    ShaderProgramManager::instance()->Get("cubemap"));
//            horse->mesh = MeshManager::instance()->Get("Horse");
//            horse->textures.push_back(
//                    TextureManager::instance()->Get("GGB3"));
//            auto&& hTransform = horse->transform;
//            hTransform.scale = Vector(0.1f);
//            hTransform.translation.Y = -10;
//            horse->SetParent(root);
//        }
        {
            auto skySphere = new SkySphere();
            skySphere->setShaderProgram(
                    ShaderProgramManager::instance()->Get("skysphere"));
            skySphere->mesh = MeshManager::instance()->Get("Sphere");
            skySphere->textures.push_back(
                    TextureManager::instance()->Get("GGB3"));
            auto&& hTransform = skySphere->transform;
            hTransform.scale = Vector(100);
            skySphere->SetParent(root);
        }
        {
            auto object = new Actor();
            auto program = ShaderProgramManager::instance()->Get("cubemap");
            object->setShaderProgram(program);
            object->mesh = MeshManager::instance()->Get("Sphere");
            object->textures.push_back(
                    TextureManager::instance()->Get("GGB3"));
            auto&& hTransform = object->transform;
            hTransform.scale = Vector(10);
            object->SetParent(root);

            auto shaderController = new MetallicRoughnessControl();
            shaderController->step = 0.1;
            Simulation::instance()->Add(shaderController);

//            auto cycleCount = new CycleNumber();
//            cycleCount->step = 0.1;
//            cycleCount->start = 0;
//            cycleCount->max = 1;
//            Simulation::instance()->Add(cycleCount);

            object->preDraw = [program, shaderController]() {
//                glUniform1f(program->GetUniformLocationId("Roughness"),
//                            cycleCount->count);
//                glUniform1f(program->GetUniformLocationId("Metallic"),
//                            cycleCount->count);
                glUniform1f(program->GetUniformLocationId("Roughness"),
                            shaderController->roughness);
                glUniform1f(program->GetUniformLocationId("Metallic"),
                            shaderController->metallic);
                glUniform4f(program->GetUniformLocationId("BaseColor"),
                            0.6f, 0.1f, 0.1f, 1);
            };
        }
        {
            auto object = new Actor();
            auto program = ShaderProgramManager::instance()->Get("cubemap");
            object->setShaderProgram(program);
            object->mesh = MeshManager::instance()->Get("Sphere");
            object->textures.push_back(
                    TextureManager::instance()->Get("GGB3"));
            auto&& hTransform = object->transform;
            hTransform.scale = Vector(10);
            hTransform.translation = Vector(-20, 0, 0);
            object->SetParent(root);

            object->preDraw = [program]() {
                glUniform1f(program->GetUniformLocationId("Roughness"), 0);
                glUniform1f(program->GetUniformLocationId("Metallic"), 1);
                glUniform4f(program->GetUniformLocationId("BaseColor"),
                            1.000f, 0.766f, 0.336f, 1);
            };
        }

        // Initializes all the actors in it.
        sceneGraph->Init();
    }

    void LightScene::OnReshape(int, int) {
//        number aspect = (number) w / (number) h,
//                angle = Maths::ToRadians(30.0f / 2.0f),
//                d = 1.0f / tanf(angle);
//        camera->projection.M[0][0] = d / aspect;
    }

    void LightScene::PreDraw() {
        controller.Update();
    }

    void LightScene::Update() {
        if (input.Click(27)) { // ESC
            Exit();
        }
        Simulation::instance()->Update();
    }

    void LightScene::OnCleanup() {
        ShaderProgramManager::instance()->cleanup();
        MeshManager::instance()->cleanup();
        Simulation::instance()->cleanup();
    }

} /* namespace Divisaction */