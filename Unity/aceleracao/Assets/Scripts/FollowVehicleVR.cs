using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FollowVehicleVR : MonoBehaviour
{
    // Start is called before the first frame update
public GameObject vehicle;

    private Vector3 offset = new Vector3(-0.15f,0,0.15f);

    void Start()
    {

    }

    void LateUpdate()
    {
        transform.position = vehicle.transform.position + offset;
        transform.rotation = vehicle.transform.rotation;
    }
}
