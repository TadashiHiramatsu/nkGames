using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

/// <summary>
/// 敵を発生させる機構のデータ.
/// </summary>
public class EnemySpawn : MonoBehaviour
{

    /// <summary>
    /// 出現範囲モードコード.
    /// </summary>
    public enum SpawnRangeCode
    {
        /// <summary>
        /// 一点.
        /// </summary>
        Point,
        /// <summary>
        /// 幅広.
        /// </summary>
        Wide,
    };

    /// <summary>
    /// 出現範囲モード.
    /// </summary>
    public SpawnRangeCode SpawnRange = SpawnRangeCode.Point;

    /// <summary>
    /// 出現範囲のサイズ.
    /// </summary>
    public float SpawnWideSize = 0;

    /// <summary>
    /// 敵の最大出現数.
    /// </summary>
    public int MaxSpawnNum = 0;

    /// <summary>
    /// 発生間隔時間(秒).
    /// </summary>
    public float SpawnTime = 0.0f;

    /// <summary>
    /// 敵のレベル.
    /// </summary>
    public int EnemyLevel = 1;

    /// <summary>
    /// 敵の種類コード.
    /// </summary>
    public enum EnemyTypeCode
    {
        Enemy_01 = 0,
    }

    /// <summary>
    /// 敵の種類.
    /// </summary>
    public EnemyTypeCode EnemyType = EnemyTypeCode.Enemy_01;

    /// <summary>
    /// スケールの設定
    /// </summary>
    /// <param name="scale"></param>
    public void SetScale(Vector3 scale)
    {
        transform.localScale = scale;
    }

}
