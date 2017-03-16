/***
* s—ñƒNƒ‰ƒX‚ÌÀ‘•.
*/
#include"nkEngine/nkstdafx.h"
#include"nkMatrix.h"

namespace nkEngine
{
	const Matrix Matrix::Identity = {
		1.0f, 0.0f, 0.0f, 0.0f ,
		0.0f, 1.0f, 0.0f, 0.0f ,
		0.0f, 0.0f, 1.0f, 0.0f ,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}