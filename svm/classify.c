static float drive[ 30 ] = {
-0.45,
-10.71,
-3.9,
3.23,
-3.47,
-46.48,
-0.470813212259,
-9.48840676812,
-4.66663848521,
107.479993289,
-117.012193597,
-126.672533461,
2.26477041946,
-21.5133333523,
-1.4776744926,
88.4697588697,
5.2776016115,
-55.4063724691,
-0.581141259371,
-7.93894033404,
-4.06835177701,
-45.0491805292,
94.0942960477,
405.40743997,
-0.08,
-10.57,
-3.45,
15.16,
-50.26,
-69.2,
};

static float forehand[ 30 ] = {
-5.25,
-2.14,
-2.47,
36.38,
50.46,
24.12,
1.60653426691,
1.0443168107,
-1.02926656983,
-86.9682368345,
626.811839195,
-186.969748739,
-6.07982927551,
3.13156646304,
-11.469749861,
-133.337042673,
120.776724241,
-90.7193676414,
-1.53967904896,
1.1946461492,
-1.56264360755,
-254.2036633,
-616.626075757,
-12.8100311632,
-4.65,
-2.34,
-3.12,
-9.68,
32.89,
39.28,
};

bool is_class( float *stroke, float *vector )
{
	int i;
	float sum = 0.0;
	
	for (i = 0; i < 45; i++)
		sum = sum + stroke[i] * vector[i];

	return sum > 0;
}


void main( void *args )
{
	int i, n = 0, type = 0;
	float data[ 30 ];

	// Initial setup
	for (i = 0; i < 30; i++)
	{
		data[ i ] = 0;
	}

	i = 0;
	while (1)
	{
		GET_DATA();
		data[ i ] = data[ i ] + ASDF;
		data[ i + 1 ] = data[ i + 1 ] + ASDF;
		data[ i + 2 ] = data[ i + 2 ] + ASDF;
		data[ i + 3 ] = data[ i + 3 ] + ASDF;
		data[ i + 4 ] = data[ i + 4 ] + ASDF;
		data[ i + 5 ] = data[ i + 5 ] + ASDF;
		n++;

		// Move onto next 5th
		if ()
		{
			data[ i ] = data[ i ] / n;
			data[ i + 1 ] = data[ i + 1 ] / n;
			data[ i + 2 ] = data[ i + 2 ] / n;
			data[ i + 3 ] = data[ i + 3 ] / n;
			data[ i + 4 ] = data[ i + 4 ] / n;
			data[ i + 5 ] = data[ i + 5 ] / n;
			n = 0;

			if (i == 24)
				i = 0;
			else
				i = i + 6;

			// Classification
			if (is_class( data, forehand ))
				type = type + 2;
			if (is_class( data, drive ))
				type = type + 1;

			data[ i ] = 0;
			data[ i + 1 ] = 0;
			data[ i + 2 ] = 0;
			data[ i + 3 ] = 0;
			data[ i + 4 ] = 0;
			data[ i + 5 ] = 0;
		}
	}

}
