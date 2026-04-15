#version 460 core

// --- Inputs (From the Vertex Shader) ---
// The name and type MUST match the 'out' variable from the vertex shader exactly.
in vec3 triColor;

// --- Outputs (To the Screen) ---
out vec4 FragColor;

void main()
{
    // FragColor is the final pixel color.
    // It requires a vec4 (R, G, B, A). We set Alpha (A) to 1.0 for fully opaque.
    FragColor = vec4(triColor, 1.0);
}