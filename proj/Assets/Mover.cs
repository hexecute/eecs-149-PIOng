using UnityEngine;
using System.Collections;
using System.IO.Ports;
using UnityEngine.UI;

public class Mover : MonoBehaviour
{
	public GameObject thingToMove;
	private SerialPort serialPort = new SerialPort("\\\\.\\COM14", 9600);
	private Rigidbody rigidBodyOfThing;
	private Animation anime;

	float highestPowerLevel;
	private Text outputText1;
	private Text outputText2;

	float getTruePowerLevel(Vector3 pseudoPowerLevel)
	{
		return Vector3.Magnitude(pseudoPowerLevel) * 30000;
	}

    void Start()
	{
		serialPort.Open();
		serialPort.ReadTimeout = 100;
		highestPowerLevel = 0;

		anime = GetComponent<Animation>();

		rigidBodyOfThing = GetComponent<Rigidbody>();

		while (!serialPort.IsOpen)
		{
			Debug.Log("not connected");
		}
		serialPort.Write("r");
		outputText1 = GameObject.Find("Top Panel Text 1").GetComponent<Text>();
		outputText2 = GameObject.Find("Top Panel Text 2").GetComponent<Text>();
		outputText1.text = "Highest power level overall: " + highestPowerLevel;
		outputText2.text = "Current measured power level: 0";
	}

	void Update()
	{
		if (serialPort.IsOpen)
		{
			try
			{
				string result = serialPort.ReadLine();
				string[] splitResult = result.Split(',');

				if ((splitResult.Length == 4) && (splitResult[0].Equals("I")))
				{
					try
					{
						serialPort.Write("s");
					}
					catch (System.Exception)
					{

					}
				}

                else if (splitResult.Length == 10)
				{
					try
					{
						Vector3 pseudoPowerLevel = new Vector3(float.Parse(splitResult[0]), float.Parse(splitResult[1]), float.Parse(splitResult[2]));
						float truePowerLevel = getTruePowerLevel(pseudoPowerLevel);

						outputText2.text = "Current measured power level: " + truePowerLevel;

						if (truePowerLevel >= 6000)
						{
							anime.Play("Allosaurus_IdleAggressive");
						}

						rigidBodyOfThing.velocity = 
							new Vector3
							(
								pseudoPowerLevel.x * 1000 * float.Parse(splitResult[3]) * Time.deltaTime,
								pseudoPowerLevel.y * 1000 * float.Parse(splitResult[4]) * Time.deltaTime,
								pseudoPowerLevel.z * 1000 * float.Parse(splitResult[5]) * Time.deltaTime
							);

						rigidBodyOfThing.angularVelocity =
							new Vector3
							(
								pseudoPowerLevel.x * 5000 * float.Parse(splitResult[6]) * Time.deltaTime,
								pseudoPowerLevel.y * 5000 * float.Parse(splitResult[7]) * Time.deltaTime,
								pseudoPowerLevel.z * 5000 * float.Parse(splitResult[8]) * Time.deltaTime
							);

						if (truePowerLevel > highestPowerLevel)
						{
							highestPowerLevel = truePowerLevel;
							outputText1.text = "Highest power level overall: " + highestPowerLevel;
						}

					}
					catch
					{

					}
				}
				else
				{

				}
			}
			catch (System.Exception)
			{

			}
		}
		else
		{
			Debug.Log("DISCONNECTED");
		}
	}
}
