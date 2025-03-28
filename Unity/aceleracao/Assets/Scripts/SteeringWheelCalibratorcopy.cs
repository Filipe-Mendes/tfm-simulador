using System.Collections;
using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.XR.Hands;

public class SteeringWheelCalibratorcopy : MonoBehaviour
{

/*     [SerializeField] private Transform pointA;
    [SerializeField] private Transform pointB; */
    [SerializeField] private bool mockCalibration = false;

    [SerializeField] private GameObject canvas;
    [SerializeField] private TMPro.TMP_Text timerText;

    [SerializeField] private Transform XROrigin;
    [SerializeField] private Transform mainCamera;
    [SerializeField] private Transform cameraOffset;
    [SerializeField] private GameObject vehicle;
    [SerializeField] private GameObject steeringWheel;
    [SerializeField] private int steeringWheelAngle = 45;
    [SerializeField] private float timeToCalibrate = 5000; //ms
    private bool calibrated = false;
    [HideInInspector] public bool toCalibrate = false;

    private XRHand leftHand;
    private XRHand rightHand;

    XRHandSubsystem m_HandSubsystem;
    XRHandSubsystem temp_m_HandSubsystem;
    private bool running = false;

    void Start()
    {   
        Debug.Log("Steeing wheel calibrator start start");
        if(toCalibrate) {
            canvas.SetActive(true);
            
            if(!mockCalibration){
                var handSubsystems = new List<XRHandSubsystem>();
                SubsystemManager.GetSubsystems(handSubsystems);

                for (var i = 0; i < handSubsystems.Count; ++i)
                {   
                    var handSubsystem = handSubsystems[i];
                    temp_m_HandSubsystem = handSubsystem;
                }
            }

            // Debug.Log("steering wheel activate");
            // steeringWheel.SetActive(true);
        }
        Debug.Log("Steeing wheel calibrator start end");
    }

    void FixedUpdate_mocktest()
    {   

        while (!calibrated){
            if( timeToCalibrate >= 0 ){
                timeToCalibrate -= Time.deltaTime;
                Debug.Log("time remaining: " + timeToCalibrate);
                timerText.text = ""+(int)Math.Ceiling(timeToCalibrate);
                break;
            } else {
                canvas.SetActive(false);

                calibrated = true;
            }
        }
        
    }

    //TODO: CLEANUP
    void FixedUpdate()
    {   
        if (toCalibrate && !running && temp_m_HandSubsystem.running)
        {
            if(!mockCalibration){
                m_HandSubsystem = temp_m_HandSubsystem;
                Debug.Log("Running Hand System");
            }
            running = true;
        }

        if(running){
            Debug.Log("running");
            while (!calibrated){
                if( timeToCalibrate >= 0 ){
                    timeToCalibrate -= Time.deltaTime;
                    Debug.Log("time remaining: " + timeToCalibrate);
                    timerText.text = ""+(int)Math.Ceiling(timeToCalibrate);
                    break;
                } else {
                    canvas.SetActive(false);
                    
                    // Timer ended, calibrate wheel
                    leftHand = m_HandSubsystem.leftHand;
                    rightHand = m_HandSubsystem.rightHand;
                    
                    Debug.Log("lh: " + leftHand);
                    Debug.Log("rh: " + rightHand);

                    XRHandJoint lj = leftHand.GetJoint(XRHandJointID.IndexTip);
                    XRHandJoint rj = rightHand.GetJoint(XRHandJointID.IndexTip);

                    Pose xrOriginPose = new Pose(XROrigin.position, XROrigin.rotation);

                    Pose lp = xrOriginPose;
                    Pose rp = xrOriginPose;

                    bool lpb = lj.TryGetPose(out lp);
                    bool rpb = rj.TryGetPose(out rp);
                    
                    if(lpb && rpb) Debug.Log("!! lp: " + lp.position + " || rp: " + rp.position);

                    lp = lp.GetTransformedBy(xrOriginPose);
                    rp = rp.GetTransformedBy(xrOriginPose);

                    if(lpb && rpb) Debug.Log("lp: " + lp.position + " || rp: " + rp.position);

                    /* Transform lp = pointA;
                    Transform rp = pointB; */

                    //////////////////////////////////////
                    /* Vector3 steeringWheelCenter = (lp.position + rp.position)/2;
                    Debug.Log("c: " + steeringWheelCenter);

                    steeringWheel.transform.position = steeringWheelCenter + new Vector3(0,1.1176f,0); //TODO: CHANGE TO CAMERA OFFSET https://docs.unity3d.com/Packages/com.unity.xr.hands@1.3/api/UnityEngine.XR.Hands.XRHandDevice.html

                    float radius = Vector3.Distance(lp.position, rp.position)/2;
                    Debug.Log("r: " + radius);

                    newScale(steeringWheel, radius * 2);

                    Debug.Log("ls: " + steeringWheel.transform.localScale); */
                    //////////////////////////////////////
                    Vector3 steeringWheelCenter = lp.position;
                    Debug.Log("c: " + steeringWheelCenter);

                    steeringWheel.transform.position = steeringWheelCenter + new Vector3(0, cameraOffset.position.y, 0); //TODO: CHANGE TO CAMERA OFFSET https://docs.unity3d.com/Packages/com.unity.xr.hands@1.3/api/UnityEngine.XR.Hands.XRHandDevice.html

                    float radius = Vector3.Distance(lp.position, rp.position);
                    Debug.Log("r: " + radius);

                    NewScale(steeringWheel, radius * 2);

                    Debug.Log("ls: " + steeringWheel.transform.localScale);



                    // steeringWheel.transform.LookAt(mainCamera, Vector3.right);

                    /* Quaternion currentRotation = steeringWheel.transform.rotation;
                    currentRotation.x = steeringWheelAngle;
                    Debug.Log("cr: " + currentRotation); */
                    // steeringWheel.transform.rotation = currentRotation;
                    // steeringWheel.transform.rotation = Quaternion.Euler(steeringWheelAngle, currentRotation.y, currentRotation.z);
                    Vector3 relativePos = mainCamera.position - steeringWheel.transform.position;

                    // the second argument, upwards, defaults to Vector3.up
                    Quaternion rotation = Quaternion.LookRotation(relativePos, new Vector3(1,0,0));
                    Debug.Log("rotation: " + rotation);
                /*  Quaternion tiltRotation = Quaternion.Euler(45, 0, 0);
                    Debug.Log("tilt: " + tiltRotation);
                    steeringWheel.transform.rotation = rotation * tiltRotation;
                    Debug.Log("ROT * tilt: " + rotation * tiltRotation); */
                    steeringWheel.transform.rotation = rotation;

                    var rot = steeringWheel.transform.localRotation.eulerAngles;
                    Debug.Log("rot: " + rot);
                    rot.Set(steeringWheelAngle, rot.y, rot.z);
                    steeringWheel.transform.localRotation = Quaternion.Euler(rot);


                    //steeringWheel.transform.Rotate(steeringWheelAngle, 0.0f, 0.0f, Space.Self);

                    // steeringWheel.transform.rotation = new Vector3(currentRotation.x, currentRotation.y, currentRotation.z);

                    // steeringWheel.transform.rotation = Quaternion.Euler(steeringWheelAngle, currentRotation.y, currentRotation.z);

                    /* var lookPos = mainCamera.position - steeringWheel.transform.position;
                    lookPos.y = 0;
                    var rotation = Quaternion.LookRotation(lookPos);
                    steeringWheel.transform.rotation = Quaternion.Slerp(steeringWheel.transform.rotation, rotation, 0); */ 
                    // steeringWheel.transform.rotation = new Vector3(steeringWheel.transform.rotation.x, 180, 45);

                    //modifying the Vector3, based on input multiplied by speed and time
                    // Vector3 currentEulerAngles = new Vector3(steeringWheel.transform.rotation.x, 180, 45) * Time.deltaTime * 1000;

                    //moving the value of the Vector3 into Quanternion.eulerAngle format
                    // Quaternion currentRotation = new Quaternion(0,0,0,0);
                    // currentRotation.eulerAngles = currentEulerAngles;

                    //apply the Quaternion.eulerAngles change to the gameObject
                    // steeringWheel.transform.rotation = currentRotation;


                    // Makes the steering wheel keep up with the vehicle
                    steeringWheel.transform.SetParent(vehicle.transform);

                    Debug.Log("calibrated " + steeringWheelCenter);
                    calibrated = true;
                }
            }
        }
    }

    public bool IsCalibrated(){
        return calibrated;
    }

    public void NewScale(GameObject theGameObject, float newSize) {

        float sizey = theGameObject.GetComponent<Renderer>().bounds.size.y;
        float sizez = theGameObject.GetComponent<Renderer>().bounds.size.z;

        Vector3 rescale = theGameObject.transform.localScale;

        rescale.y = newSize * rescale.y / sizey;
        rescale.z = newSize * rescale.z / sizez;

        theGameObject.transform.localScale = rescale;
    }
}