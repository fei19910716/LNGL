#version 440 core

layout(local_size_x = 2) in;
layout(std430, binding = 0) buffer writeonly Result{
  float out_picture[];
};
layout(std430, binding = 1) buffer readonly In_p1{
  float in_p1[];
};


void main() {

  out_picture[gl_GlobalInvocationID.x] = out_picture[gl_GlobalInvocationID.x] + in_p1[gl_GlobalInvocationID.x];

}