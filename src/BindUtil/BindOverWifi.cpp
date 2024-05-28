#include "BindOverWifi.h"
#ifdef ARDUINO_ARCH_ESP32
uint8_t UDPStream::discoveryMsg[6] = { 0x42, 0X69, 0X6E, 0X64, 0X44, 0X43 };   // BindDC
uint8_t UDPStream::connectMsg[6] = { 0x42, 0X69, 0X6E, 0X64, 0X43, 0X4E };     // BindCN
uint8_t UDPStream::stopMsg[6] = { 0x42, 0X69, 0X6E, 0X64, 0X53, 0X54 };        // BindST
uint8_t UDPStream::bindHeartbeat[6] = { 0x42, 0X69, 0X6E, 0X64, 0X48, 0X42 };  // BindHB
uint16_t UDPStream::bindPort = 7997;

bool UDPStream::begin(Bind &bind, const char* bindname) {
  return begin(bindname, bind);
}

bool UDPStream::begin(const char* bindname, Bind &bind) {
  this->_bind = &bind;
  this->bindname = bindname;
  if (this->udp.listen(this->bindPort)) {
    this->udp.onPacket([this](AsyncUDPPacket packet) {
       this->handleUDP(*this, packet);
    });
    return true;
  }
  return false;
}

size_t UDPStream::write(const uint8_t *buffer, size_t size) {
  if (!this->sendPackets) {
    return 0;
  }

  if (this->sendPackets == true && this->lastHeartbeat + 5000 > millis()) {
    this->udp.writeTo(buffer, size, this->canvasIP, this->bindPort);
    #if UDP_DEBUG_MSG
    Serial.print("TX: ");
    Serial.print(this->canvasIP);
    Serial.print(" - Hex[");
    for (int i = 0; i < size; i++) {
      Serial.print(buffer[i], HEX);
      Serial.print(" ");
    }
    Serial.println("]");
    #endif
    return size;
  } else {
    this->sendPackets = false;
    this->canvasIP = IPAddress(0, 0, 0, 0);
    return 0;
  }
}

void UDPStream::handleUDP(UDPStream& udpStream, AsyncUDPPacket& packet) {
  #if UDP_DEBUG_MSG
  Serial.print("RX: ");
  Serial.print(packet.remoteIP());
  Serial.print(" - [");
  Serial.write(packet.data(), packet.length());
  Serial.print("]");
  Serial.print(" - Hex[");
  for (int i = 0; i < packet.length(); i++) {
    Serial.print(packet.data()[i], HEX);
    Serial.print(" ");
  }
  Serial.println("]");
  #endif

  if (memcmp(packet.data(), udpStream.discoveryMsg, sizeof(udpStream.discoveryMsg)) == 0) {
    char buffer[50];
    sprintf(buffer, "BindDiscovered:%s", udpStream.bindname);
    #if UDP_DEBUG_MSG
    Serial.println(buffer);
    #endif
    udpStream.udp.writeTo((uint8_t*)buffer, strlen(buffer), packet.remoteIP(), packet.localPort());
  }

  if (memcmp(packet.data(), udpStream.connectMsg, sizeof(udpStream.connectMsg)) == 0) {
    // Todo: Check if is already connected or not!  millis() - lastHeartbeat > 5000 => disconnected and sendPackets = false
    if (udpStream.canvasIP == IPAddress(0, 0, 0, 0)) {
      udpStream.lastHeartbeat = millis();
      udpStream.canvasIP = packet.remoteIP();
      udpStream.sendPackets = true;
      char buffer[50];
      sprintf(buffer, "BindConnected:%s", udpStream.bindname);
      #if UDP_DEBUG_MSG
      Serial.println(buffer);
      #endif
      udpStream.udp.writeTo((uint8_t*)buffer, strlen(buffer), udpStream.canvasIP, packet.localPort());
    } else {
      char buffer[50];
      sprintf(buffer, "BindConnectionFailed:%s", udpStream.bindname);
      #if UDP_DEBUG_MSG
      Serial.println(buffer);
      #endif
      udpStream.udp.writeTo((uint8_t*)buffer, strlen(buffer), packet.remoteIP(), packet.localPort());
    }
  }
  if (udpStream.canvasIP == packet.remoteIP()) {

    udpStream.lastHeartbeat = millis();
  
    if (memcmp(packet.data(), udpStream.bindHeartbeat, sizeof(udpStream.bindHeartbeat)) == 0) {
      char buffer[50];
      sprintf(buffer, "BindHeartbeat:%s - time:%d", udpStream.bindname, udpStream.lastHeartbeat);
      #if UDP_DEBUG_MSG
      Serial.println(buffer);
      #endif
      udpStream.udp.writeTo((uint8_t*)buffer, strlen(buffer), packet.remoteIP(), packet.localPort());
    }

    if (memcmp(packet.data(), udpStream.stopMsg, sizeof(udpStream.stopMsg)) == 0) {
      udpStream.sendPackets = false;
      udpStream.canvasIP = IPAddress(0, 0, 0, 0);
    }
    udpStream._bind->sync(packet.data(),packet.length());
  }
}
#endif // ARDUINO_ARCH_ESP32
