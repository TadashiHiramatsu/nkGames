using UnityEngine;
using UnityEditor;
using NUnit.Framework;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Text;

public class DataOutput : EditorWindow
{
    /// <summary>
    /// ウィンドウを開く関数
    /// </summary>
    [MenuItem("Window/DataOutput")]
    static void Open()
    {
        EditorWindow.GetWindow<DataOutput>("DataOutput");
    }

    /// <summary>
    /// マップデータの親オブジェクト
    /// </summary>
    GameObject MapData_;

    /// <summary>
    /// エネミースポーンデータの親オブジェクト
    /// </summary>
    GameObject EnemySpawnData_;

    /// <summary>
    /// GUIの描画
    /// </summary>
    private void OnGUI()
    {
        EditorGUILayout.BeginVertical(GUI.skin.box);
        {
            EditorGUILayout.LabelField("マップ配置出力");

            MapData_ = EditorGUILayout.ObjectField("MapData", MapData_, typeof(GameObject), true) as GameObject;

            if (GUILayout.Button("出力"))
            {
                MapDataOutput();
            }
        }
        EditorGUILayout.EndVertical();

        EditorGUILayout.BeginVertical(GUI.skin.box);
        {
            EditorGUILayout.LabelField("エネミースポナー配置出力");

            EnemySpawnData_ = EditorGUILayout.ObjectField("EnemySpawnData", EnemySpawnData_, typeof(GameObject), true) as GameObject;

            if (GUILayout.Button("出力"))
            {
                EnemySpawnData();
            }
        }
        EditorGUILayout.EndVertical();

    }

    void MapDataOutput()
    {
        if (!MapData_)
        {
            Debug.Log("親オブジェクトが設定されていません");
            return;
        }
        else
        {
            if (MapData_.transform.childCount == 0)
            {
                Debug.Log("マップオブジェクトが設定されていません");
                return;
            }

            string text = "モデルファイル名,位置X,位置Y,位置Z,回転X,回転Y,回転Z,回転W,拡大X,拡大Y,拡大Z\n";

            foreach (Transform children in MapData_.transform)
            {
                string write = "";
                string[] name = children.name.Split(" ("[0]);
                write += string.Format("{0}", name[0]);                   //モデルファイル名
                write += string.Format(",{0:f}", children.localPosition.x);     //位置X
                write += string.Format(",{0:f}", children.localPosition.y);     //位置Y
                write += string.Format(",{0:f}", children.localPosition.z);     //位置Z
                write += string.Format(",{0:f}", children.localRotation.x);     //回転X
                write += string.Format(",{0:f}", children.localRotation.y);     //回転Y
                write += string.Format(",{0:f}", children.localRotation.z);     //回転Z
                write += string.Format(",{0:f}", children.localRotation.w);     //回転W
                write += string.Format(",{0:f}", children.localScale.x * -1);        //拡大X
                write += string.Format(",{0:f}", children.localScale.y);        //拡大Y
                write += string.Format(",{0:f}", children.localScale.z);        //拡大Z
                write += "\n";

                text += write;
            }

            StreamWriter sw = new StreamWriter(@"C:\Github\nkGames\_HackandSlash\_HackandSlash\Asset\Data\MapData\" + MapData_.name + ".csv", false, Encoding.UTF8);
            sw.Write(text);
            sw.Close();

            Debug.Log("出力に成功しました");
        }
    }

    void EnemySpawnData()
    {
        if (!EnemySpawnData_)
        {
            Debug.Log("親オブジェクトが設定されていません");
            return;
        }
        else
        {
            if (EnemySpawnData_.transform.childCount == 0)
            {
                Debug.Log("スポーンオブジェクトが設定されていません");
                return;
            }

            string text = "位置X,位置Y,位置Z,出現範囲,出現最大数,発生間隔時間,敵レベル,敵種類\n";

            foreach (Transform children in EnemySpawnData_.transform)
            {

                EnemySpawn es = children.GetComponent<EnemySpawn>();

                string write = "";

                write += string.Format("{0}", children.position.x);     //位置X
                write += string.Format(",{0}", children.position.y);    //位置Y
                write += string.Format(",{0}", children.position.z);    //位置Z

                write += string.Format(",{0}", es.SpawnWideSize);       //出現範囲
                write += string.Format(",{0}", es.MaxSpawnNum);         //出現最大数
                write += string.Format(",{0}", es.SpawnTime);           //発生間隔時間

                write += string.Format(",{0}", es.EnemyLevel);          //敵のレベル
                write += string.Format(",{0}", (int)es.EnemyType);           //敵の種類

                write += "\n";

                text += write;
            }

            StreamWriter sw0 = new StreamWriter(@"C:\Github\nkGames\_HackandSlash\_HackandSlash\Asset\Data\EnemySpawnData\" + EnemySpawnData_.name + ".csv", false, Encoding.UTF8);
            sw0.Write(text);
            sw0.Close();

            Debug.Log("出力に成功しました");
        }
    }

}
