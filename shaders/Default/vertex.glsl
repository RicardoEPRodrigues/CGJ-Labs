#version 330 core

in vec4 in_Position;
in vec4 in_Color;
in vec2 in_TexCoord;
in vec3 in_Normal;
out vec4 ex_Color;
out vec2 ex_TexCoord;
out vec3 ex_Normal;

uniform mat4 ModelMatrix;

uniform SharedMatrices {
    mat4 ViewMatrix;
    mat4 ProjectionMatrix;
};

void main(void)
{
    vec4 ModelColor = vec4(0.9, 0.5, 0.5, 1.0);

    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * in_Position;

    mat3 normalMatrix = transpose(inverse(mat3(ViewMatrix) * mat3(ModelMatrix)));
    ex_Normal = normalMatrix * in_Normal;

//    float zMixer = clamp((ModelMatrix * in_Position).z, 0.3, 1.0);
//    float xMixer = clamp((ModelMatrix * in_Position).x, 0.3, 0.5);
//    ex_Color = vec4(ModelColor.x * zMixer + xMixer,
//                    ModelColor.y * zMixer + xMixer,
//                    ModelColor.z * zMixer + xMixer,
//                    ModelColor.w);
    ex_Color = ModelColor;
    ex_TexCoord = in_TexCoord;
}