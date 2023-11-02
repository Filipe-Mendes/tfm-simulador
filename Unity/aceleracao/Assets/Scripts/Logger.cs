using System.Collections;
using System;
using System.IO;
using System.Collections.Generic;
using UnityEngine;

public class Logger : MonoBehaviour
{

    // Vehicle
    [SerializeField] private GameObject vehicle;
    private Rigidbody rb;

    // Movement measurements
    private Vector3 jerk;
    private Vector3 acceleration;
    private Vector3 lastAcceleration;
    private Vector3 currentVelocity;
    private Vector3 lastVelocity;
    private Vector3 lastPosition;
    private Quaternion rotation;

    private float[] pointsToSend;


    // Logging
    private List<Vector3> positionArr = new List<Vector3>();
    private List<Vector3> accelerationArr = new List<Vector3>();
    private List<Vector3> lastVelocityArr = new List<Vector3>();
    private List<Vector3> currentVelocityArr = new List<Vector3>();
    private List<Quaternion> rotationArr = new List<Quaternion>();
    private List<int> timeArr = new List<int>();

    private long timeStart;
    private long timeEnd;

    // Platform
    private bool toConnect = false;
    private bool connected = false;
    [SerializeField] private GameObject platformInterfaceObject;
    private PlatformInterface platformInterface;

    
    void Start()
    {
        rb = vehicle.GetComponent<Rigidbody>();
        lastVelocity = transform.InverseTransformDirection(rb.velocity);

        timeStart = DateTimeOffset.Now.ToUnixTimeMilliseconds();
    }

    void FixedUpdate()
    {
        CalculateValues();
        if(connected) SendValues();
    }

    public bool IsConnected(){
        return connected;
    }

    private void OnApplicationQuit()
    {
        timeEnd = DateTimeOffset.Now.ToUnixTimeMilliseconds();
        SaveArraysToFile();
    }

    private void SendValues(){
        float xaxis = acceleration.x;
        float yaxis = acceleration.y;
        float zaxis = acceleration.z;

        float xangle = rotation.eulerAngles.x;
        float yangle = rotation.eulerAngles.y;
        float zangle = rotation.eulerAngles.z;

        float[] points = { xaxis, yaxis, zaxis, xangle, yangle, zangle };

        // SEND TO PLATFORM
        platformInterface.SendData(points);
    }

    // TODO: REMOVE
    /*private void LogValues()
    {
        /* Grapher.Log(jerk, "Jerk", Color.white);
        Grapher.Log(acceleration, "Acceleration", Color.red);
        Grapher.Log(lastVelocity, "Velocity", Color.green);
        Grapher.Log(rb.transform.position, "Position", Color.yellow);
        Grapher.Log(acceleratorInput, "Vertival Input", Color.cyan); */

        // Debug.Log("LV:" + lastVelocity + " V:" + transform.InverseTransformDirection(rb.velocity) + " || ACC:" + acceleration);
        // Debug.Log("rz:" + Math.Abs(rb.transform.rotation.y) + " || rze:" + Math.Abs(rb.transform.rotation.eulerAngles.y) + " || hi " + acceleratorInput);
    /*
        float xaxis = acceleration.x;
        float yaxis = acceleration.y;
        float zaxis = acceleration.z;

        float xangle = rotation.eulerAngles.x;
        float yangle = rotation.eulerAngles.y;
        float zangle = rotation.eulerAngles.z;

        float[] points = { xaxis, yaxis, zaxis, xangle, yangle, zangle };
            //    pointsToSend = points;

        /* if (connected)
        {
            // TEST
            if (Input.GetKey(KeyCode.Alpha1)) { testPoints[0]++; SendData(testPoints); }
            if (Input.GetKey(KeyCode.Alpha2)) { testPoints[0]--; SendData(testPoints); }
            if (Input.GetKey(KeyCode.Alpha3)) { testPoints[1]++; SendData(testPoints); }
            if (Input.GetKey(KeyCode.Alpha4)) { testPoints[1]--; SendData(testPoints); }
            if (Input.GetKey(KeyCode.Alpha5)) { testPoints[2]++; SendData(testPoints); }
            if (Input.GetKey(KeyCode.Alpha6)) { testPoints[2]--; SendData(testPoints); }

            if (Input.GetKey(KeyCode.Keypad7)) { testPoints[3]++; SendData(testPoints); }
            if (Input.GetKey(KeyCode.Keypad8)) { testPoints[3]--; SendData(testPoints); }
            if (Input.GetKey(KeyCode.Keypad4)) { testPoints[4]++; SendData(testPoints); }
            if (Input.GetKey(KeyCode.Keypad5)) { testPoints[4]--; SendData(testPoints); }
            if (Input.GetKey(KeyCode.Keypad1)) { testPoints[5]++; SendData(testPoints); }
            if (Input.GetKey(KeyCode.Keypad2)) { testPoints[5]--; SendData(testPoints); }

            //Debug.Log("ACC:" + testPoints[0] + " " + testPoints[1] + " "+testPoints[2] + " "+" ROT:" + testPoints[3] + " " + testPoints[4] + " "+testPoints[5] + " ");

            SendData(points);
        }*/

    /*}*/

    private void SaveArraysToFile()
    {
        long totalTime = timeEnd - timeStart;
        int inc = (int)(totalTime / accelerationArr.Count);

        int t = 0;
        for (int i = 0; i <= accelerationArr.Count; i++)
        {
            timeArr.Add(t);
            t += inc;
        }

        using (StreamWriter sw = new StreamWriter("./log_acceleration.txt"))
        {
            int i = 0;
            foreach (Vector3 v in accelerationArr)
            {
                sw.WriteLine(timeArr[i] + " " + v.x + " " + v.y + " " + v.z + "\n");
                i++;
            }
        }

        //Velocity
        using (StreamWriter sw = new StreamWriter("./log_velocity.txt"))
        {
            int i = 0;
            foreach (Vector3 v in lastVelocityArr)
            {
                sw.WriteLine(timeArr[i] + " " + v.x + " " + v.y + " " + v.z + "\n");
                i++;
            }
        }

        //Current Velocity
        using (StreamWriter sw = new StreamWriter("./log_current_velocity.txt"))
        {
            int i = 0;
            foreach (Vector3 v in currentVelocityArr)
            {
                sw.WriteLine(timeArr[i] + " " + v.x + " " + v.y + " " + v.z + "\n");
                i++;
            }
        }

        //Position
        using (StreamWriter sw = new StreamWriter("./log_position.txt"))
        {
            int i = 0;
            foreach (Vector3 v in positionArr)
            {
                sw.WriteLine(timeArr[i] + " " + v.x + " " + v.y + " " + v.z + "\n");
                i++;
            }
        }

        //Rotation
        using (StreamWriter sw = new StreamWriter("./log_rotation.txt"))
        {
            int i = 0;
            foreach (Quaternion v in rotationArr)
            {
                sw.WriteLine(timeArr[i] + " " + v.x + " " + v.y + " " + v.z + " " + v.w + "\n");
                i++;
            }
        }
    }

    private void CalculateValues()
    {
        currentVelocity = transform.InverseTransformDirection(rb.velocity);
        acceleration = (currentVelocity - lastVelocity) / Time.fixedDeltaTime;
        jerk = (acceleration - lastAcceleration) / Time.fixedDeltaTime;
        rotation = rb.rotation;

        accelerationArr.Add(acceleration);
        lastVelocityArr.Add(currentVelocity);
        lastVelocity = currentVelocity;
        lastAcceleration = acceleration;
        rotationArr.Add(rotation);
        positionArr.Add(rb.transform.position);
        lastPosition = rb.transform.position;
    }

    public void TryConnect(){
        platformInterfaceObject.SetActive(true);
        platformInterface = platformInterfaceObject.GetComponent<PlatformInterface>();
        connected = platformInterface.ConnectToPlatform();
    }
}
