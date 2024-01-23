using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class VehicleSpeed : MonoBehaviour
{
    [SerializeField] private TMPro.TMP_Text dashboard;
    [SerializeField] private GameObject vehicle;
    private VehicleController vehicleController;
    private Rigidbody rb;

    void Start()
    {
        rb = vehicle.GetComponent<Rigidbody>();
        vehicleController = vehicle.GetComponent<VehicleController>();
    }

    void Update()
    {   
        string revText = vehicleController.IsReverse() ? " R" : "";
        dashboard.text = ""+(int)rb.velocity.magnitude+" km/h" + revText;
    }
}
