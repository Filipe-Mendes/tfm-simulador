using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UI : MonoBehaviour
{
    [SerializeField] private GameObject canvas;
    [SerializeField] private GameObject managerObject;
    private Manager manager;

    Toggle platformToggle;
    Toggle loggerToggle;
    Toggle calibrateswToggle;

    TMPro.TMP_Dropdown modeDropdown;
    TMPro.TMP_Dropdown inputDropdown;
    TMPro.TMP_Dropdown cameraDropdown;

    Button startButton;

    void Start()
    {
        manager = managerObject.GetComponent<Manager>();
      
        platformToggle = GameObject.Find("Platform Toggle").GetComponent<Toggle>();
        loggerToggle = GameObject.Find("Logger Toggle").GetComponent<Toggle>();
        calibrateswToggle = GameObject.Find("Calibrator Toggle").GetComponent<Toggle>();

        modeDropdown = GameObject.Find("Mode Dropdown").GetComponent<TMPro.TMP_Dropdown>();
        inputDropdown = GameObject.Find("Input Dropdown").GetComponent<TMPro.TMP_Dropdown>();
        cameraDropdown = GameObject.Find("Camera Dropdown").GetComponent<TMPro.TMP_Dropdown>();

        startButton = GameObject.Find("Start Button").GetComponent<Button>();
        startButton.onClick.AddListener(Clicked);
    }

    void Clicked(){
        manager.toLog = loggerToggle.isOn;
        manager.toConnect = platformToggle.isOn;
        manager.toCalibrate = calibrateswToggle.isOn;

        manager.mode = (MODE)cameraDropdown.value;
        manager.drivingMode = (DRIVING_MODE)modeDropdown.value;
        manager.inputDevice = (INPUT_DEVICE)inputDropdown.value;

        canvas.SetActive(false);

        manager.startPressed = true;

        Debug.Log("Start pressed on UI");
    }

    void Update()
    {
        // Debug.Log(platformToggle.isOn + "||" + loggerToggle.isOn + "||" + calibrateswToggle.isOn);
        // Debug.Log(modeDropdown.value + "||" + (DRIVING_MODE)modeDropdown.value + "!!" + inputDropdown.value + "||" + cameraDropdown.value );
    }
}
