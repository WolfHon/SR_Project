/*!
 * \file Engine_Enum.h
 * \date 2017/07/13 21:10
 *
 * \author Han
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef __Engine_Enum_h__
#define __Engine_Enum_h__

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
	enum TILETYPE {TILE_PATH, TILE_UNBROKEN, TILE_BROKEN};
	enum TILETEXTURE {TILE_IMAGE0};
}

#endif // __Engine_Enum_h__