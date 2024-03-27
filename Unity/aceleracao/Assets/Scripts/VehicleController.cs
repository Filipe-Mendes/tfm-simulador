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


public class VehicleController : MonoBehaviour
{
    private bool ready = false;

    [SerializeField] private Transform resetPos;
    [SerializeField] private GameObject driverPosition;
    [SerializeField] private Camera vrCamera;

    // Testing variables
    // [SerializeField] private float speedBumpAcc = 0.4f;
    [SerializeField] private float speedBumpAcc = 1;
    [SerializeField] private float speedBumpBrake = 0.5f;
    private DRIVING_MODE mode;








    [SerializeField] private GameObject[] speedBumps;
    private bool[] passedSBs = {false, false};


    [SerializeField] private GameObject speedBump;
    [SerializeField] private GameObject speedBump1;
    
    private bool passedSB = false;
    private bool passedSB1 = false;











    [SerializeField] private TMPro.TMP_Text ip_text;


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

    }

    public void SetUpVehicle(DRIVING_MODE dm, INPUT_DEVICE ind){
        mode = dm;
        inputDevice = ind;
        Debug.Log("in: " + userInput.currentControlScheme);

        switch(inputDevice){
            case INPUT_DEVICE.KEYBOARD:
                userInput.SwitchCurrentControlScheme("Keyboard&Mouse", InputSystem.devices[0]);
                break;
            case INPUT_DEVICE.JOYSTICK:
                userInput.SwitchCurrentControlScheme("Joystick", Joystick.all[0]);
                break;
        }

        ready = true;
    }

    private void UpdateDriverPosition(){

        float rotationAngleY = resetPos.rotation.eulerAngles.y - driverPosition.transform.rotation.eulerAngles.y;
        driverPosition.transform.Rotate(0,rotationAngleY, 0);

        Vector3 distance = resetPos.position - vrCamera.transform.position;
        driverPosition.transform.position += distance;
    }


    private void FixedUpdate()
    {
        // Restart the scene
        if (restartAction.ReadValue<float>() == 1){
            SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);
        }


        if(ready){
            Debug.Log("Vehicle ready");

            // if(clutchAction.ReadValue<float>() != -1) finishedSetUp = true;

            // Debug.Log(userInput.currentControlScheme + " || steer: " + steerAction.ReadValue<float>() + " || accelerator: " + acceleratorAction.ReadValue<float>()  
            // + " || brake: " + brakeAction.ReadValue<float>()  + " || clutch: " + clutchAction.ReadValue<float>() );
            //UpdateDriverPosition();
    
            if (mode != DRIVING_MODE.FREE) PerformTestScenario();
            else HandleInput();

            HandleMotor();
            HandleSteering();
            UpdateWheels();
        }
    }

    private void HandleInput()
    {
        acceleratorInput = acceleratorAction.ReadValue<float>();
        brakeInput = brakeAction.ReadValue<float>();
        steerInput = steerAction.ReadValue<float>();
        if(previousSteerInput == -2) previousSteerInput = steerInput; 

        ip_text.text = "";
        ip_text.text += userInput.currentControlScheme + "\nsteer: " + steerInput + "\naccelerator: " + acceleratorInput + "\nbrake: " + brakeInput  + "\nclutch: " + clutchAction.ReadValue<float>() + "\nreverse: " + reverseAction.ReadValue<float>();

        // Putting the car in reverse
        if (Math.Abs((int)rb.velocity.magnitude) < 1)
        {
            // if (reverseAction.ReadValue<float>() == 1) reverse = !reverse;
            if (reverseAction.ReadValue<float>() == 1) reverse = true;
            else reverse = false;
        }   
    }
    

    public void PerformTestScenario()
    {
        // HARDCODED MOVEMENT

        // STRAIGHT LINE
        if (mode == DRIVING_MODE.STRAIGHT_LINE)
        {
            acceleratorInput = 1;
            //if (rb.transform.position.z > hardcodedStoppingPoint/2)
            //{
                if (rb.velocity.magnitude <= 10) {
                    Debug.Log("ACC 1 " + rb.velocity.magnitude);
                    acceleratorInput = 1;
                }
                else {
                    Debug.Log("ACC 0 " + rb.velocity.magnitude);
                    acceleratorInput = 0f;
                }
                
                
                
                //acceleratorInput = 0;
                //if (rb.transform.position.z > hardcodedStoppingPoint + 20) {
                    //brakeInput = 0.5f;
                    //if(brakeInput < 1) brakeInput += 0.01f;
                    // isBraking = true;
                //}
            //}
            //Debug.Log("acc: " + acceleratorInput + " || brake: " + brakeInput + " || pos.z: " + rb.transform.position.z );
        }


        if (mode == DRIVING_MODE.COLLISION || mode == DRIVING_MODE.SIDE_TILT)
        {
            acceleratorInput = 1;
            if (rb.transform.position.z > hardcodedStoppingPoint)
            {
                acceleratorInput = 0;
                isBraking = true;
            }
        }

        // REVERSE
        if (mode == DRIVING_MODE.REVERSE)
        {
            reverse = true;
            Debug.Log("test reverse " + reverse);
            acceleratorInput = 1;
            if (rb.transform.position.z < -hardcodedStoppingPoint)
            {
                acceleratorInput = 0;
                isBraking = true;
            }
        }

        // SPEED BUMP
        if (mode == DRIVING_MODE.SPEED_BUMP)
        {
            // Debug.Log(acceleratorInput + " " + brakeInput + " acc: " + acceleration.z + " m/s  vel: " + currentVelocity.z * 3.6 + " km/h" );
            speedBump.SetActive(true);
            speedBump1.SetActive(true);

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


            if (rb.transform.position.z > speedBump1.transform.position.z + 10)
            {
                acceleratorInput = 0;
                isBraking = true;
                brakeInput = speedBumpBrake;
            }
            Debug.Log("acc: " + acceleratorInput);
        }
        else
        {
            speedBump.SetActive(false);
            speedBump1.SetActive(false);
        }

        // CURVE
        if (mode == DRIVING_MODE.CURVE)
        {

            float decPos = 0;
            acceleratorInput = 0.8f;

            //TODO: POR OUTRA VEZ
            if (rb.velocity.z * 3.6 > 35 && !decelerating)
            {
                // Debug.Log("ai " + acceleratorInput + " || decPos " + decPos + " || pos " + rb.transform.position + " || dec " + decelerating );
                acceleratorInput = 0.5f;
                decelerating = true;
                decPos = rb.transform.position.z;
            }

            if (decelerating && rb.transform.position.z >= decPos + 10)
            {
                if (Math.Abs(rb.transform.rotation.eulerAngles.y) >= 75) steerInput = 0;
                else steerInput = 1;
                if (rb.transform.position.x > 60) isBraking = true;
            }
        }
    }

    private void HandleMotor()
    {
        if (reverse)
        {
            acceleratorInput = -acceleratorInput;
            for(int i = 0; i < 2; i++) wheelColliders[i].motorTorque = acceleratorInput * reverseMotorForce;
        }
        else
        {
            for(int i = 0; i < 2; i++) wheelColliders[i].motorTorque = acceleratorInput * motorForce;
            // for(int i = 0; i < 2; i++) wheelColliders[i].motorTorque = CalculateMotorTorque();
        }

        currentbrakeForce = 0;
        if (isBraking) currentbrakeForce = brakeForce;
        if (!isBraking && brakeInput != 0) currentbrakeForce = brakeInput * brakeForce;

        ApplyBraking();
    }


    private void ApplyBraking()
    {   
        foreach (WheelCollider wheel in wheelColliders) wheel.brakeTorque = currentbrakeForce;
    }

    private void HandleSteering()
    {
        currentSteerAngle = maxSteerAngle * steerInput;

        for(int i = 0; i < 2; i++) wheelColliders[i].steerAngle = currentSteerAngle;

        steeringWheel.transform.Rotate(maxSteeringWheelAngle * +(steerInput - previousSteerInput), 0, 0, Space.Self);
        previousSteerInput = steerInput;
    }

    private void UpdateWheels()
    {
        for(int i = 0; i < wheelColliders.Length; i++){
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

    public bool IsReverse(){ return reverse; }
}