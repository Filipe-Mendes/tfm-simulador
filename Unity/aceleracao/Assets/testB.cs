using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class testB : MonoBehaviour
{
    [SerializeField] public int int1 = 1;
    [SerializeField] public int int2 = 200;

    void Start()
    {
        Debug.Log("S i1: " + int1 + " || i2: " + int2);
    }

    void Update()
    {
        Debug.Log("U i1: " + int1 + " || i2: " + int2);
    }
}
