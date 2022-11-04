/**
 * Ardity (Serial Communication for Arduino + Unity)
 * Author: Daniel Wilches <dwilches@gmail.com>
 *
 * This work is released under the Creative Commons Attributions license.
 * https://creativecommons.org/licenses/by/2.0/
 */

using UnityEngine;
using System.Collections;
using System.Collections.Generic;

/**
 * Sample for reading using polling by yourself, and writing too.
 */
public class SampleUserPolling_ReadWrite : MonoBehaviour
{
    public SerialController serialController;
    public AudioSource voice;
    public AudioSource buttons;

    public List<AudioClip> queue = new List<AudioClip>();

    public AudioClip intro1;
    public AudioClip intro2;
    public AudioClip firstButton;
    public AudioClip comedy1;
    public AudioClip encourage;
    public AudioClip gap;
    public AudioClip choc1;
    public AudioClip choc2;
    public AudioClip zebraCry;

    public AudioClip done1;
    public AudioClip done2;
    public AudioClip done3;

    public AudioClip tutorial;
    public AudioClip hint1;
    public AudioClip hint2;
    public AudioClip hint3;

    float timer = 0;

    // Initialization
    void Start()
    {
        voice.clip = intro1;
        voice.Play();
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
            buttons.Play();
        }

        if (Input.GetKeyDown(KeyCode.A))
        {
            serialController.SendSerialMessage("2");
            buttons.Play();
        }

        if (Input.GetKeyDown(KeyCode.S))
        {
            serialController.SendSerialMessage("3");
            buttons.Play();
        }

        if (Input.GetKeyDown(KeyCode.D))
        {
            serialController.SendSerialMessage("4");
            buttons.Play();
        }

        if (Input.GetKeyDown(KeyCode.UpArrow))
        {
            serialController.SendSerialMessage("5");
            buttons.Play();
        }

        if (Input.GetKeyDown(KeyCode.DownArrow))
        {
            serialController.SendSerialMessage("6");
            buttons.Play();
        }

        if (Input.GetKeyDown(KeyCode.LeftArrow))
        {
            serialController.SendSerialMessage("7");
            buttons.Play();
        }

        if (Input.GetKeyDown(KeyCode.RightArrow))
        {
            serialController.SendSerialMessage("8");
            buttons.Play();
        }

        if (Input.GetKeyDown(KeyCode.Alpha9))
        {
            serialController.SendSerialMessage("9");
            buttons.Play();
        }

        if (Input.GetKeyDown(KeyCode.Alpha0))
        {
            serialController.SendSerialMessage("0");
            buttons.Play();
        }

        //---------------------------------------------------------------------
        // Receive data
        //---------------------------------------------------------------------

        string message = serialController.ReadSerialMessage();

        if(voice.clip != intro1 || voice.clip != intro2)
        {
            timer += Time.deltaTime;
        }

        if(timer >= 15f)
        {
            int rand = Random.Range(0, 3);

            switch(rand)
            {
                case 0:
                    queue.Add(hint1);
                    break;
                case 1:
                    queue.Add(hint2);
                    break;
                case 2:
                    queue.Add(hint3);
                    break;
            }

            timer = 0f;
        }

        if(queue.Count == 0)
        {
            int rand = Random.Range(0, 4);

            switch (rand)
            {
                case 0:
                    queue.Add(comedy1);
                    break;
                case 1:
                    queue.Add(choc1);
                    break;
                case 2:
                    queue.Add(choc2);
                    break;
                case 3:
                    queue.Add(zebraCry);
                    break;
            }
        }

        if (message == null)
        { 
            if (!voice.isPlaying && queue.Count > 0)
            {
                voice.clip = queue[0];
                queue.RemoveAt(0);
                voice.Play();
            }

            Debug.Log(queue.Count);
        }

        else
        {
            if (message.Equals("intro2"))
            {
                queue.Add(intro2);
            }

            if (message.Equals("firstButton"))
            {
                voice.clip = firstButton;
                voice.Play();

            }

            if (message.Equals("done1"))
            {
                voice.clip = done1;
                voice.Play();
                timer = 0;
            }

            if (message.Equals("done2"))
            {
                voice.clip = done2;
                voice.Play();
                timer = 0;
            }

            if (message.Equals("done3"))
            {
                voice.clip = done3;
                voice.Play();
                timer = 0;
            }
        }
        // Check if the message is plain data or a connect/disconnect event.
        if (ReferenceEquals(message, SerialController.SERIAL_DEVICE_CONNECTED))
            Debug.Log("Connection established");
        else if (ReferenceEquals(message, SerialController.SERIAL_DEVICE_DISCONNECTED))
            Debug.Log("Connection attempt failed or disconnection detected");
        else
            Debug.Log("Message arrived: " + message);
    }
}
