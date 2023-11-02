using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;


public class InputTest : MonoBehaviour
{
    private PlayerInput userInput;
    private InputAction testAction;
    // Start is called before the first frame update
    void Start()
    {
        userInput = GetComponent<PlayerInput>();
        userInput.neverAutoSwitchControlSchemes = true;
        userInput.SwitchCurrentControlScheme("Gamepad", Gamepad.all[0]);
        testAction = userInput.actions["Test"];

    }

    // Update is called once per frame
    void Update()
    {
        Debug.Log("in: " + testAction.ReadValue<float>());
    }
}
