/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef EWPARSERWRAP_H_
#define EWPARSERWRAP_H_

#include <node.h>
#include <node_object_wrap.h>

#include "../extension_whitelist_parser.h"

namespace EWParserWrap {

  /**
   * Wraps Extension Whitelist for use in Node
   */
class CEWParserWrap : public ExtensionWhitelistParser, public node::ObjectWrap {
 public:
  static void Init(v8::Local<v8::Object> exports);

 private:
  CEWParserWrap();
  virtual ~CEWParserWrap();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void AddToBlacklist(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void AddToWhitelist(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void IsBlacklisted(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void IsWhitelisted(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Serialize(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Deserialize(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Cleanup(const v8::FunctionCallbackInfo<v8::Value>& args);

  static v8::Persistent<v8::Function> constructor;
};

}   // namespace EWParserWrap

#endif  //EWPARSERWRAP_H_
