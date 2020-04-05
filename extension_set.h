/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef EXTENSION_SET_H_
#define EXTENSION_SET_H_

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unordered_set>

#define EXTENSION_ID_LEN 32

class ExtensionSet {
  private:
    std::unordered_set<std::string> set;
  public:
    ExtensionSet();
    ~ExtensionSet();
    void Add(std::string);
    bool Exists(std::string);
    char* Serialize(uint32_t* size);
    void Deserialize(char* buffer, uint32_t size);
};

#endif  // EXTENSION_SET_H_
