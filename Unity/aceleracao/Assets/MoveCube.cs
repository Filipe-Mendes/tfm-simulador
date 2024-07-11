using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
using System.IO;
using System;



public class MoveCube : MonoBehaviour
{
    public int power = 10;

    private Rigidbody rb;

    private PlayerInput userInput;
    private InputAction steerAction;
    private InputAction acceleratorAction;
    private InputAction brakeAction;

    private float move = 0;

    // Movement measurements
    private Vector3 jerk;
    private Vector3 acceleration;
    private Vector3 lastAcceleration;
    private Vector3 currentVelocity;
    private Vector3 lastVelocity;
    private Vector3 lastPosition;
    private Vector3 currentPosition;
    private Quaternion rotation;

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

    void Start()
    {
         Debug.Log(rb);
        rb = GetComponent<Rigidbody>();
        userInput = GetComponent<PlayerInput>();
        userInput.neverAutoSwitchControlSchemes = true;

        steerAction = userInput.actions["Steering"];
        acceleratorAction = userInput.actions["Accelerator"];
        brakeAction = userInput.actions["Brake"];


        lastPosition = transform.position;
        lastVelocity = new Vector3(0, 0, 0);
        lastAcceleration = new Vector3(0, 0, 0);
        timeStart = DateTimeOffset.Now.ToUnixTimeMilliseconds();

    }

    // Update is called once per frame
    void FixedUpdate()
    {

        Debug.Log(rb);
       /*  move = 0;
        move += acceleratorAction.ReadValue<float>() * 0.01f;
        transform.Translate(0, 0, move); */
        if(acceleratorAction.ReadValue<float>() != 0){
            // rb.AddForce(Vector3.forward * power);
            rb.AddForce(0, 0, 1, ForceMode.Impulse);


        }


        CalculateValues();
        SaveArraysToFile();
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


    }

    private void CalculateValues()
    {
        currentPosition = transform.position;
        // currentVelocity = rb.velocity;
        currentVelocity = (currentPosition - lastPosition) / Time.fixedDeltaTime;
        lastPosition = currentPosition;
        acceleration = (currentVelocity - lastVelocity) / Time.fixedDeltaTime;
        // Debug.Log("ACC: " + acceleration);
        lastVelocity = currentVelocity;

        rotation = transform.rotation;


        positionArr.Add(currentPosition);
        lastVelocityArr.Add(currentVelocity);
        accelerationArr.Add(acceleration);
        rotationArr.Add(rotation);

        timeArr.Add(t);
        t += (int)(Time.fixedDeltaTime * 1000);

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

}
