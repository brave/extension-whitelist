/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef EXTENSION_WHITELIST_DATA_H_
#define EXTENSION_WHITELIST_DATA_H_

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define EXTENSION_ID_LEN 32

struct ST_EXTENSION_WHITELIST_DATA {
public:
  ST_EXTENSION_WHITELIST_DATA():
    sExtensionID() {
    *sExtensionID = '\0';
  }

  ST_EXTENSION_WHITELIST_DATA(const ST_EXTENSION_WHITELIST_DATA &other) {
    strncpy(sExtensionID, other.sExtensionID, EXTENSION_ID_LEN + 1);
  }

  ST_EXTENSION_WHITELIST_DATA(const char *other) {
    assert(strlen(other) == EXTENSION_ID_LEN);
    strncpy(sExtensionID, other, EXTENSION_ID_LEN + 1);
  }

  ~ST_EXTENSION_WHITELIST_DATA() {}

  uint64_t GetHash() const;

  bool operator==(const ST_EXTENSION_WHITELIST_DATA &rhs) const {
    return !memcmp(sExtensionID, rhs.sExtensionID, EXTENSION_ID_LEN);
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
    size = static_cast<uint32_t>(strlen(buffer) + 1);
    memcpy(sExtensionID, buffer + size, extensionLength);
    sExtensionID[extensionLength] = '\0';
    size += extensionLength;

    return size;
  }

  char sExtensionID[EXTENSION_ID_LEN + 1];
};

#endif  // EXTENSION_WHITELIST_DATA_H_
