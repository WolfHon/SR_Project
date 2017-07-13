/*!
 * \file Engine_Enum.h
 * \date 2015/04/05 8:42
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/
#ifndef Engine_Enum_h__
#define Engine_Enum_h__

namespace Engine
{
	enum ANGLE {ANGLE_X, ANGLE_Y, ANGLE_Z, ANGLE_END,};
	enum TEXTURETYPE { TEXTURE_NORMAL, TEXTURE_CUBE };
	enum RESOURCETYPE {RESOURCE_STATIC, RESOURCE_DYNAMIC, RESOURCE_END};
	enum BUFFERTYPE
	{
		BUFFER_TRICOL,
		BUFFER_RCCOL,
		BUFFER_RCTEX,
		BUFFER_TERRAINTEX,
		BUFFER_CUBETEX,
	};
	enum COLLISIONID {COLLISON_TERRAIN, COLLISON_MOUSE, COLLISON_AABB};
}

#endif // Engine_Enum_h__