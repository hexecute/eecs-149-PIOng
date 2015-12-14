using UnityEngine;
using System.Collections;
using System.IO.Ports;
using UnityEngine.UI;

public class Displayer : MonoBehaviour
{

	private SerialPort serialPort = new SerialPort("\\\\.\\COM14", 9600);
	private Text outputText1;
	private Text outputText2;
	private Text outputText3;


	void Start ()
	{
		serialPort.Open();
		serialPort.ReadTimeout = 100;

		while (!serialPort.IsOpen)
		{
			Debug.Log("not connected");
		}

		outputText1 = GameObject.Find("Top Panel Text 1").GetComponent<Text>();
		outputText2 = GameObject.Find("Top Panel Text 2").GetComponent<Text>();
		outputText3 = GameObject.Find("Bottom Panel Text 2").GetComponent<Text>();

		outputText1.text = "Last Detected Stroke:";

		serialPort.Write("r");
		serialPort.Write("p");
		serialPort.Write("s");
	}
	

	void Update ()
	{
		if (serialPort.IsOpen)
		{
			try
			{
				string result = serialPort.ReadLine();
				if (result[0] == '-')
				{
					outputText2.text = result.Substring(1);
				}
			}
			catch(System.Exception)
			{

			}
		}
		else
		{
			Debug.Log("DISCONNECTED");
		}
	}
}
