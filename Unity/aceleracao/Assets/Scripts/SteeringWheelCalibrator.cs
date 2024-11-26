using System.Collections;
using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.XR.Hands;

public class SteeringWheelCalibrator : MonoBehaviour
{

    /*     [SerializeField] private Transform pointA;
        [SerializeField] private Transform pointB; */
    [SerializeField] private bool mockCalibration = false;
    [SerializeField] private GameObject clp;
    [SerializeField] private GameObject crp;
    [SerializeField] private GameObject head;

    [SerializeField] private GameObject canvas;
    [SerializeField] private TMPro.TMP_Text timerText;

    [SerializeField] private Transform XROrigin;
    [SerializeField] private Transform mainCamera;
    [SerializeField] private Transform cameraOffset;
    [SerializeField] private GameObject vehicle;
    [SerializeField] private GameObject steeringWheel;
    [SerializeField] private int steeringWheelAngle = 45;
    [SerializeField] private float timeToCalibrate = 10; //s
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
        if (toCalibrate)
        {
            canvas.SetActive(true);

            if (!mockCalibration)
            {
                var handSubsystems = new List<XRHandSubsystem>();
                SubsystemManager.GetSubsystems(handSubsystems);

                for (var i = 0; i < handSubsystems.Count; ++i)
                {
                    var handSubsystem = handSubsystems[i];
                    temp_m_HandSubsystem = handSubsystem;
                }
            }

            // Debug.Log("steering wheel activate");
            steeringWheel.SetActive(true);
        }
        Debug.Log("Steeing wheel calibrator start end");
    }

    /*
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
    */
    //TODO: CLEANUP
    void FixedUpdateOld()
    {
        if (toCalibrate && !running && temp_m_HandSubsystem.running)
        {
            if (!mockCalibration)
            {
                m_HandSubsystem = temp_m_HandSubsystem;
                Debug.Log("Running Hand System");
            }
            running = true;
        }

        if (running)
        {
            while (!calibrated)
            {
                if (timeToCalibrate >= 0)
                {
                    timeToCalibrate -= Time.deltaTime; // deltaTime is in seconds
                    Debug.Log("time remaining: " + timeToCalibrate);
                    timerText.text = "" + (int)Math.Ceiling(timeToCalibrate);
                    // break;
                }
                else
                {
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

                    if (lpb && rpb) Debug.Log("!! lp: " + lp.position + " || rp: " + rp.position);


                    /////////// 25 11
                    Vector3 lpp = transform.TransformPoint(lp.position);
                    Vector3 rpp = transform.TransformPoint(rp.position);

                    if (lpb && rpb) Debug.Log("! lpp: " + lpp + " || rpp: " + rpp);

                    //lp = lp.GetTransformedBy(xrOriginPose);
                    //rp = rp.GetTransformedBy(xrOriginPose);

                    //if(lpb && rpb) Debug.Log("lp: " + lp.position + " || rp: " + rp.position);

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

                    // Vector3 steeringWheelCenter = lp.position;
                    //2511
                    Vector3 steeringWheelCenter = lpp;
                    Debug.Log("c: " + steeringWheelCenter);

                    steeringWheel.transform.position = steeringWheelCenter;
                    // 2511  + new Vector3(0, cameraOffset.position.y, 0); //TODO: CHANGE TO CAMERA OFFSET https://docs.unity3d.com/Packages/com.unity.xr.hands@1.3/api/UnityEngine.XR.Hands.XRHandDevice.html

                    //2511
                    // float radius = Vector3.Distance(lp.position, rp.position);
                    float radius = Vector3.Distance(lpp, rpp);
                    Debug.Log("r: " + radius);

                    NewScale(steeringWheel, radius * 2);

                    Debug.Log("ls: " + steeringWheel.transform.localScale);



                    // steeringWheel.transform.LookAt(mainCamera, Vector3.right);

                    /* Quaternion currentRotation = steeringWheel.transform.rotation;
                    currentRotation.x = steeringWheelAngle;
                    Debug.Log("cr: " + currentRotation); */
                    // steeringWheel.transform.rotation = currentRotation;
                    // steeringWheel.transform.rotation = Quaternion.Euler(steeringWheelAngle, currentRotation.y, currentRotation.z);
                    // 2511 Vector3 relativePos = mainCamera.position - steeringWheel.transform.position;

                    // the second argument, upwards, defaults to Vector3.up
                    // 2511 Quaternion rotation = Quaternion.LookRotation(relativePos, new Vector3(1,0,0));
                    // 2511 Debug.Log("rotation: " + rotation);
                    /*  Quaternion tiltRotation = Quaternion.Euler(45, 0, 0);
                        Debug.Log("tilt: " + tiltRotation);
                        steeringWheel.transform.rotation = rotation * tiltRotation;
                        Debug.Log("ROT * tilt: " + rotation * tiltRotation); */
                    //2511 steeringWheel.transform.rotation = rotation;

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

    void FixedUpdate8()
    {
        if (!mockCalibration && toCalibrate && !running && temp_m_HandSubsystem.running)
        {
            if (!mockCalibration)
            {
                m_HandSubsystem = temp_m_HandSubsystem;
                Debug.Log("Running Hand System");
            }
            running = true;
        } else {
            running = true;
        }

        if (running)
        {
            while (!calibrated)
            {
                if (timeToCalibrate >= 0)
                {
                    timeToCalibrate -= Time.deltaTime; // deltaTime is in seconds
                    Debug.Log("time remaining: " + timeToCalibrate);
                    timerText.text = "" + (int)Math.Ceiling(timeToCalibrate);
                    break;
                }
                else
                {
                    canvas.SetActive(false);

                    if(!mockCalibration){

                        // Timer ended, calibrate wheel
                        leftHand = m_HandSubsystem.leftHand;
                        rightHand = m_HandSubsystem.rightHand;

                        XRHandJoint lj = leftHand.GetJoint(XRHandJointID.IndexTip);
                        XRHandJoint rj = rightHand.GetJoint(XRHandJointID.IndexTip);

                        // TO REPLACE NULL
                        Pose xrOriginPose = new Pose(XROrigin.position, XROrigin.rotation);
                        Pose lp = xrOriginPose;
                        Pose rp = xrOriginPose;

                        bool lpb = lj.TryGetPose(out lp);
                        bool rpb = rj.TryGetPose(out rp);

                        // LP / RP -> POSES OF THE INDEX FINGERS                    
                        if (lpb && rpb) Debug.Log("!! lp: " + lp.position + " || rp: " + rp.position);
                    


                        // TRANSFORMED INTO WORLD SPACE
                        // c2611
                        // lp = lp.GetTransformedBy(xrOriginPose);
                        // rp = rp.GetTransformedBy(xrOriginPose);
                        // if (lpb && rpb) Debug.Log("! lp: " + lp + " || rp: " + rp);


                        // LEFT FINGER POINTS TO THE CENTER OF THE STEERING WHEEL, REPOSITION SW
                        //Vector3 steeringWheelCenter = lp.position;
                    }

                    Vector3 steeringWheelCenter = clp.transform.position;
                    
                    
                    Debug.Log("c: " + steeringWheelCenter);
                    steeringWheel.transform.position = steeringWheelCenter;

                    // THE RADIUS OF THE SW IS GIVEN BY THE DISTANCE BETWEEN THE LEFT AND RIGHT FINGER
                    // c26 float radius = Vector3.Distance(lp.position, rp.position);
                    float radius = Vector3.Distance(clp.transform.position, crp.transform.position);
                    Debug.Log("r: " + radius);

                    // SCALE THE SW ACCORDING TO THE RADIUS
                    NewScale(steeringWheel, radius * 2);

                    Vector3 directionToHead = head.transform.position - clp.transform.position;

                    // Flatten the direction vector onto the XZ-plane
                    directionToHead.y = 0;

                    // Calculate the Y-axis rotation to face the head
                    Quaternion tiltRotation = Quaternion.Euler(0, 0, 45);
                    Quaternion lookAtHead = Quaternion.LookRotation(directionToHead);

                    // Combine the rotation with the desired Z-axis tilt (e.g., 45 degrees)
                    Quaternion finalRotation = lookAtHead * tiltRotation; //* Quaternion.Euler(0, 90, 0);;
                    finalRotation.eulerAngles = new Vector3(finalRotation.eulerAngles.x, 90, finalRotation.eulerAngles.z);

                    // Apply the rotation to the disk
                    // disk.transform.position = lf; // Set the position
                    // disk.transform.localScale = new Vector3(radius * 2, disk.transform.localScale.y, radius * 2); // Scale the disk
                    steeringWheel.transform.rotation = finalRotation;



                    // 2511  + new Vector3(0, cameraOffset.position.y, 0); //TODO: CHANGE TO CAMERA OFFSET https://docs.unity3d.com/Packages/com.unity.xr.hands@1.3/api/UnityEngine.XR.Hands.XRHandDevice.html

                    // steeringWheel.transform.LookAt(mainCamera, Vector3.right);

                    /* Quaternion currentRotation = steeringWheel.transform.rotation;
                    currentRotation.x = steeringWheelAngle;
                    Debug.Log("cr: " + currentRotation); */
                    // steeringWheel.transform.rotation = currentRotation;
                    // steeringWheel.transform.rotation = Quaternion.Euler(steeringWheelAngle, currentRotation.y, currentRotation.z);
                    // 2511 Vector3 relativePos = mainCamera.position - steeringWheel.transform.position;

                    // the second argument, upwards, defaults to Vector3.up
                    // 2511 Quaternion rotation = Quaternion.LookRotation(relativePos, new Vector3(1,0,0));
                    // 2511 Debug.Log("rotation: " + rotation);
                    /*  Quaternion tiltRotation = Quaternion.Euler(45, 0, 0);
                        Debug.Log("tilt: " + tiltRotation);
                        steeringWheel.transform.rotation = rotation * tiltRotation;
                        Debug.Log("ROT * tilt: " + rotation * tiltRotation); */
                    //2511 steeringWheel.transform.rotation = rotation;




                    // var rot = steeringWheel.transform.localRotation.eulerAngles;
                    // Debug.Log("rot: " + rot);
                    // rot.Set(steeringWheelAngle, rot.y, rot.z);
                    // steeringWheel.transform.localRotation = Quaternion.Euler(rot);




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
                    // Debug.Log("calibrated " + steeringWheelCenter);
                    calibrated = true;
                }
            }
        }
    }

    void FixedUpdate()
    {
        if (!mockCalibration && toCalibrate && !running && temp_m_HandSubsystem.running)
        {
            if (!mockCalibration)
            {
                m_HandSubsystem = temp_m_HandSubsystem;
                Debug.Log("Running Hand System");
            }
            running = true;
        } else {
            running = true;
        }

        if (running)
        {
            while (!calibrated)
            {
                if (timeToCalibrate >= 0)
                {
                    timeToCalibrate -= Time.deltaTime; // deltaTime is in seconds
                    Debug.Log("time remaining: " + timeToCalibrate);
                    timerText.text = "" + (int)Math.Ceiling(timeToCalibrate);
                    break;
                }
                else
                {
                    canvas.SetActive(false);

                    if(!mockCalibration){

                        // Timer ended, calibrate wheel
                        leftHand = m_HandSubsystem.leftHand;
                        rightHand = m_HandSubsystem.rightHand;

                        XRHandJoint lj = leftHand.GetJoint(XRHandJointID.IndexTip);
                        XRHandJoint rj = rightHand.GetJoint(XRHandJointID.IndexTip);

                        // TO REPLACE NULL
                        Pose xrOriginPose = new Pose(XROrigin.position, XROrigin.rotation);
                        Pose lp = xrOriginPose;
                        Pose rp = xrOriginPose;

                        bool lpb = lj.TryGetPose(out lp);
                        bool rpb = rj.TryGetPose(out rp);

                        // LP / RP -> POSES OF THE INDEX FINGERS                    
                        if (lpb && rpb) Debug.Log("!! lp: " + lp.position + " || rp: " + rp.position);
                    



                        // LEFT FINGER POINTS TO THE CENTER OF THE STEERING WHEEL, REPOSITION SW
                        //Vector3 steeringWheelCenter = lp.position;
                    }

                    Vector3 steeringWheelCenter = clp.transform.position;
                    
                    
                    Debug.Log("c: " + steeringWheelCenter);
                    steeringWheel.transform.position = steeringWheelCenter;

                    // THE RADIUS OF THE SW IS GIVEN BY THE DISTANCE BETWEEN THE LEFT AND RIGHT FINGER
                    // c26 float radius = Vector3.Distance(lp.position, rp.position);
                    float radius = Vector3.Distance(clp.transform.position, crp.transform.position);
                    Debug.Log("r: " + radius);

                    // SCALE THE SW ACCORDING TO THE RADIUS
                    NewScale(steeringWheel, radius * 2);

                    Vector3 directionToHead = head.transform.position - clp.transform.position;

                    // Flatten the direction vector onto the XZ-plane
                    directionToHead.y = 0;

                    // Calculate the Y-axis rotation to face the head
                    Quaternion tiltRotation = Quaternion.Euler(0, 0, 45);
                    Quaternion lookAtHead = Quaternion.LookRotation(directionToHead);

                    // Combine the rotation with the desired Z-axis tilt (e.g., 45 degrees)
                    Quaternion finalRotation = lookAtHead * tiltRotation; //* Quaternion.Euler(0, 90, 0);;
                    finalRotation.eulerAngles = new Vector3(finalRotation.eulerAngles.x, 90, finalRotation.eulerAngles.z);

                    steeringWheel.transform.rotation = finalRotation;


                    steeringWheel.transform.SetParent(vehicle.transform);
                    calibrated = true;
                }
            }
        }
    }

    public bool IsCalibrated()
    {
        return calibrated;
    }

    public void NewScale(GameObject theGameObject, float newSize)
    {

        float sizey = theGameObject.GetComponent<Renderer>().bounds.size.y;
        float sizez = theGameObject.GetComponent<Renderer>().bounds.size.z;

        Vector3 rescale = theGameObject.transform.localScale;

        rescale.y = newSize * rescale.y / sizey;
        rescale.z = newSize * rescale.z / sizez;

        theGameObject.transform.localScale = rescale;
    }
}
