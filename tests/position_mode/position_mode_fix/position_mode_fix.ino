#include <Dynamixel2Arduino.h>

#define DXL_SERIAL   Serial3
#define DEBUG_SERIAL Serial

const int DXL_DIR_PIN = 84;

const uint8_t DXL_ID = 1;
const float DXL_PROTOCOL_VERSION = 1.0;
const uint32_t DXL_BAUDRATE = 1000000;

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);

void setup()
{
  DEBUG_SERIAL.begin(115200);
  while (!DEBUG_SERIAL);

  // OpenCR <-> AX-18A communication
  dxl.begin(DXL_BAUDRATE);
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);

  DEBUG_SERIAL.println("Searching for AX-18A...");

  // Check communication first
  if (!dxl.ping(DXL_ID))
  {
    DEBUG_SERIAL.println("ERROR: AX-18A ID 1 not found!");
    return;
  }

  DEBUG_SERIAL.println("AX-18A found!");

  // AX-18A Protocol 1.0:
  // OP_POSITION corresponds to Joint Mode
  dxl.torqueOff(DXL_ID);

  if (!dxl.setOperatingMode(DXL_ID, OP_POSITION))
  {
    DEBUG_SERIAL.println("Failed to set position mode!");
    return;
  }

  dxl.torqueOn(DXL_ID);

  DEBUG_SERIAL.println("Torque ON");
}

void loop()
{
  // Move to approximately center position
  DEBUG_SERIAL.println("Moving to 120 degrees...");
  dxl.setGoalPosition(DXL_ID, 120.0, UNIT_DEGREE);

  delay(2000);

  float pos = dxl.getPresentPosition(DXL_ID, UNIT_DEGREE);
  DEBUG_SERIAL.print("Present position: ");
  DEBUG_SERIAL.println(pos);

  // Move to another safe position
  DEBUG_SERIAL.println("Moving to 180 degrees...");
  dxl.setGoalPosition(DXL_ID, 180.0, UNIT_DEGREE);

  delay(2000);

  pos = dxl.getPresentPosition(DXL_ID, UNIT_DEGREE);
  DEBUG_SERIAL.print("Present position: ");
  DEBUG_SERIAL.println(pos);
}