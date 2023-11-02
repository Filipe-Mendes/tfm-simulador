using UnityEngine;
using UnityEditor;
using UnityEngine.InputSystem;


#if UNITY_EDITOR
[InitializeOnLoad]
#endif
public class Shift : InputProcessor<float>
{
    #if UNITY_EDITOR
    static Shift()
    {
        Initialize();
    }
    #endif

    [RuntimeInitializeOnLoadMethod(RuntimeInitializeLoadType.BeforeSceneLoad)]
    static void Initialize()
    {
        InputSystem.RegisterProcessor<Shift>();
    }

    [Tooltip("Number to add to incoming values.")]
    public float valueShift = 0;

    public override float Process(float value, InputControl control)
    {
        return value + valueShift;
    }
}