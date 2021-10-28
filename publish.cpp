#include <mosquitto.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int gtemp;
void on_connect(struct mosquitto *mosq, void *obj, int reason_code)
{
	/* equivalent for MQTT v5.0
	 * clients is mosquitto_reason_string().
	 */
	printf("on_connect: %s\n", mosquitto_connack_string(reason_code));
	if(reason_code != 0){
		printf("cound not connect to the broker\n");
		mosquitto_disconnect(mosq);
		//return false;
	}
	//return true;
}


void on_publish(struct mosquitto *mosq, void *obj, int mid)
{
	printf("Message with temperature %d and mid %d has been published.\n", gtemp, mid);
}

int get_temperature(void)
{
	sleep(1);
	gtemp = random()%100; 
	return gtemp;
}

void publish_sensor_data(struct mosquitto *mosq)
{
	char payload[20];
	int temp;
	int rc;

	/* Get our pretend data */
	temp = get_temperature();
	snprintf(payload, sizeof(payload), "%d", temp);

	int mid;
	rc = mosquitto_publish(mosq, &mid, "sensor/temperature", strlen(payload), payload, 2, false);
	if(rc != MOSQ_ERR_SUCCESS){
		fprintf(stderr, "Error publishing: %s\n", mosquitto_strerror(rc));
	}
}


int main(int argc, char *argv[])
{
	struct mosquitto *mosq;
	int rc;

	mosquitto_lib_init();

	mosq = mosquitto_new(NULL, true, NULL);
	if(mosq == NULL){
		fprintf(stderr, "Error: Out of memory.\n");
		return 1;
	}

	mosquitto_connect_callback_set(mosq, on_connect);
	mosquitto_publish_callback_set(mosq, on_publish);

	rc = mosquitto_connect(mosq, "test.mosquitto.org", 1883, 20);
	if(rc != MOSQ_ERR_SUCCESS){
		mosquitto_destroy(mosq);
		fprintf(stderr, "Error: %s\n", mosquitto_strerror(rc));
		return 1;
	}

	/* Run the network loop in a background thread, this call returns quickly. */
	rc = mosquitto_loop_start(mosq);
	if(rc != MOSQ_ERR_SUCCESS){
		mosquitto_destroy(mosq);
		fprintf(stderr, "Error: %s\n", mosquitto_strerror(rc));
		return 1;
	}

	sleep(1);
	while(1){
		publish_sensor_data(mosq);
	}

	mosquitto_lib_cleanup();
	return 0;
}

