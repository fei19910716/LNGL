
For a PBR lighting model to be considered physically based, it has to satisfy the following 3 conditions:

Be based on the microfacet surface model.
Be energy conserving.
Use a physically based BRDF.


[Radiant flux] = Φ, 辐射功率， 一般用光源RGB颜色表示。

[Solid angle] = sr, 立体角

[radiance] = Φ / (sr ⋅ m2), 单位立体角，单位面积接收到的辐射功率。
    the radiance is used for two cases:
    1，angle-dependent diffuse reflection (BRDF)
    2，emission from light sources

[irradiance] = Φ / m2, 单位面积，所有立体角上接收到的辐射功率。
    irradiance refers to incoming power

[Radiant intensity] = Φ / sr， 光源在某个立体角方向的辐射功率。