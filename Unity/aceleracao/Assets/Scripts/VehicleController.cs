using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;
using UnityEngine.SceneManagement;
using System.Net;
using System.Net.Sockets;
using System.Text;
using UnityEngine.InputSystem;
using UnityEngine.Assertions;
using System.Threading;


public class VehicleController : MonoBehaviour
{
    private bool ready = false;

    // [SerializeField] private GameObject driverPosition;
    [SerializeField] private Camera vrCamera;

    // Testing variables
    // [SerializeField] private float speedBumpAcc = 0.4f;
    [SerializeField] private float speedBumpAcc = 1;
    [SerializeField] private float speedBumpBrake = 1;
    private DRIVING_MODE mode;



    private int curbBegin = 50;
    private int curbEnd = 75;

    private bool[] passedSBs = { false, false };
    [SerializeField] private GameObject speedBump;
    [SerializeField] private GameObject speedBump1;

    private bool passedSB = false;
    private bool passedSB1 = false;



    [SerializeField] private int hardcodedStoppingPoint = 100;
    bool decelerating = false;


    private Vector3 initialPosition = new Vector3(0, 5, 35);
    private Quaternion initialRotation = new Quaternion(0, 1, 0, 0);
    [SerializeField] private GameObject centerOfMass;

    private Rigidbody rb;

    // Handling input
    private float steerInput;
    private float previousSteerInput = -2;
    private float acceleratorInput;
    private float brakeInput;
    private const string ACCELERATOR = "Accelerator";
    private const string BRAKE = "Brake";
    private bool isBraking;
    private bool turned = false;
    private bool reverse = false;

    private float currentSteerAngle;
    private float currentbrakeForce;

    [SerializeField] private float motorForce;
    private float reverseMotorForce;
    [SerializeField] private float brakeForce;
    [SerializeField] private float maxSteerAngle;

    [SerializeField] private WheelCollider[] wheelColliders;
    [SerializeField] private Transform[] wheelMeshes;

    // Input configurations
    private INPUT_DEVICE inputDevice;
    private PlayerInput userInput;
    private InputAction steerAction;
    private InputAction acceleratorAction;
    private InputAction brakeAction;
    private InputAction clutchAction;
    private InputAction reverseAction;
    private InputAction restartAction;


    // Steering wheel
    [SerializeField] private float maxSteeringWheelAngle = 540;
    [SerializeField] private GameObject steeringWheel;

    private long timeStart;
    private long waitingTime = 1000;
    private bool waitOver = false;


    private void Start()
    {
        rb = GetComponent<Rigidbody>();
        rb.centerOfMass = centerOfMass.transform.position;
        reverseMotorForce = motorForce / 5;

        // Configure Input
        userInput = GetComponent<PlayerInput>();
        userInput.neverAutoSwitchControlSchemes = true;

        steerAction = userInput.actions["Steering"];
        acceleratorAction = userInput.actions["Accelerator"];
        brakeAction = userInput.actions["Brake"];
        clutchAction = userInput.actions["Clutch"];
        reverseAction = userInput.actions["Reverse"];

        restartAction = userInput.actions["Restart"];


        rb.sleepThreshold = 0.0f;

        // timeStart = DateTimeOffset.Now.ToUnixTimeMilliseconds();

    }

    public void SetUpVehicle(DRIVING_MODE dm, INPUT_DEVICE ind)
    {
        mode = dm;
        inputDevice = ind;
        Debug.Log("in: " + userInput.currentControlScheme);

        switch (inputDevice)
        {
            case INPUT_DEVICE.KEYBOARD:
                userInput.SwitchCurrentControlScheme("Keyboard&Mouse", InputSystem.devices[0]);
                break;
            case INPUT_DEVICE.JOYSTICK:
                userInput.SwitchCurrentControlScheme("Joystick", Joystick.all[0]);
                break;
        }

        ready = true;
        timeStart = DateTimeOffset.Now.ToUnixTimeMilliseconds();
    }

    /*     private void UpdateDriverPosition()
        {

            float rotationAngleY = resetPos.rotation.eulerAngles.y - driverPosition.transform.rotation.eulerAngles.y;
            driverPosition.transform.Rotate(0, rotationAngleY, 0);

            Vector3 distance = resetPos.position - vrCamera.transform.position;
            driverPosition.transform.position += distance;
        } */

    private void FixedUpdate()
    {
        // Restart the scene
        if (restartAction.ReadValue<float>() == 1)
        {
            SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);
        }

        /* if (!waitOver)
        {
            Debug.Log("wait not over");
            if (DateTimeOffset.Now.ToUnixTimeMilliseconds() >= timeStart + waitingTime) waitOver = true;
        } */

        if (ready)
        {
            if (mode != DRIVING_MODE.FREE) PerformTestScenario();
            else HandleInput();

            HandleMotor();
            HandleSteering();
            UpdateWheels();
        }
    }

    // private float accIn = 0;
    // private float brIn = 0;
    private bool drag = false;
    public float brakeSmoothFactor = 0.05f;  // Smoothing factor for brake input
    private float smoothedBrakeInput = 0f;  // Store the smoothed brake input


    private void HandleInput()
    {
        acceleratorInput = acceleratorAction.ReadValue<float>();
        brakeInput = brakeAction.ReadValue<float>();

        // smoothedBrakeInput = Mathf.Lerp(smoothedBrakeInput, brakeInput, brakeSmoothFactor);
        smoothedBrakeInput = brakeInput;
        if (brakeInput == 0) smoothedBrakeInput = 0;

        steerInput = steerAction.ReadValue<float>();
        if (previousSteerInput == -2) previousSteerInput = steerInput;
        if (acceleratorInput == 0 && brakeInput == 0) drag = true;
        else drag = false;

        /* if(inputDevice == INPUT_DEVICE.KEYBOARD){
            acceleratorInput = Mathf.Lerp(acceleratorInput, accIn, 0.05f);
            brakeInput = Mathf.Lerp(brakeInput, brIn, 0.2f);
            Debug.Log("LERP accelerator: " + acceleratorInput + " || brake: " + brakeInput);
        } */

        // Putting the car in reverse
        if (Math.Abs((int)rb.velocity.magnitude) < 1)
        {
            //TODO:
            // if (reverseAction.ReadValue<float>() == 1) reverse = !reverse;
            if (reverseAction.ReadValue<float>() == 1) reverse = true;
            else reverse = false;
        }
    }


    public void PerformTestScenario()
    {
        // HARDCODED MOVEMENT

        if (!waitOver)
        {
            if (DateTimeOffset.Now.ToUnixTimeMilliseconds() >= timeStart + waitingTime) waitOver = true;
        }
        if (waitOver)
        {

            // STRAIGHT LINE
            if (mode == DRIVING_MODE.STRAIGHT_LINE)
            {

                acceleratorInput = 1f;
                if (rb.transform.position.z > hardcodedStoppingPoint / 2) //25
                {
                    acceleratorInput = 0;
                    if (rb.transform.position.z > hardcodedStoppingPoint + 20) //70
                    {
                        brakeInput = 1f;
                        smoothedBrakeInput = brakeInput;
                        isBraking = true;
                    }
                }
                Debug.Log("acc: " + acceleratorInput + " || brake: " + brakeInput + " || pos.z: " + rb.transform.position.z);
            }

            // TODO: mode == DRIVING_MODE.COLLISION 


            // TODO: FINAL
            if (mode == DRIVING_MODE.SIDE_TILT)
            {
                acceleratorInput = 1;
                if (rb.transform.position.z > curbBegin / 2) acceleratorInput = 0;
                if (rb.transform.position.z > curbEnd)
                {
                    brakeInput = 1;
                    isBraking = true;
                }
            }

            // REVERSE
            if (mode == DRIVING_MODE.REVERSE)
            {
                reverse = true;
                acceleratorInput = 1;
                if (rb.transform.position.z < -hardcodedStoppingPoint / 3)
                {
                    acceleratorInput = 0;
                    isBraking = true;
                }
            }

            // SPEED BUMP
            if (mode == DRIVING_MODE.SPEED_BUMP)
            {
                // Debug.Log(acceleratorInput + " " + brakeInput + " acc: " + acceleration.z + " m/s  vel: " + currentVelocity.z * 3.6 + " km/h" );

                //acceleratorInput = 0.4f;
                acceleratorInput = speedBumpAcc;

                if (!passedSB && rb.transform.position.z + 25 >= speedBump.transform.position.z)
                {
                    acceleratorInput = 0;
                    // brakeInput = speedBumpBrake;
                }

                if (rb.transform.position.z >= speedBump.transform.position.z + 3)
                {
                    passedSB = true;
                    // brakeInput = 0;
                }

                //if(passedSB && !passedSB1) acceleratorInput += 0.2f;

                if (!passedSB1 && rb.transform.position.z + 25 >= speedBump1.transform.position.z)
                {
                    acceleratorInput = 0;
                    // acceleratorInput -= 0.2f;
                    // brakeInput = speedBumpBrake;
                }

                if (rb.transform.position.z >= speedBump1.transform.position.z + 3)
                {
                    passedSB1 = true;
                    // brakeInput = 0;
                }

                if (passedSB1 && rb.transform.position.z > speedBump1.transform.position.z + 10)
                {
                    acceleratorInput = 0;
                    isBraking = true;
                    brakeInput = speedBumpBrake;
                    smoothedBrakeInput = brakeInput;
                }
                Debug.Log("acc: " + acceleratorInput);
            }


            // CURVE
            if (mode == DRIVING_MODE.CURVE)
            {

                float decPos = 0;
                if (decelerating) acceleratorInput = 0;
                else acceleratorInput = 0.8f;

                if (rb.velocity.z * 3.6 > 10 && !decelerating) // INITIAL ACCELERATION
                {
                    // Debug.Log("ai " + acceleratorInput + " || decPos " + decPos + " || pos " + rb.transform.position + " || dec " + decelerating );
                    acceleratorInput = 0;
                    decelerating = true;
                    decPos = rb.transform.position.z;   // POSITION WHERE THE VEHICLE STOPPED ACCELERATING
                }

                if (decelerating && rb.transform.position.z >= decPos + 20)     // VEHICLE STARTS TURNING 20M AFTER DECPOS
                {
                    if (Math.Abs(rb.transform.rotation.eulerAngles.y) >= 80)
                    {
                        turned = true;
                        steerInput = 0;
                    }
                    if(!turned) steerInput = 0.1f;

                    if (rb.transform.position.x > 50) isBraking = true;
                }
            }
        }
    }

    private void HandleMotor()
    {

        Debug.Log("acc: " + acceleratorInput + " || br: " + smoothedBrakeInput);

        if (reverse)
        {
            acceleratorInput = -acceleratorInput;
            for (int i = 0; i < 2; i++) wheelColliders[i].motorTorque = acceleratorInput * reverseMotorForce;
        }
        else
        {
            for (int i = 0; i < 2; i++) wheelColliders[i].motorTorque = acceleratorInput * motorForce;
        }

        currentbrakeForce = 0;
        // if (isBraking) currentbrakeForce = brakeForce;
        // if (!isBraking && brakeInput != 0) currentbrakeForce = brakeInput * brakeForce;
        currentbrakeForce = brakeForce * smoothedBrakeInput;

        //if (drag) currentbrakeForce = brakeForce * 0.05f;

        ApplyBraking();
    }

    // public float brakeSmoothFactor = 0.1f;  // Smoothing factor for brake force
    // private float smoothedBrakeForce = 0f;  // Store the smoothed brake force


    private void ApplyBraking()
    {

        foreach (WheelCollider wheel in wheelColliders)
        {
            wheel.brakeTorque = currentbrakeForce;
        }
    }

    private void HandleSteering()
    {
        currentSteerAngle = maxSteerAngle * steerInput;
        // Debug.Log("rot: " + Mathf.Lerp(0, currentSteerAngle, t));
        for (int i = 0; i < 2; i++) wheelColliders[i].steerAngle = Mathf.Lerp(wheelColliders[i].steerAngle, currentSteerAngle, 0.2f);
        // for (int i = 0; i < 2; i++) wheelColliders[i].steerAngle = currentSteerAngle;

        steeringWheel.transform.Rotate(maxSteeringWheelAngle * +(steerInput - previousSteerInput), 0, 0, Space.Self);
        previousSteerInput = steerInput;
    }

    private void UpdateWheels()
    {
        for (int i = 0; i < wheelColliders.Length; i++)
        {
            UpdateSingleWheel(wheelColliders[i], wheelMeshes[i]);
        }
    }

    private void UpdateSingleWheel(WheelCollider wheelCollider, Transform wheelTransform)
    {
        Vector3 pos;
        Quaternion rot;
        wheelCollider.GetWorldPose(out pos, out rot);
        wheelTransform.rotation = rot;
        wheelTransform.position = pos;
    }

    public bool IsReverse() { return reverse; }

    public float GetAcceleratorInput()
    {
        return acceleratorInput;
    }

    public float GetBrakeInput()
    {
        return smoothedBrakeInput;
    }

    public float GetSteerInput()
    {
        return steerInput;
    }
}