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

    /*
    private List<Vector3> motorTorqueArr = new List<Vector3>();
    private List<float> motorTorqueArr = new List<float>();
    private List<float> frontSuspension = new List<float>();
    private List<float> frontSuspension1 = new List<float>();
    private List<float> rearSuspension = new List<float>();
    private List<float> rearSuspension1 = new List<float>(); 
    */



    private long timeStart;
    private long timeEnd;

    // Platform
    private bool toConnect = false;
    private bool connected = false;
    [SerializeField] private GameObject platformInterfaceObject;
    private PlatformInterface platformInterface;

    [SerializeField] private bool clamping = true;
    [SerializeField] private bool invertXZ = false;
    [SerializeField] private bool sendHarcoded = false;
    private float[][] hardcodedData;
    private int index = 0;

    public enum File_Mode
    {
        Straight_line_drag,
        Straight_line_brake,
        Speed_bump,
        Curve,
        Side_tilt
    }
    [SerializeField] public File_Mode file;

    private static Dictionary<File_Mode, string> hardcodedFiles = new Dictionary<File_Mode, string>
    {
        { File_Mode.Straight_line_brake, "straight_line_brake_hardcoded.txt" },
        { File_Mode.Straight_line_drag, "straight_line_drag_hardcoded.txt" },
        { File_Mode.Speed_bump, "speed_bump_hardcoded.txt" },
        { File_Mode.Curve, "curve_hardcoded.txt" },
        { File_Mode.Side_tilt, "side_tilt_hardcoded.txt" }
    };


    void Start()
    {
        rb = vehicle.GetComponent<Rigidbody>();

        lastPosition = vehicle.transform.position;
        lastVelocity = new Vector3(0, 0, 0);
        lastAcceleration = new Vector3(0, 0, 0);

        timeStart = DateTimeOffset.Now.ToUnixTimeMilliseconds();

        vehicleController = vehicle.GetComponent<VehicleController>();

        rb.sleepThreshold = 0.0f;

        if (sendHarcoded)
        {
            string path = Application.dataPath + "/HardcodedAcceleration/";

            accelerationArr = LoadFileIntoListVector3(path + "acceleration_" + hardcodedFiles[file]);
            rotationArr = LoadFileIntoListQuaternion(path + "rotation_" + hardcodedFiles[file]);
            Debug.Log("acc count: " + accelerationArr.Count + " || rot count: " + rotationArr.Count);
            if (accelerationArr.Count != rotationArr.Count)
            {
                Debug.Log("Acceleration and rotation files do not have the same size");
                UnityEditor.EditorApplication.isPlaying = false;
            }
        }
    }

    void FixedUpdate()
    {
        if (sendHarcoded)
        {
            if (index < accelerationArr.Count) ParseHardcodedValues();
            else UnityEditor.EditorApplication.isPlaying = false;
        }
        else CalculateValues();

        if (connected) SendValues();
    }

    public bool IsConnected()
    {
        return connected;
    }

    private void OnApplicationQuit()
    {
        timeEnd = DateTimeOffset.Now.ToUnixTimeMilliseconds();
        if (!sendHarcoded) SaveArraysToFile();
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
    [SerializeField] private int windowSize = 5;
    private int windowSizeAdjustment = 0;
    [SerializeField] private int maxIncreaseAcceleration = 5;
    private int accCount = 0;
    private Queue<Vector3> window = new Queue<Vector3>();

    private Vector3 QueueSum(Queue<Vector3> queue){
        Vector3 sum = new Vector3();
        foreach(Vector3 ac in queue){
            sum += ac;
        }    
        return sum;
    }

    private void CalculateValues()
    {
        accCount++;

        currentPosition = vehicle.transform.position;
        currentVelocity = vehicle.transform.InverseTransformDirection(rb.velocity);
        lastPosition = currentPosition;
        acceleration = (currentVelocity - lastVelocity) / Time.fixedDeltaTime;

        // Ignore spikes in acceleration
        Vector3 absoluteAcc = new Vector3(Mathf.Abs(acceleration.x),Mathf.Abs(acceleration.y),Mathf.Abs(acceleration.z));
        Vector3 absoluteLastAcc = new Vector3(Mathf.Abs(lastAcceleration.x),Mathf.Abs(lastAcceleration.y),Mathf.Abs(lastAcceleration.z));

        Vector3 accDifference = acceleration - lastAcceleration;

        if(acceleration != Vector3.zero){
            Debug.Log("Don't enqueue 1");
            if (accDifference.x >  maxIncreaseAcceleration  || 
                accDifference.y >  maxIncreaseAcceleration  || 
                accDifference.z >  maxIncreaseAcceleration ){
           /*  if (absoluteAcc.x > absoluteLastAcc.x * maxIncreaseAcceleration || 
                absoluteAcc.y > absoluteLastAcc.y * maxIncreaseAcceleration || 
                absoluteAcc.z > absoluteLastAcc.z * maxIncreaseAcceleration){ */
                Debug.Log("Don't enqueue 2");
                // Do not enqueue acceleration value
                windowSizeAdjustment++;
            } else {
                Debug.Log("Enqueue");
                window.Enqueue(acceleration);
                windowSizeAdjustment = 0;
            }
        }   


        if(accCount > windowSize && averageAcceleration){

            avgAcc = QueueSum(window)/(windowSize - windowSizeAdjustment);
            window.Dequeue();
            acceleration = avgAcc;
        }

        lastAcceleration = acceleration;

        lastVelocity = currentVelocity;
        rotation = vehicle.transform.rotation;

        // CLAMP VALUES IF VALUES EXCEED LIMITS
        // if (clamping) ClampValues();

        positionArr.Add(currentPosition);
        lastVelocityArr.Add(currentVelocity);
        accelerationArr.Add(acceleration);
        rotationArr.Add(rotation);

        timeArr.Add(t);
        t += (int)(Time.fixedDeltaTime * 1000);

        Debug.Log("acc :" + acceleration);
    }

    /* private void ClampValues()
    {
        if (vehicleController.GetBrakeInput() < 0.1 && vehicleController.GetAcceleratorInput() < 0.1 && currentVelocity.z < 0.5f)
        {
            acceleration.x = Mathf.Clamp(acceleration.x, -1.0f, 1.0f);
            acceleration.y = Mathf.Clamp(acceleration.y, -1.0f, 1.0f);
            acceleration.z = Mathf.Clamp(acceleration.z, -1.0f, 1.0f);
        }
    } */

    private void ParseHardcodedValues()
    {
        acceleration = accelerationArr[index];
        rotation = rotationArr[index];
        index++;
    }

    public void TryConnect()
    {
        platformInterfaceObject.SetActive(true);
        platformInterface = platformInterfaceObject.GetComponent<PlatformInterface>();
        connected = platformInterface.ConnectToPlatform();
    }

    /*
    Vector3 CalculateAverageWheelPosition()
    {
        Vector3 sum = Vector3.zero;
        int childCount = 0;

        foreach (Transform child in wheels.transform)
        {
            sum += wheels.transform.TransformPoint(child.localPosition); ;
            childCount++;
        }
        Vector3 avg = sum / childCount;
        Debug.Log("AVG: " + avg);
        return avg;
    }

    public Vector3 Round(Vector3 vector3, int decimalPlaces)
    {
        float multiplier = 1;
        for (int i = 0; i < decimalPlaces; i++)
        {
            multiplier *= 10f;
        }
        return new Vector3(
            Mathf.Round(vector3.x * multiplier) / multiplier,
            Mathf.Round(vector3.y * multiplier) / multiplier,
            Mathf.Round(vector3.z * multiplier) / multiplier);
    } 
    */
    public List<Vector3> LoadFileIntoListVector3(string path)
    {
        List<Vector3> list = new List<Vector3>();
        try
        {
            string[] lines = File.ReadAllLines(path);

            foreach (string line in lines)
            {
                if (!string.IsNullOrWhiteSpace(line))
                {
                    string[] parts = line.Trim().Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                    Vector3 listLine = new Vector3(float.Parse(parts[1]), float.Parse(parts[2]), float.Parse(parts[3]));
                    // Debug.Log("line: " + line + "|| listline: " + listLine);

                    list.Add(listLine);
                }
            }
            Debug.Log("Finished loading file");
        }
        catch (Exception e)
        {
            Debug.Log("An error occurred: " + e.Message);
        }
        return list;
    }

    public List<Quaternion> LoadFileIntoListQuaternion(string path)
    {
        List<Quaternion> list = new List<Quaternion>();
        try
        {
            string[] lines = File.ReadAllLines(path);

            foreach (string line in lines)
            {
                if (!string.IsNullOrWhiteSpace(line))
                {
                    string[] parts = line.Trim().Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                    Quaternion listLine = new Quaternion(float.Parse(parts[1]), float.Parse(parts[2]), float.Parse(parts[3]), float.Parse(parts[4]));
                    // Debug.Log("line: " + line + "|| listline: " + listLine);

                    list.Add(listLine);
                }
            }
            Debug.Log("Finished loading file");
        }
        catch (Exception e)
        {
            Debug.Log("An error occurred: " + e.Message);
        }
        return list;
    }
}