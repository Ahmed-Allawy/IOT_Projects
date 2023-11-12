#pragma once

#include <string>

using namespace std;

// WiFi credentials
const char *SSID = "Wokwi-GUEST";
const char *PASSWORD = "";

// MQTT settings
const string ID = "ahmed@Allawy_2023";

const string BROKER = "test.mosquitto.org";
const string CLIENT_NAME = ID + "nightlight_esp32_client";

const string CLIENT_TELEMETRY_TOPIC = ID + "/light";
const string SERVER_COMMAND_TOPIC = ID + "/commands";
