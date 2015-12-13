using UnityEngine;
using System.Collections;
using System.IO.Ports;

public class Mover : MonoBehaviour
{
	public GameObject thingToMove;
	private SerialPort serialPort = new SerialPort("\\\\.\\COM9", 9600);
	private Rigidbody rigidBodyOfThing;
    float roll, pitch;
    float ax, ay, az, mag;
    float time;



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
                else if (splitResult.Length == 10)
                {
                    try
                    {
                        time = float.Parse(splitResult[0]);
                        ax = float.Parse(splitResult[1]);
                        ay = float.Parse(splitResult[2]);
                        az = float.Parse(splitResult[3]);
                        mag = Mathf.Sqrt(Mathf.Pow(ax, 2) + Mathf.Pow(ay, 2) + Mathf.Pow(az, 2));
                        Quaternion AddRot = Quaternion.identity;



                        //roll = Mathf.Atan2(ay,ax) * 180 / Mathf.PI;
                        //pitch = Mathf.Atan2(-ax, Mathf.Sqrt(ay * ay + az * az)) * 180 / Mathf.PI;
                        roll = Mathf.Abs(Mathf.Atan2(ax/mag, az/mag) * 180 / Mathf.PI);
                        //pitch = -Mathf.Atan2(ay/mag, az/mag) * 180 / Mathf.PI;
                        AddRot.eulerAngles = new Vector3(0, 0/*yaw*/, roll);
                        rigidBodyOfThing.rotation *= AddRot;


                        //Debug.Log(result);
                        Debug.Log("roll :"+roll);
                        //Debug.Log(pitch);
                    }
                    catch
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
