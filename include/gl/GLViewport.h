/**
 * @file GLViewport.h
 * @brief Declaration of the GLViewport class for viewport types.
 */

#ifndef _3dmodeler_glviewport_h
#define _3dmodeler_glviewport_h

namespace _3dmodeler
{
/**
 * @class Viewport
 * @brief An enum class for viewport types
 * 
 * Values: NONE, TOP, FRONT, SIDE
 */
enum class GLViewport {
    NONE, // None
    SIDE, // Side viewport
    TOP,  // Top viewport
    FRONT // Front viewport
};
} // end namepsace _3dmodeler

#endif // _3dmodeler_glviewport_h