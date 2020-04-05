/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "extension_set.h"
#include <stdexcept>

ExtensionSet::ExtensionSet() {}
ExtensionSet::~ExtensionSet() {}

void ExtensionSet::Add(std::string key) {
  if (key.length() != EXTENSION_ID_LEN) {
    throw std::runtime_error("Invalid extension length given!");
  }
  set.insert(key);
}

bool ExtensionSet::Exists(std::string key) {
  return set.find(key) != set.end();
}

char* ExtensionSet::Serialize(uint32_t* size) {
  *size = set.size() * EXTENSION_ID_LEN;
  char* buffer = new char[*size];
  size_t offset = 0;
  for (std::string e : set) {
    memcpy(buffer + offset, e.c_str(), EXTENSION_ID_LEN);
    offset += EXTENSION_ID_LEN;
  }
  return buffer;
}

void ExtensionSet::Deserialize(char* buffer, uint32_t size) {
  set.clear();
  for (uint32_t i = 0; i < size; i++) {
    std::string s(buffer, EXTENSION_ID_LEN);
    set.insert(s);
    buffer += EXTENSION_ID_LEN;
  }
}
