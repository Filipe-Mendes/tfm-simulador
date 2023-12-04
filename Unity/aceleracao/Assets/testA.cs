using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class testA : MonoBehaviour
{
    [SerializeField] private GameObject GOB;
    private testB tb;

    void Start(){
        tb = GOB.GetComponent<testB>();
        tb.int2 = 2;
        GOB.SetActive(true);
    }

    void Update(){
        
    }
}
