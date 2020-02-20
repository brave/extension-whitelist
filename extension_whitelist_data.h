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
    if (buffer) {
      memcpy(buffer, sExtensionID, EXTENSION_ID_LEN);
    }
    return EXTENSION_ID_LEN;
  }

  uint32_t Deserialize(char *buffer, uint32_t bufferSize) {
    if (!buffer || 0 == buffer) {
      return 0;
    }
    memcpy(sExtensionID, buffer, EXTENSION_ID_LEN);
    sExtensionID[EXTENSION_ID_LEN] = '\0';
    return EXTENSION_ID_LEN;
  }

  char sExtensionID[EXTENSION_ID_LEN + 1];
};

#endif  // EXTENSION_WHITELIST_DATA_H_
