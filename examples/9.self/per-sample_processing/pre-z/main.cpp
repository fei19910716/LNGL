
/*
 * 1, PreZ(Zprepass)
 *      实际上就是一个深度计算, PreZ是用一个pass，只算深度
 *      具体用途：
 *          大规模草、透明排序会用到PreZ
 * 2, early-z 和 PreZ的区别
 *      early-z，自动的，对面数有要求，
 *      PreZ，当early-z失效的时候，或者需要深度图的时候，一种手动代替的方案
*/


/**
 * Sample: 使用pre-z进行不透明物体的渲染
*/

int main()
{

}