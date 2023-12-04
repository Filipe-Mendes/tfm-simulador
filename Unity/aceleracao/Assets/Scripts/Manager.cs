using UnityEngine;

public class Manager : MonoBehaviour
{
    // UI
    [SerializeField] private bool showUI = true;
    [SerializeField] GameObject canvasUI;
    [HideInInspector] public bool startPressed = false;

    // Mode configuration
    [SerializeField] public INPUT_DEVICE inputDevice = INPUT_DEVICE.JOYSTICK;
    [SerializeField] public MODE mode = MODE.VR;
    [SerializeField] private GameObject mainCamera;
    [SerializeField] private GameObject sideCamera;
    [SerializeField] private GameObject vrRig;

    // Scene mode
    [SerializeField] private GameObject handsVisualizer;
    [SerializeField] public DRIVING_MODE drivingMode = DRIVING_MODE.FREE;
    [SerializeField] private GameObject speedBumps;

    // Logger
    [SerializeField] public bool toLog = false;
    [SerializeField] public bool toConnect = false;
    private bool triedConnection = false;
    private bool connected = false;
    [SerializeField] private GameObject loggerObject;
    private Logger logger;

    // Calibrators
    [SerializeField] private GameObject calibratorObject;
    [SerializeField] public bool toCalibrate = false;
    private bool calibrated = false;
    private SteeringWheelCalibrator steeringWheelCalibrator;

    // VehicleController
    [SerializeField] private GameObject vehicleControllerObject;
    private VehicleController vehicleController;

    private bool ready = false;
    private bool readySent = false;
    private bool setUpFinished = false;


    void Start()
    {
        if(!showUI){
            canvasUI.SetActive(false);
            SetUpScene();
        } else {
            canvasUI.SetActive(true);
        }
    }

    void SetUpScene(){
        Debug.Log("Set up scene on Manager");
        // Mode
        switch (mode){
            case MODE.SCREEN:
                mainCamera.SetActive(true);
                sideCamera.SetActive(true);
                vrRig.SetActive(false);
                break;
            case MODE.VR:
                mainCamera.SetActive(false);
                sideCamera.SetActive(false);
                vrRig.SetActive(true);
                break;
        }

        // Driving Mode
        vehicleController = vehicleControllerObject.GetComponent<VehicleController>();
        if(drivingMode != DRIVING_MODE.FREE) handsVisualizer.SetActive(false);

        // Activate objects like speed bumps etc
        switch (drivingMode){
            case DRIVING_MODE.SPEED_BUMP:
                speedBumps.SetActive(true);
                break;
        }

        // Calibrator
        if(toCalibrate) {
            calibratorObject.SetActive(true);
            steeringWheelCalibrator = calibratorObject.GetComponent<SteeringWheelCalibrator>();
            steeringWheelCalibrator.toCalibrate = toCalibrate;  //TODO: PASSAR PARA ANTES DA ATIVAÇAO
        }

        // Logger
        if(toLog) {
            loggerObject.SetActive(true);
            logger = loggerObject.GetComponent<Logger>();
        }

        setUpFinished = true;
    }

    void Update()
    {
        if (showUI && startPressed && !setUpFinished){
            SetUpScene();
            // startPressed = true;
        }

        if(!ready && setUpFinished){
            if(toCalibrate) calibrated = steeringWheelCalibrator.IsCalibrated();


            //TODO: REFORMULAR??
            if(toConnect) {
                if(!triedConnection){
                    logger.TryConnect();
                    triedConnection = true;
                }
                connected = logger.IsConnected();
                if (!connected) Debug.Log("Error! Could not connect to platform!");
            }

            ready = ( (toCalibrate && calibrated) || !toCalibrate ) && ( (toConnect && connected) || !toConnect );
        }
        
        if(ready && !readySent && setUpFinished){
            // send mode to vehicleController
            vehicleController.SetUpVehicle(drivingMode, inputDevice);
            readySent = true;
        }

    }
}
