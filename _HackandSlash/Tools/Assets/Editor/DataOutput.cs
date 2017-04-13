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

    /// <summary>
    /// マップ情報をファイルに書き出し.
    /// </summary>
    void MapDataOutput()
    {
        if (!MapData_)
        {
            Debug.Log("親オブジェクトが設定されていませんyo!!!");
            return;
        }

        //マップ配置のリストを作成.
        List<GameObject> MapList = CreateMapList();

        if (MapList.Count == 0)
        {
            Debug.Log("マップオブジェクトが登録されていませんyo!!!");
            return;
        }

        string text = "モデルファイル名,位置X,位置Y,位置Z,回転X,回転Y,回転Z,回転W,拡大X,拡大Y,拡大Z\n";

        foreach (GameObject Object in MapList)
        {

            //オブジェクトのトランスフォーム.
            Transform MapTransform = Object.transform;

            string write = "";

            //オブジェクトの名前だけ取得.
            string[] name = MapTransform.name.Split(" ("[0]);

            write += string.Format("{0}", name[0]);                             //モデルファイル名
            write += string.Format(",{0:f}", MapTransform.position.x);     //位置X
            write += string.Format(",{0:f}", MapTransform.position.y);     //位置Y
            write += string.Format(",{0:f}", MapTransform.position.z);     //位置Z
            write += string.Format(",{0:f}", MapTransform.rotation.x);     //回転X
            write += string.Format(",{0:f}", MapTransform.rotation.y);     //回転Y
            write += string.Format(",{0:f}", MapTransform.rotation.z);     //回転Z
            write += string.Format(",{0:f}", MapTransform.rotation.w);     //回転W
            write += string.Format(",{0:f}", MapTransform.localScale.x * -1);   //拡大X
            write += string.Format(",{0:f}", MapTransform.localScale.y);        //拡大Y
            write += string.Format(",{0:f}", MapTransform.localScale.z);        //拡大Z
            write += "\n";

            text += write;
        }

        StreamWriter sw = new StreamWriter(@"C:\Github\nkGames\_HackandSlash\_HackandSlash\Asset\Data\MapData\" + MapData_.name + ".csv", false, Encoding.UTF8);
        sw.Write(text);
        sw.Close();

        Debug.Log("出力に成功しましたyo!!!");
    }
    
    /// <summary>
    /// 引数のマップデータの親から書き出すリストを作成する.
    /// </summary>
    /// <returns></returns>
    List<GameObject> CreateMapList()
    {
        //リスト.
        List<GameObject> MapList = new List<GameObject>();

        //子供を見る.
        GetChildren(MapData_,ref MapList);

        //返す.
        return MapList;
    }

    /// <summary>
    /// 子供をリストに追加する.
    /// </summary>
    /// <param name="parent"></param>
    /// <param name="maplist"></param>
    void GetChildren(GameObject parent,ref List<GameObject> maplist)
    {

        //トランスフォームを取得.
        Transform pt = parent.transform;

        if (pt.childCount == 0)
        {
            //子供がいないので抜ける.
            return;
        }

        //子供をすべて見る.
        foreach(Transform child in pt)
        {
            string[] name = child.name.Split(" ("[0]);

            if (name[0] != "GameObject")
            {
                //リストに登録.
                maplist.Add(child.gameObject);
            }
            
            //子供を見る.
            GetChildren(child.gameObject,ref maplist);
        }

    }



    /// <summary>
    /// 敵のスポーン地点をファイルに書き出し.
    /// </summary>
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
