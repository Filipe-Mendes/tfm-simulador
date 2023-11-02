using UnityEngine;

public class Manager : MonoBehaviour
{
    
    // Mode configuration
    [SerializeField] private INPUT_DEVICE inputDevice = INPUT_DEVICE.JOYSTICK;
    [SerializeField] private MODE mode = MODE.VR;
    [SerializeField] private GameObject mainCamera;
    [SerializeField] private GameObject sideCamera;
    [SerializeField] private GameObject vrRig;

    // Scene mode
    [SerializeField] private GameObject handsVisualizer;
    [SerializeField] private DRIVING_MODE drivingMode = DRIVING_MODE.FREE;
    [SerializeField] private GameObject speedBumps;

    // Logger
    [SerializeField] private bool toLog = false;
    [SerializeField] private bool toConnect = false;
    private bool triedConnection = false;
    private bool connected = false;
    [SerializeField] private GameObject loggerObject;
    private Logger logger;

    // Calibrators
    [SerializeField] private GameObject calibratorObject;
    [SerializeField] private bool toCalibrate = false;
    private bool calibrated = false;
    private SteeringWheelCalibrator steeringWheelCalibrator;

    // VehicleController
    [SerializeField] private GameObject vehicleControllerObject;
    private VehicleController vehicleController;


    private bool ready = false;
    private bool readySent = false;


    void Start()
    {
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

        // activate objects like speed bumps etc
        switch (drivingMode){
            case DRIVING_MODE.SPEED_BUMP:
                speedBumps.SetActive(true);
                break;
        }

        // Calibrator
        if(toCalibrate) {
            calibratorObject.SetActive(true);
            steeringWheelCalibrator = calibratorObject.GetComponent<SteeringWheelCalibrator>();
            steeringWheelCalibrator.toCalibrate = toCalibrate;
        }

        // Logger
        if(toLog) {
            loggerObject.SetActive(true);
            logger = loggerObject.GetComponent<Logger>();
        }


    }

    void Update()
    {
        if(!ready){
            if(toCalibrate) calibrated = steeringWheelCalibrator.IsCalibrated();


            //TODO: REFORMULAR??
            if(toConnect) {
                if(!triedConnection){
                    logger.TryConnect();
                    triedConnection = true;
                }
                connected = logger.IsConnected();
            }

            ready = (( (toCalibrate && calibrated) || !toCalibrate ) && ( (toConnect && connected) || !toConnect ));
        }
        
        if(ready && !readySent){
            // send mode to vehicleController
            vehicleController.SetUpVehicle(drivingMode, inputDevice);
            readySent = true;
        }

    }
}
