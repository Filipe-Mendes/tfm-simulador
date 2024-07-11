using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BlockController : MonoBehaviour
{
    [SerializeField] private float movementSpeed = 5.0f;

    void Start()
    {
        
    }

    void FixedUpdate()
    {
        transform.position += transform.forward * Time.deltaTime * movementSpeed;

    }
}
