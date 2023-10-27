/**
 * Frame extrapolation is the process of producing a new, future frame
    based on the contents of two previously rendered frames. It may be
    used to produce high frame rate display updates without incurring the
    full cost of traditional rendering at the higher framerate.
*/


/**
 * @brief produce an extrapolated frame based on the contents of two previous frames
 * 
 * The three textures provided must have the same
    dimensions and format. While <src1>, <src2> and <output> can
    have multiple levels the implementation only reads from or writes
    to the base level.
*/
void ExtrapolateTex2DQCOM(uint src1,uint src2, uint output, float scaleFactor);
