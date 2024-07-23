using System.Collections;
using System;
using System.IO;
using System.Collections.Generic;
using UnityEngine;


public class Logger : MonoBehaviour
{

    private VehicleController vehicleController;

    // Vehicle
    [SerializeField] private GameObject vehicle;
    private Rigidbody rb;

    // Movement measurements
    private Vector3 jerk;
    private Vector3 acceleration;
    private Vector3 lastAcceleration;
    private Vector3 lastAccelerationNoAvg;
    private Vector3 currentVelocity;
    private Vector3 lastVelocity;
    private Vector3 lastPosition;
    private Vector3 currentPosition;
    private Quaternion rotation;

    private float[] pointsToSend;


    // Logging
    private List<Vector3> positionArr = new List<Vector3>();
    private List<Vector3> accelerationArr = new List<Vector3>();
    private List<Vector3> lastVelocityArr = new List<Vector3>();
    private List<Vector3> currentVelocityArr = new List<Vector3>();
    private List<Quaternion> rotationArr = new List<Quaternion>();
    private List<int> timeArr = new List<int>();
    private int t = 0;

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

        lastPosition = vehicle.transform.position;
        lastVelocity = new Vector3(0, 0, 0);
        lastAcceleration = new Vector3(0, 0, 0);

        timeStart = DateTimeOffset.Now.ToUnixTimeMilliseconds();

        vehicleController = vehicle.GetComponent<VehicleController>();

        rb.sleepThreshold = 0.0f;

    }

    void FixedUpdate()
    {
        CalculateValues();

        if (connected) SendValues();
    }

    public bool IsConnected()
    {
        return connected;
    }

    private void OnApplicationQuit()
    {
        timeEnd = DateTimeOffset.Now.ToUnixTimeMilliseconds();
        SaveArraysToFile();
    }

    private void SendValues()
    {
        float xaxis = acceleration.x;
        float yaxis = acceleration.y;
        float zaxis = acceleration.z;

        float xangle = rotation.eulerAngles.x;
        float yangle = rotation.eulerAngles.y;
        float zangle = rotation.eulerAngles.z;

        float[] points = { xaxis, yaxis, zaxis, xangle, yangle, zangle };

        // SEND TO PLATFORM
        platformInterface.SendData(points);

        Debug.Log("x: " + xaxis + " || y: " + yaxis + " || z: " + zaxis);
    }

    private void SaveArraysToFile()
    {
        /*
        long totalTime = timeEnd - timeStart;
        int inc = (int)(totalTime / accelerationArr.Count);

         int t = 0;
        for (int i = 0; i <= accelerationArr.Count; i++)
        {
            timeArr.Add(t);
            t += inc;
        } */

        using (StreamWriter sw = new StreamWriter("./log_acceleration.txt"))
        {
            int i = 0;
            foreach (Vector3 v in accelerationArr)
            {
                sw.WriteLine(timeArr[i] + " " + v.x + " " + v.y + " " + v.z + "");
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
        /* using (StreamWriter sw = new StreamWriter("./log_current_velocity.txt"))
        {
            int i = 0;
            foreach (Vector3 v in currentVelocityArr)
            {
                sw.WriteLine(timeArr[i] + " " + v.x + " " + v.y + " " + v.z + "\n");
                i++;
            }
        } */

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

        /* using (StreamWriter sw = new StreamWriter("./log_torque.txt"))
        {
            int i = 0;
            foreach (float v in motorTorqueArr)
            {
                sw.WriteLine(timeArr[i] + " " + v + "\n");
                // sw.WriteLine(timeArr[i] + " " + to + "\n");
                i++;
            }
        } */
        /*         using (StreamWriter sw = new StreamWriter("./log_suspension.txt"))
                {
                    int i = 0;
                    foreach (float v in timeArr)
                    {
                        sw.WriteLine(v + " " + rearSuspension[i] + " " + rearSuspension1[i] + " " + frontSuspension[i] + " " + frontSuspension1[i] + "\n");
                        // sw.WriteLine(timeArr[i] + " " + to + "\n");
                        i++;
                    }
                } */
    }

    private Vector3 avgAcc;
    [SerializeField] private bool averageAcceleration = true;
    [SerializeField] private int maxWindowSize = 5;
    private int currentWindowSize = 0;
    [SerializeField] private int maxIncreaseAcceleration = 7;
    private int accCount = 0;
    private Queue<Vector3> window = new Queue<Vector3>();

    private Vector3 QueueSum(Queue<Vector3> queue)
    {
        Vector3 sum = new Vector3();
        foreach (Vector3 ac in queue)
        {
            sum += ac;
        }
        return sum;
    }

    private bool firstValue = false;
    private void CalculateValues()
    {
        accCount++;

        currentPosition = vehicle.transform.position;
        currentVelocity = vehicle.transform.InverseTransformDirection(rb.velocity);
        lastPosition = currentPosition;
        acceleration = (currentVelocity - lastVelocity) / Time.fixedDeltaTime;

        // Ignore spikes in acceleration
        Vector3 absoluteAcc = new Vector3(Mathf.Abs(acceleration.x), Mathf.Abs(acceleration.y), Mathf.Abs(acceleration.z));
        Vector3 absoluteLastAcc = new Vector3(Mathf.Abs(lastAcceleration.x), Mathf.Abs(lastAcceleration.y), Mathf.Abs(lastAcceleration.z));
        Vector3 accDifference = acceleration - lastAccelerationNoAvg;
        // Vector3 accDifference = acceleration - lastAcceleration;
        Debug.Log("diff: " + accDifference);

        bool spike = false;
        Debug.Log(accCount + " :: " + QueueToString(window, 2) + " :: spike: " + spike);

        if (averageAcceleration)
        {
            if (acceleration.z > 0.01f || firstValue) 
            {
                firstValue = true;
                // Check if value is a spike in acceleration and if it should be put in the queue
                if (accDifference.x > maxIncreaseAcceleration || accDifference.y > maxIncreaseAcceleration || accDifference.z > maxIncreaseAcceleration) spike = true;

                if (!spike)
                {
                    window.Enqueue(acceleration);
                    currentWindowSize++;
                }
            }

            Debug.Log(accCount + " :: " + QueueToString(window, 2) + " :: spike: " + spike);
            Debug.Log("time: " + accCount + " || spike: " + spike );

            lastAccelerationNoAvg = acceleration;

            // DEQUEUE THE FIRST VALUE IN THE QUEUE
            if (currentWindowSize > 0)
            {
                avgAcc = QueueSum(window) / currentWindowSize;
                if (currentWindowSize >= maxWindowSize)
                {
                    window.Dequeue();
                    currentWindowSize--;
                }
                acceleration = avgAcc;
            }
            Debug.Log(accCount + " :: " + QueueToString(window, 2) + " :: spike: " + spike);
        }


        lastAcceleration = acceleration;

        lastVelocity = currentVelocity;
        rotation = vehicle.transform.rotation;

        positionArr.Add(currentPosition);
        lastVelocityArr.Add(currentVelocity);
        accelerationArr.Add(acceleration);
        rotationArr.Add(rotation);

        timeArr.Add(t);
        t += (int)(Time.fixedDeltaTime * 1000);

        Debug.Log("acc :" + acceleration);
    }

    private string QueueToString(Queue<Vector3> queue, int coordinate)
    {
        string str = "";
        foreach (Vector3 value in window)
        {
            str += value[coordinate] + " | ";
        }
        return str;
    }

    public void TryConnect()
    {
        platformInterfaceObject.SetActive(true);
        platformInterface = platformInterfaceObject.GetComponent<PlatformInterface>();
        connected = platformInterface.ConnectToPlatform();
    }

}