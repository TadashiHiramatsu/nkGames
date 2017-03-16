/**
 * @file	nkOriginalDefine.h
 *
 * 定義ファイル.
 */
#pragma once

namespace nkEngine
{

/**
 * A macro that defines cast.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/09
 */
#define r_cast reinterpret_cast
/**
 * A macro that defines cast.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/09
 */
#define	s_cast static_cast
/**
 * A macro that defines cast.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/09
 */
#define	c_cast const_cast

/**
 * A macro that defines safe delete.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/09
 *
 * @param p The void to process.
 */
#define SAFE_DELETE(p) { if (p) { delete (p);     (p) = nullptr; } }
/**
 * A macro that defines safe delete array.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/09
 *
 * @param p The void to process.
 */
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p);   (p) = nullptr; } }
/**
 * A macro that defines safe release.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/09
 *
 * @param p The void to process.
 */
#define SAFE_RELEASE(p) { if (p) { (p)->Release(); (p) = nullptr; } }

	
/**
* Windows ヘッダーから使用されていない部分を除外します.
*
* @author HiramatsuTadashi
* @date 2017/01/09
*/
#define WIN32_LEAN_AND_MEAN

/**
 * π.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/09
 */
#define PI 3.14159265358979323846f

	/** 1フレームの経過時間(単位:秒)。固定FPS. */
	static const float GAME_DELTA_TIME = 1.0f / 60.0f;

}// namespace nkEngine