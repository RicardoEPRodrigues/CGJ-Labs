#version 330 core

in vec4 in_Position;
in vec4 in_Color;
out vec4 ex_Color;

uniform mat4 ModelMatrix;
uniform vec4 ModelColor = vec4(0.5, 0.5, 0.5, 1.0);

uniform SharedMatrices {
    mat4 ViewMatrix;
    mat4 ProjectionMatrix;
};

void main(void)
{
    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * in_Position;

    float zMixer = clamp((in_Position).z, 0.3, 1.0);
    float xMixer = clamp((in_Position).x, 0.3, 0.5);
    ex_Color = vec4(ModelColor.x * zMixer + xMixer,
                    ModelColor.y * zMixer + xMixer,
                    ModelColor.z * zMixer + xMixer,
                    ModelColor.w);
}