CC = gcc166

ALL : CAN SERVO

CAN:
	$(CC) -O2 -I "./include" -I "." -Wall -m7 -g can.c -o can -ltpc167 -lcan_16x_l

SERVO:
	$(CC) -O2 -I "./include" -I "." -Wall -m7 -g servo.c -o servo -ltpc167 -lcan_16x_l

clean:
	rm -f can servo


