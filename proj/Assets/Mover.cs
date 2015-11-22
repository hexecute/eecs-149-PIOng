using UnityEngine;
using System.Collections;
using System.IO.Ports;

public class Mover : MonoBehaviour
{
	public GameObject thingToMove;
	private SerialPort serialPort = new SerialPort("\\\\.\\COM11", 9600);

	void Start()
	{
		serialPort.Open();
		serialPort.ReadTimeout = 1;
	}

	void Update()
	{
		if (serialPort.IsOpen)
		{
			try
			{
				string result = serialPort.ReadLine();
				string[] splitResult = result.Split(',');
				if (splitResult.Length == 3)
				{
					try
					{
						thingToMove.transform.Rotate
							(
								int.Parse(splitResult[0]), int.Parse(splitResult[1]), int.Parse(splitResult[2])
							);
						Debug.Log(splitResult[0] + ", " + splitResult[1] + ", " + splitResult[2]);
					}
					catch (System.Exception)
					{

					}
				}
			}
			catch (System.Exception)
			{

			}
		}
		else
		{

		}
	}
}
