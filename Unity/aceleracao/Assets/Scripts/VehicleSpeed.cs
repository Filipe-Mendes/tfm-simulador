using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class VehicleSpeed : MonoBehaviour
{
    [SerializeField] private TMPro.TMP_Text dashboard;
    [SerializeField] private GameObject vehicle;
    private VehicleController vehicleController;
    private Rigidbody rb;
    private float speed;


    void Start()
    {
        rb = vehicle.GetComponent<Rigidbody>();
        vehicleController = vehicle.GetComponent<VehicleController>();
    }

    void Update()
    {   
        string revText = vehicleController.IsReverse() ? " R" : "";
        speed = rb.velocity.magnitude * 3.6f;
        dashboard.text = ""+ (int)speed +" km/h" + revText;
    }
}
