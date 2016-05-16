#include "Colors.glsl"

out vec4 oColor;
void main(){
    vec2 uv = gl_PointCoord.xy;
    oColor = vec4(uv.x,uv.y,0.0f,0.2f);
}
