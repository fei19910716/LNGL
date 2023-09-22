
According to the OpenGL GL_ARB_multisample specification, "multisampling" refers to a specific optimization of supersampling.

msaa是fsaa的一种优化

The specification dictates that the renderer evaluate the fragment program once per pixel, and only "truly" supersample the depth and stencil values.

msaa每个pixel只会执行一次fragment shader，但是depth/stencil是FSAA的（所有atanchment的分辨率还是增加的）

In supersample anti-aliasing, multiple locations are sampled within every pixel, and each of those samples[3] is fully rendered and combined with the others to produce the pixel that is ultimately displayed

FSAA中所有samples都会进行渲染，最后综合在一起决定最终的pixel颜色


In multisample anti-aliasing, if any of the multi sample locations in a pixel is covered by the triangle being rendered, a shading computation must be performed for that triangle. However this calculation only needs to be performed once for the whole pixel regardless of how many sample positions are covered

对于msaa，只要一个pixel的任意sample被triangle覆盖，则需要执行fragment shader一次，且仅需一次。

the result of the shading calculation is simply applied to all of the relevant multi sample locations.

所有被覆盖的samples都会使用该相同的输出值