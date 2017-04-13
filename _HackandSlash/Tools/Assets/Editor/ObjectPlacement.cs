using UnityEngine;
using UnityEditor;

[InitializeOnLoad]
public class ObjectPlacement
{

    static ObjectPlacement()
    {
        //シーンビューにGUIを追加.
        //SceneView.onSceneGUIDelegate += OnSceneGUI;
    }

    /// <summary>
    /// シーンビューのGUI.
    /// </summary>
    /// <param name="sceneview"></param>
    static void OnSceneGUI(SceneView sceneview)
    {
        Rect Rect_ = new Rect(8, 24, 100, 0);

        GUILayout.Window(1, Rect_, Func, "オブジェクト配置");
    }

    static void Func(int id)
    {
        if (GUILayout.Button("ボタン1"))
        {
        }
    }

    /// <summary>
    /// 配置する.
    /// </summary>
    static void Placement()
    {
        //シーンビューのカメラ?
        Camera scenecamera = SceneView.currentDrawingSceneView.camera;

        RaycastHit hit;
        Ray ray = scenecamera.ScreenPointToRay(Input.mousePosition);

        if (Physics.Raycast(ray, out hit))
        {
            Transform hitobject = hit.transform;

            if(hitobject.tag != "Ground")
            {
                return;
            }

            Debug.Log(hitobject.position.ToString());

        }

    }

}
