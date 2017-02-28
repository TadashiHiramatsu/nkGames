using UnityEngine;
using UnityEditor;
using NUnit.Framework;
using System.Collections.Generic;


/// <summary>
/// 敵を発生させる機構のデータのエディタークラス.
/// </summary>
[CustomEditor(typeof(EnemySpawn))]
public class EnemtSpawnEditor : Editor
{

    /// <summary>
    /// GUI拡張関数
    /// </summary>
    public override void OnInspectorGUI()
    {
        //ターゲットを取得
        EnemySpawn es = target as EnemySpawn;

        EditorGUILayout.BeginVertical(GUI.skin.box);
        {
            EditorGUILayout.LabelField("敵スポナーの設定");

            //出現範囲モードの設定
            es.SpawnRange = (EnemySpawn.SpawnRangeCode)EditorGUILayout.EnumPopup("出現範囲モード", es.SpawnRange);

            //出現範囲サイズの設定
            if (es.SpawnRange == EnemySpawn.SpawnRangeCode.Wide)
            {
                es.SpawnWideSize = EditorGUILayout.Slider("出現範囲サイズ(半径)", es.SpawnWideSize, 1.0f, 100.0f);
                es.SetScale(new Vector3(es.SpawnWideSize * 2, 0.1f, es.SpawnWideSize * 2));
            }
            else
            {
                es.SpawnWideSize = 0;
                es.SetScale(new Vector3(1.0f, 0.1f, 1.0f));
            }

            //敵の出現最大数の設定
            es.MaxSpawnNum = EditorGUILayout.IntField("出現最大数", es.MaxSpawnNum);

            //発生間隔時間の設定
            es.SpawnTime = EditorGUILayout.FloatField("発生間隔時間", es.SpawnTime);

            //敵のレベル
            es.EnemyLevel = EditorGUILayout.IntSlider("出現レベル", es.EnemyLevel, 1, 100);

            //敵の種類
            es.EnemyType = (EnemySpawn.EnemyTypeCode)EditorGUILayout.EnumPopup("出現する敵の種類", es.EnemyType);

        }
        EditorGUILayout.EndVertical();

    }
}
