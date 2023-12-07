using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FollowVehicle : MonoBehaviour
{
    [SerializeField] private GameObject vehicle;

    [SerializeField] private Vector3 offset = new Vector3(0,10,-15);

    void Start()
    {

    }

    void LateUpdate()
    {
        transform.position = vehicle.transform.position + offset;
        transform.rotation = vehicle.transform.rotation;

    }
}
