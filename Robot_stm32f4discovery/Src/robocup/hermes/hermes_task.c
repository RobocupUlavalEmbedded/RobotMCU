#include "hermes_task.h"

// This is the main task, it is intended to run indefinitely
void hermesTask(void) {
	// We have a small stack, this is why they are static
	static char packetBuffer[COBS_MAX_PAYLOAD_LEN];
	static unsigned char dataBuffer[COBS_MAX_PACKET_LEN];
	size_t payloadLen = 0;
	Result_t res;
	for(;;) {
		// Get data from device

		size_t bytesReceived = g_hermesHandle.com.readUntilZero(packetBuffer, COBS_MAX_PACKET_LEN);

		if(bytesReceived == 0){
			//LOG_INFO("Timeout on receiving\r\n");
			// It's more efficient to wait a few ticks before trying again
			osDelay(1);
			continue;
		}
		if(bytesReceived < sizeof(encodedPacketHeaderStruct_t)){
			static char packetHumanReadable[3*100]; // For each byte, three character needed
			static char messageAndPacket[3*100+30];

			convertBytesToStr(packetBuffer, bytesReceived, packetHumanReadable);

			sprintf(messageAndPacket, "Too small packet %s\r\n", packetHumanReadable);
			LOG_INFO(messageAndPacket);
			continue;
	    }

		// Check if our robot is recipient, before decoding
		encodedPacketHeaderStruct_t* encodedHeader = (encodedPacketHeaderStruct_t *) packetBuffer;
		if (encodedHeader->header.destAddress != ADDR_ROBOT && encodedHeader->header.destAddress != ADDR_BROADCAST) {
			LOG_INFO("Wrong dest\r\n");
			continue;
		}

		// The packet is decoded
		res = decobifyData(packetBuffer, bytesReceived, dataBuffer, &payloadLen);
		if (res == FAILURE){
			LOG_INFO("Fail decoding\r\n");
			continue;
		}

		packetHeaderStruct_t* currentPacketHeaderPtr = (packetHeaderStruct_t *) dataBuffer;
		res = validPayload(currentPacketHeaderPtr, payloadLen);

		if (res == FAILURE) {
			continue;
		}

		// Find the corresponding packet in the packet table
		packet_t packet = g_packetsTable[(size_t) (currentPacketHeaderPtr->packetType)];

		LOG_INFO("Success!!!\r\n");
		// Call callback that handle the packet
		packet.callback(dataBuffer);

		// This is use to give back control to other task
		osDelay(1);
	}
}
