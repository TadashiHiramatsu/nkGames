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
    public SpawnRangeCode SpawnRange;

    /// <summary>
    /// 出現範囲のサイズ.
    /// </summary>
    public float SpawnWideSize;

    /// <summary>
    /// 敵の最大出現数.
    /// </summary>
    public int MaxSpawnNum;

    /// <summary>
    /// 発生間隔時間(秒).
    /// </summary>
    public float SpawnTime;

    /// <summary>
    /// 敵のレベル.
    /// </summary>
    public int EnemyLevel;

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
    public EnemyTypeCode EnemyType;

    /// <summary>
    /// スケールの設定
    /// </summary>
    /// <param name="scale"></param>
    public void SetScale(Vector3 scale)
    {
        transform.localScale = scale;
    }

}

