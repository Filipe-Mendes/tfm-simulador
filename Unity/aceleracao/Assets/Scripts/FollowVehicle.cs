using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FollowVehicle : MonoBehaviour
{
    // Start is called before the first frame update
public GameObject vehicle;

    private Vector3 offset = new Vector3(0,10,-15);

    void Start()
    {

    }

    void LateUpdate()
    {
        transform.position = vehicle.transform.position + offset;
    }
}
