#include "fbo.h"


namespace fg
{
template<>
std::unique_ptr<FrameBuffer> realize(const FrameBuffer::Description& description)
{
  return std::make_unique<FrameBuffer>(description);
}
}