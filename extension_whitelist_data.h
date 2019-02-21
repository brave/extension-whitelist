/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef EXTENSION_WHITELIST_DATA_H_
#define EXTENSION_WHITELIST_DATA_H_

#include <stdint.h>
#include <stdio.h>
#include <string.h>

struct ST_EXTENSION_WHITELIST_DATA {
public:
  ST_EXTENSION_WHITELIST_DATA():
    sExtensionID(nullptr) {
  }

  ST_EXTENSION_WHITELIST_DATA(const ST_EXTENSION_WHITELIST_DATA &other) {
    if (nullptr == other.sExtensionID) {
      return;
    }

    sExtensionID = new char[strlen(other.sExtensionID) + 1];
    strcpy(sExtensionID, other.sExtensionID);
  }

  ~ST_EXTENSION_WHITELIST_DATA() {
    if (nullptr != sExtensionID) {
      delete []sExtensionID;
    }
  }

  uint64_t GetHash() const;

  bool operator==(const ST_EXTENSION_WHITELIST_DATA &rhs) const {
    int extensionLen = static_cast<int>(strlen(sExtensionID));
    int rhsExtensionIDLen = static_cast<int>(strlen(rhs.sExtensionID));

    if (extensionLen != rhsExtensionIDLen) {
      return false;
    }

    return !memcmp(sExtensionID, rhs.sExtensionID, extensionLen);
  }

  // Nothing needs to be updated when an extension is added multiple times
  void Update(const ST_EXTENSION_WHITELIST_DATA &) {}

  uint32_t Serialize(char* buffer) {
    uint32_t size = 0;

    char sz[32];
    uint32_t dataLenSize = 1 + snprintf(sz, sizeof(sz), "%x", (unsigned int)strlen(sExtensionID));

    if (buffer) {
      memcpy(buffer + size, sz, dataLenSize);
    }
    size += dataLenSize;

    if (buffer) {
      memcpy(buffer + size, sExtensionID, strlen(sExtensionID));
    }
    size += static_cast<uint32_t>(strlen(sExtensionID));

    return size;
  }

  uint32_t Deserialize(char *buffer, uint32_t bufferSize) {
    uint32_t size = 0;

    if (!buffer || 0 == bufferSize) {
      return size;
    }
    unsigned int extensionLength = 0;
    sscanf(buffer, "%x", &extensionLength);
    if (sExtensionID) {
      delete []sExtensionID;
    }
    size = static_cast<uint32_t>(strlen(buffer) + 1);
    sExtensionID = new char[extensionLength + 1];
    if (!sExtensionID) {
      return size;
    }
    memcpy(sExtensionID, buffer + size, extensionLength);
    sExtensionID[extensionLength] = '\0';
    size += extensionLength;

    return size;
  }

  char* sExtensionID;
};

#endif  // EXTENSION_WHITELIST_DATA_H_
