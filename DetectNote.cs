using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using UnityEngine;
//DIG3878
//FinalProject
//Nicole Ter Doest, Amanda Machado, Joanna Mijares
public class DetectNote : MonoBehaviour
{
    bool key1 = false, key2 = false, key3 = false, key4 = false, key5 = false, key6 = false, key7 = false;

    public AudioClip firstthirdNote;
    public AudioClip secondNote;
    public AudioClip fourthNote;
    public AudioClip fifthNote;
    public AudioClip sixthNote;
    public AudioClip lastNote;

    public AudioClip wrongNote;
    public AudioClip winningTune;

    public GameObject green1;
    public GameObject green2;
    public GameObject green3;
    public GameObject green4;
    public GameObject green5;
    public GameObject green6;
    public GameObject green7;

    public GameObject musicsheetSOLID;
    public GameObject musicsheetANIM;


    void OnCollisionEnter2D(UnityEngine.Collision2D collision)
    {
        if (collision.gameObject.tag == "Note1/3")
        {
            key1 = true;
            green1.SetActive(true);
            StartCoroutine(DelayColor());
            AudioSource.PlayClipAtPoint(firstthirdNote, transform.position);
        }

        if (collision.gameObject.tag == "Note1/3" && key2)
        {
            green3.SetActive(true);
            StartCoroutine(DelayColor());
            key3 = true;
            AudioSource.PlayClipAtPoint(firstthirdNote, transform.position);
        }
        if (collision.gameObject.tag == "Note2")
        {
           
            green2.SetActive(true);
            StartCoroutine(DelayColor());
            AudioSource.PlayClipAtPoint(secondNote, transform.position);
        }
        if (collision.gameObject.tag == "Note2" && key1)
        {
            key2 = true;
            
        }

        if (collision.gameObject.tag == "Note4")
        {
            green4.SetActive(true);
            StartCoroutine(DelayColor());
            AudioSource.PlayClipAtPoint(fourthNote, transform.position);
        }
        if (collision.gameObject.tag == "Note4" && key3)
        {
            key4 = true;
        }
        if (collision.gameObject.tag == "Note5")
        {
            green5.SetActive(true);
            StartCoroutine(DelayColor());
            AudioSource.PlayClipAtPoint(fifthNote, transform.position);
        }
        if (collision.gameObject.tag =="Note5"&& key4)
        {
            key5 = true;
        }

        if (collision.gameObject.tag == "Note6")
        {
            green6.SetActive(true);
            StartCoroutine(DelayColor());
            AudioSource.PlayClipAtPoint(sixthNote, transform.position);
        }
        if (collision.gameObject.tag == "Note6" && key5)
        {
            key6 = true;
        }

        if (collision.gameObject.tag == "Note7")
        {
            green7.SetActive(true);
            StartCoroutine(DelayColor());
            AudioSource.PlayClipAtPoint(lastNote, transform.position);
        }
        if (collision.gameObject.tag == "Note7" && key6)
        {
            key7 = true;
        }

        if (collision.gameObject.tag == "wrong")
        {
            key1 = false;
            key2 = false;
            key3 = false;
            key4 = false;
            key5 = false;
            key6 = false;
            key7 = false;

            AudioSource.PlayClipAtPoint(wrongNote, transform.position);
        }

        if (key7)
        {
            AudioSource.PlayClipAtPoint(winningTune, transform.position);
            green1.SetActive(true);
            green2.SetActive(true);
            green3.SetActive(true);
            green4.SetActive(true);
            green5.SetActive(true);
            green6.SetActive(true);
            green7.SetActive(true);

            musicsheetANIM.SetActive(true);
            musicsheetSOLID.SetActive(false);

        }

    }

    IEnumerator DelayColor()
    {
        yield return new WaitForSeconds(1);
        green1.SetActive(false);
        green2.SetActive(false);
        green3.SetActive(false);
        green4.SetActive(false);
        green5.SetActive(false);
        green6.SetActive(false);
        green7.SetActive(false);

    }
}

