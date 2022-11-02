/**
 * Ardity (Serial Communication for Arduino + Unity)
 * Author: Daniel Wilches <dwilches@gmail.com>
 *
 * This work is released under the Creative Commons Attributions license.
 * https://creativecommons.org/licenses/by/2.0/
 */

using UnityEngine;
using System.Collections;

/**
 * Sample for reading using polling by yourself, and writing too.
 */
public class SampleUserPolling_ReadWrite : MonoBehaviour
{
    public SerialController serialController;

    // Initialization
    void Start()
    {
        serialController = GameObject.Find("SerialController").GetComponent<SerialController>();

        Debug.Log("Find the correct code");
    }

    // Executed each frame
    void Update()
    {
        //---------------------------------------------------------------------
        // Send data
        //---------------------------------------------------------------------

        // If you press one of these keys send it to the serial device. A
        // sample serial device that accepts this input is given in the README.
        if (Input.GetKeyDown(KeyCode.W))
        {
            serialController.SendSerialMessage("1");
        }

        if (Input.GetKeyDown(KeyCode.A))
        {
            serialController.SendSerialMessage("2");
        }

        if(Input.GetKeyDown(KeyCode.S))
        {
            serialController.SendSerialMessage("3");
        }

        if (Input.GetKeyDown(KeyCode.D))
        {
            serialController.SendSerialMessage("4");
        }

        if (Input.GetKeyDown(KeyCode.UpArrow))
        {
            serialController.SendSerialMessage("5");
        }

        if (Input.GetKeyDown(KeyCode.DownArrow))
        {
            serialController.SendSerialMessage("6");
        }

        if (Input.GetKeyDown(KeyCode.RightArrow))
        {
            serialController.SendSerialMessage("7");
        }

        if (Input.GetKeyDown(KeyCode.LeftArrow))
        {
            serialController.SendSerialMessage("8");
        }

        if (Input.GetKeyDown(KeyCode.Z))
        {
            serialController.SendSerialMessage("0");
            Debug.Log("Sent");

        }

        //---------------------------------------------------------------------
        // Receive data
        //---------------------------------------------------------------------

        string message = serialController.ReadSerialMessage();

        if (message == null)
            return;

        // Check if the message is plain data or a connect/disconnect event.
        if (ReferenceEquals(message, SerialController.SERIAL_DEVICE_CONNECTED))
            Debug.Log("Connection established");
        else if (ReferenceEquals(message, SerialController.SERIAL_DEVICE_DISCONNECTED))
            Debug.Log("Connection attempt failed or disconnection detected");
        else
            Debug.Log("Message arrived: " + message);
    }
}
