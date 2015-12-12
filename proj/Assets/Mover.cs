using UnityEngine;
using System.Collections;
using System.IO.Ports;

public class Mover : MonoBehaviour
{
	public GameObject thingToMove;
	private SerialPort serialPort = new SerialPort("\\\\.\\COM8", 9600);
	private Rigidbody rigidBodyOfThing;

	void Start()
	{
		serialPort.Open();
		serialPort.ReadTimeout = 100;

		rigidBodyOfThing = GetComponent<Rigidbody>();

		while (!serialPort.IsOpen)
		{
			Debug.Log("not connected");
		}
		serialPort.Write("r");
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
						thingToMove.transform.rotation =
							Quaternion.Euler
							(
								float.Parse(splitResult[1]),
								float.Parse(splitResult[2]),
								float.Parse(splitResult[3])
							);
						Debug.Log(result);
						serialPort.Write("s");
					}
					catch (System.Exception)
					{

					}
				}

				else if (splitResult.Length == 7)
				{
					try
					{

						rigidBodyOfThing.velocity = 
							new Vector3
							(
								5 * 9.8f * float.Parse(splitResult[0]) * Time.deltaTime,
								5 * 9.8f * float.Parse(splitResult[1]) * Time.deltaTime,
								5 * 9.8f * float.Parse(splitResult[2]) * Time.deltaTime
							);

						rigidBodyOfThing.angularVelocity =
							new Vector3
							(
								50 * float.Parse(splitResult[3]) * Time.deltaTime,
								50 * float.Parse(splitResult[4]) * Time.deltaTime,
								50 * float.Parse(splitResult[5]) * Time.deltaTime
							);


						Debug.Log(result);
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
