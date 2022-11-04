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

    public AudioClip silence;

    public List<AudioClip> queue = new List<AudioClip>();

    public float timer = 0;
    public float silenceTimer = 0;

    // Initialization
    void Start()
    {
        queue.Add(intro1);
        queue.Add(intro2);
        queue.Add(tutorial);
        queue.Add(choc1);
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
            timer = 0;
            StopPlaying(gap);
        }

        if (Input.GetKeyDown(KeyCode.A))
        {
            serialController.SendSerialMessage("2");
            buttons.Play();
            timer = 0;
            StopPlaying(gap);
        }

        if (Input.GetKeyDown(KeyCode.S))
        {
            serialController.SendSerialMessage("3");
            buttons.Play();
            timer = 0;
            StopPlaying(gap);
        }

        if (Input.GetKeyDown(KeyCode.D))
        {
            serialController.SendSerialMessage("4");
            buttons.Play();
            timer = 0;
            StopPlaying(gap);
        }

        if (Input.GetKeyDown(KeyCode.UpArrow))
        {
            serialController.SendSerialMessage("5");
            buttons.Play();
            timer = 0;
            StopPlaying(gap);
        }

        if (Input.GetKeyDown(KeyCode.DownArrow))
        {
            serialController.SendSerialMessage("6");
            buttons.Play();
            timer = 0;
            StopPlaying(gap);
        }

        if (Input.GetKeyDown(KeyCode.LeftArrow))
        {
            serialController.SendSerialMessage("7");
            buttons.Play();
            timer = 0;
            StopPlaying(gap);
        }

        if (Input.GetKeyDown(KeyCode.RightArrow))
        {
            serialController.SendSerialMessage("8");
            buttons.Play();
            timer = 0;
            StopPlaying(gap);
        }

        if (Input.GetKeyDown(KeyCode.Alpha9))
        {
            serialController.SendSerialMessage("9");
        }

        if (Input.GetKeyDown(KeyCode.Alpha0))
        {
            serialController.SendSerialMessage("0");
        }

        //---------------------------------------------------------------------
        // Receive data
        //---------------------------------------------------------------------

        string message = serialController.ReadSerialMessage();

        if (!voice.clip.Equals(intro1) && !voice.clip.Equals(intro2) && !voice.clip.Equals(tutorial))
        {
            timer += Time.deltaTime;
            Debug.Log(!voice.isPlaying);

            if (!voice.isPlaying)
            {
                silenceTimer += Time.deltaTime;
            }
        }


        //hints timer
        if (timer >= 30f)
        {
            int rand = Random.Range(0, 4);

            switch (rand)
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
                case 3:
                    voice.clip = gap;
                    voice.Play();
                    break;
            }

            timer = 0f;
        }


        if (silenceTimer >= 20f)
        {
            int rand = Random.Range(0, 5);

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
                case 4:
                    queue.Add(encourage);
                    break;
            }

            silenceTimer = 0f;
        }

        



        if (message == null)
        { 
            if (!voice.isPlaying && queue.Count > 0)
            {
                voice.clip = queue[0];
                queue.RemoveAt(0);
                voice.Play();
            }
        }

        else
        {
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
                silenceTimer = 0;
            }

            if (message.Equals("done2"))
            {
                voice.clip = done2;
                voice.Play();
                timer = 0;
                silenceTimer = 0;
            }

            if (message.Equals("done3"))
            {
                voice.clip = done3;
                voice.Play();
                timer = 0;
                silenceTimer = 0;
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

    void StopPlaying(AudioClip clip)
    {
        if(voice.Equals(clip))
        {
            voice.Stop();
        }

        if(queue.Contains(clip))
        {
            queue.Remove(clip);
        }
    }
}
