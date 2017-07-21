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
	enum LAYERID {LAYER_ENVIROMENT, LAYER_GAMELOGIC, LAYER_UI};
	enum ANGLE {ANGLE_X, ANGLE_Y, ANGLE_Z, ANGLE_END,};
	enum TEXTURETYPE { TEXTURE_NORMAL, TEXTURE_CUBE };
	enum RESOURCETYPE {RESOURCE_STATIC, RESOURCE_DYNAMIC, RESOURCE_END};
	enum OBJECT_RESULT	{ OR_OK = 0, OR_DELETE,	OR_EXIT	};
	enum BUFFERTYPE
	{
		BUFFER_RCTEX,
		BUFFER_SLOPETEX,
		BUFFER_CUBETEX,
		BUFFER_CUBECOLOR,
		MODEL_PLAYER
	};

	enum COLLISIONID {COLLISON_TERRAIN, COLLISON_OBB, COLLISON_END};
	enum TILETYPE {TILE_UNBROKEN, TILE_BROKEN , TILE_START};
	enum TILETEXTURE {TILE_IMAGE0, TILE_IMAGE1, TILE_IMAGE2, TILE_IMAGE3 , TILE_IMAGE4 ,TILE_IMAGE5  , TILE_IMAGE6 ,TILE_IMAGE7 ,TILE_IMAGE8};
	enum TILESHAPE {TILE_CUBE, TILE_SLOPE};
	enum ITEMOPTION {ITEM_POWER, ITEM_SPEED , ITEM_ADDBOMB , ITEM_ELSE};
}

#endif // __Engine_Enum_h__