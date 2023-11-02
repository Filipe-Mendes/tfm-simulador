using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SideCameraScript : MonoBehaviour
{
    // Start is called before the first frame update
public GameObject vehicle;
    //private Vector3 offset = new Vector3(0,10,-15);

    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void LateUpdate()
    {
        transform.position = vehicle.transform.position + new Vector3(-5.5f,1,0);
    }
}
