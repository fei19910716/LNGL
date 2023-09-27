

int main()
{
    /**
     * https://bgolus.medium.com/anti-aliased-alpha-test-the-esoteric-alpha-to-coverage-8b177335ae4f
    */
   
    /**
     * 
     *  alpha test会造成锯齿的存在，这种锯齿msaa没有用，因为在shader中就会被discard;
        alpha blend一定程度上可以解决这种锯齿，但是由于blend会关闭深度写入，导致渲染草，树等网络交叉的物体时效果出错，此时可以用OIT解决。

        A2C是一种multisampling技术, 其使用coverage mask代替alpha blend，因为不使用alpha blend, 因此可以不用排序半透明物体,
        即当msaa开启时，A2C可以实现OIT（因为不使用alpha blend），A2C常用于渲染茂密的树叶或草地。

        激活条件：
            A2C必须要结合MSAA使用，因此如果使用deferred shading, 则msaa被抑制， A2C也就没法使用了。
            游戏一般会倾向于在后处理阶段做抗锯齿，如FXAA, 则msaa被抑制，A2C也就没法使用了。

        VR has lead to the resurgence of forward rendering and of MSAA. This means A2C has become a useful tool again, especially for VR.

        Anti-aliased alpha test is one of the most basic use cases for Alpha to Coverage.

        Alpha to Coverage maps the alpha output from a pixel shader to the coverage mask of MSAA

        Alpha to Coverage let’s the pixel shader’s output alpha change the fraction of coverage samples rendered to.


        个人理解：
        MSAA开启后pixel最后的颜色是所有samples平均之后的结果；
        A2C开启时，会将fragment shader执行后该pixel的alpha转换为coverage mask（具体转换成多少implementation决定）；
        coverage mask 是bit filed，用于确定哪些sample会被用于计算最终的pixel color.
    */
}