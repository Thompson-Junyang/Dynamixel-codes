
// #include <Dynamixel2Arduino.h>

// #define DXL_SERIAL   Serial3
// #define DEBUG_SERIAL Serial

// const int DXL_DIR_PIN = 84;

// const uint8_t DXL_ID = 1;
// const float DXL_PROTOCOL_VERSION = 1.0;
// const uint32_t DXL_BAUDRATE = 1000000;

// Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);

// void setup()
// {
//   DEBUG_SERIAL.begin(115200);
//   while (!DEBUG_SERIAL);

//   DEBUG_SERIAL.println("Starting AX-18A test...");

//   // Communication
//   dxl.begin(DXL_BAUDRATE);
//   dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);

//   // 1. Test communication
//   if (!dxl.ping(DXL_ID))
//   {
//     DEBUG_SERIAL.println("ERROR: Cannot find AX-18A!");
//     return;
//   }

//   DEBUG_SERIAL.println("Ping OK!");

//   // 2. Configure Joint/Position mode
//   dxl.torqueOff(DXL_ID);

//   if (dxl.setOperatingMode(DXL_ID, OP_POSITION))
//   {
//     DEBUG_SERIAL.println("Position mode OK!");
//   }
//   else
//   {
//     DEBUG_SERIAL.println("ERROR: Position mode failed!");
//   }

//   // 3. Enable motor torque
//   if (dxl.torqueOn(DXL_ID))
//   {
//     DEBUG_SERIAL.println("Torque ON OK!");
//   }
//   else
//   {
//     DEBUG_SERIAL.println("ERROR: Torque ON failed!");
//   }

//   // 4. Read current position BEFORE moving
//   float pos = dxl.getPresentPosition(DXL_ID, UNIT_DEGREE);

//   DEBUG_SERIAL.print("Current position = ");
//   DEBUG_SERIAL.println(pos);

//   // 5. First move to a safe middle position
//   DEBUG_SERIAL.println("Moving to 150 degrees...");

//   if (dxl.setGoalPosition(DXL_ID, 150.0, UNIT_DEGREE))
//   {
//     DEBUG_SERIAL.println("Goal position command sent!");
//   }
//   else
//   {
//     DEBUG_SERIAL.println("ERROR: Goal position command failed!");
//   }
// }


// void loop()
// {
//   DEBUG_SERIAL.println("Go to 250");

//   bool ok = dxl.setGoalPosition(
//       DXL_ID,
//       250.0,
//       UNIT_DEGREE
//   );

//   DEBUG_SERIAL.print("Command result = ");
//   DEBUG_SERIAL.println(ok);

//   delay(3000);

//   DEBUG_SERIAL.print("Actual = ");
//   DEBUG_SERIAL.println(
//       dxl.getPresentPosition(DXL_ID, UNIT_DEGREE)
//   );


//   DEBUG_SERIAL.println("Go to 50");

//   ok = dxl.setGoalPosition(
//       DXL_ID,
//       50.0,
//       UNIT_DEGREE
//   );

//   DEBUG_SERIAL.print("Command result = ");
//   DEBUG_SERIAL.println(ok);

//   delay(3000);

//   DEBUG_SERIAL.print("Actual = ");
//   DEBUG_SERIAL.println(
//       dxl.getPresentPosition(DXL_ID, UNIT_DEGREE)
//   );
// }


// //test for 50 -250
// void loop()
// {
//   // Move to 250 degrees
//   DEBUG_SERIAL.println("Moving to 250 degrees...");

//   dxl.setGoalPosition(DXL_ID, 250.0, UNIT_DEGREE);

//   delay(2000);

//   DEBUG_SERIAL.print("Position = ");
//   DEBUG_SERIAL.println(
//     dxl.getPresentPosition(DXL_ID, UNIT_DEGREE)
//   );


//   // Move to 50 degrees
//   DEBUG_SERIAL.println("Moving to 50 degrees...");

//   dxl.setGoalPosition(DXL_ID, 50.0, UNIT_DEGREE);

//   delay(2000);

//   DEBUG_SERIAL.print("Position = ");
//   DEBUG_SERIAL.println(
//     dxl.getPresentPosition(DXL_ID, UNIT_DEGREE)
//   );
// }




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
  // PC <-> OpenCR
  DEBUG_SERIAL.begin(115200);

  delay(2000);

  DEBUG_SERIAL.println("===== PROGRAM START =====");

  // OpenCR <-> AX-18A
  dxl.begin(DXL_BAUDRATE);
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);

  DEBUG_SERIAL.println("Dynamixel port initialized");

  // Ping
  if (dxl.ping(DXL_ID))
  {
    DEBUG_SERIAL.println("Ping OK");
  }
  else
  {
    DEBUG_SERIAL.println("Ping FAILED");
    return;
  }

  // Position mode
  dxl.torqueOff(DXL_ID);

  if (dxl.setOperatingMode(DXL_ID, OP_POSITION))
  {
    DEBUG_SERIAL.println("Position mode OK");
  }
  else
  {
    DEBUG_SERIAL.println("Position mode FAILED");
    return;
  }

  // Torque ON
  if (dxl.torqueOn(DXL_ID))
  {
    DEBUG_SERIAL.println("Torque ON OK");
  }
  else
  {
    DEBUG_SERIAL.println("Torque ON FAILED");
    return;
  }

  DEBUG_SERIAL.print("Current position = ");
  DEBUG_SERIAL.println(
    dxl.getPresentPosition(DXL_ID, UNIT_DEGREE)
  );

  DEBUG_SERIAL.println("Setup finished");
}

void loop()
{
  DEBUG_SERIAL.println("Go to RAW 1023");

  bool result = dxl.setGoalPosition(DXL_ID, 1023);

  DEBUG_SERIAL.print("Command result = ");
  DEBUG_SERIAL.println(result);

  delay(3000);

  DEBUG_SERIAL.print("Actual RAW = ");
  DEBUG_SERIAL.println(
    dxl.getPresentPosition(DXL_ID)
  );

  DEBUG_SERIAL.print("Actual Degree = ");
  DEBUG_SERIAL.println(
    dxl.getPresentPosition(DXL_ID, UNIT_DEGREE)
  );


  DEBUG_SERIAL.println("Go to RAW 0");

  result = dxl.setGoalPosition(DXL_ID, 0);

  DEBUG_SERIAL.print("Command result = ");
  DEBUG_SERIAL.println(result);

  delay(3000);

  DEBUG_SERIAL.print("Actual RAW = ");
  DEBUG_SERIAL.println(
    dxl.getPresentPosition(DXL_ID)
  );

  DEBUG_SERIAL.print("Actual Degree = ");
  DEBUG_SERIAL.println(
    dxl.getPresentPosition(DXL_ID, UNIT_DEGREE)
  );
}