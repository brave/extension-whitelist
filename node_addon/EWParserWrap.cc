/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <node_buffer.h>

#include "EWParserWrap.h"

namespace EWParserWrap {

  using v8::Function;
  using v8::FunctionCallbackInfo;
  using v8::FunctionTemplate;
  using v8::Isolate;
  using v8::Local;
  using v8::MaybeLocal;
  using v8::Int32;
  using v8::Object;
  using v8::Persistent;
  using v8::String;
  using v8::Boolean;
  using v8::Value;
  using v8::Exception;
  using v8::NewStringType;

  char *deserializedData = nullptr;

  Persistent<Function> CEWParserWrap::constructor;

  CEWParserWrap::CEWParserWrap() {
  }

  CEWParserWrap::~CEWParserWrap() {
  }

  void CEWParserWrap::Init(Local<Object> exports) {
    Isolate* isolate = exports->GetIsolate();

    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
    tpl->SetClassName(String::NewFromUtf8(isolate, "CEWParser", NewStringType::kNormal).ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    NODE_SET_PROTOTYPE_METHOD(tpl, "addToBlacklist", CEWParserWrap::AddToBlacklist);
    NODE_SET_PROTOTYPE_METHOD(tpl, "addToWhitelist", CEWParserWrap::AddToWhitelist);
    NODE_SET_PROTOTYPE_METHOD(tpl, "isBlacklisted", CEWParserWrap::IsBlacklisted);
    NODE_SET_PROTOTYPE_METHOD(tpl, "isWhitelisted", CEWParserWrap::IsWhitelisted);
    NODE_SET_PROTOTYPE_METHOD(tpl, "serialize", CEWParserWrap::Serialize);
    NODE_SET_PROTOTYPE_METHOD(tpl, "deserialize", CEWParserWrap::Deserialize);
    NODE_SET_PROTOTYPE_METHOD(tpl, "cleanup", CEWParserWrap::Cleanup);

    constructor.Reset(isolate, tpl->GetFunction(isolate->GetCurrentContext()).ToLocalChecked());
    exports->Set(isolate->GetCurrentContext(),
                 String::NewFromUtf8(isolate, "CEWParser", NewStringType::kNormal).ToLocalChecked(),
                 tpl->GetFunction(isolate->GetCurrentContext()).ToLocalChecked());
  }

  void CEWParserWrap::New(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.IsConstructCall()) {
      // Invoked as constructor: `new CEWParserWrap(...)`
      CEWParserWrap* obj = new CEWParserWrap();
      obj->Wrap(args.This());
      args.GetReturnValue().Set(args.This());
    } else {
      // Invoked as plain function `CEWParserWrap(...)`,
      // turn into construct call.
      const int argc = 1;
      Local<Value> argv[argc] = { args[0] };
      Local<Function> cons = Local<Function>::New(isolate, constructor);
      args.GetReturnValue().Set(
        cons->NewInstance(isolate->GetCurrentContext(), argc, argv)
        .ToLocalChecked());
    }
  }

  void CEWParserWrap::AddToBlacklist(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    if (args.Length() != 1) {
      isolate->ThrowException(Exception::TypeError(
                                String::NewFromUtf8(isolate, "Wrong number of arguments", NewStringType::kNormal).ToLocalChecked()));
      return;
    }

    if (!args[0]->IsString()) {
      isolate->ThrowException(Exception::TypeError(
                                String::NewFromUtf8(isolate, "Wrong arguments", NewStringType::kNormal).ToLocalChecked()));
      return;
    }

    String::Utf8Value id(isolate, args[0]->ToString(isolate->GetCurrentContext()).FromMaybe(Local<String>()));
    const char * buffer = *id;

    CEWParserWrap* obj = ObjectWrap::Unwrap<CEWParserWrap>(args.Holder());
    obj->addToBlacklist(buffer);
  }

  void CEWParserWrap::AddToWhitelist(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    if (args.Length() != 1) {
      isolate->ThrowException(Exception::TypeError(
                                String::NewFromUtf8(isolate, "Wrong number of arguments", NewStringType::kNormal).ToLocalChecked()));
      return;
    }

    if (!args[0]->IsString()) {
      isolate->ThrowException(Exception::TypeError(
                                String::NewFromUtf8(isolate, "Wrong arguments", NewStringType::kNormal).ToLocalChecked()));
      return;
    }

    String::Utf8Value id(isolate, args[0]->ToString(isolate->GetCurrentContext()).FromMaybe(Local<String>()));
    const char * buffer = *id;

    CEWParserWrap* obj = ObjectWrap::Unwrap<CEWParserWrap>(args.Holder());
    obj->addToWhitelist(buffer);
  }

  void CEWParserWrap::IsBlacklisted(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    if (args.Length() != 1) {
      isolate->ThrowException(Exception::TypeError(
                                String::NewFromUtf8(isolate, "Wrong number of arguments", NewStringType::kNormal).ToLocalChecked()));
      return;
    }

    if (!args[0]->IsString()) {
      isolate->ThrowException(Exception::TypeError(
                                String::NewFromUtf8(isolate, "Wrong arguments", NewStringType::kNormal).ToLocalChecked()));
      return;
    }

    String::Utf8Value id(isolate, args[0]->ToString(isolate->GetCurrentContext()).FromMaybe(Local<String>()));
    const char * bufferID = *id;

    CEWParserWrap* obj = ObjectWrap::Unwrap<CEWParserWrap>(args.Holder());
    args.GetReturnValue().Set(Boolean::New(isolate, obj->isBlacklisted(bufferID)));
  }

  void CEWParserWrap::IsWhitelisted(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    if (args.Length() != 1) {
      isolate->ThrowException(Exception::TypeError(
                                String::NewFromUtf8(isolate, "Wrong number of arguments", NewStringType::kNormal).ToLocalChecked()));
      return;
    }

    if (!args[0]->IsString()) {
      isolate->ThrowException(Exception::TypeError(
                                String::NewFromUtf8(isolate, "Wrong arguments", NewStringType::kNormal).ToLocalChecked()));
      return;
    }

    String::Utf8Value id(isolate, args[0]->ToString(isolate->GetCurrentContext()).FromMaybe(Local<String>()));
    const char * bufferID = *id;

    CEWParserWrap* obj = ObjectWrap::Unwrap<CEWParserWrap>(args.Holder());
    args.GetReturnValue().Set(Boolean::New(isolate, obj->isWhitelisted(bufferID)));
  }

  void CEWParserWrap::Serialize(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    CEWParserWrap* obj = ObjectWrap::Unwrap<CEWParserWrap>(args.Holder());

    unsigned int totalSize = 0;
    // Serialize data
    char* data = obj->serialize(&totalSize);
    if (nullptr == data) {
      isolate->ThrowException(Exception::TypeError(
                                String::NewFromUtf8(isolate, "Could not serialize", NewStringType::kNormal).ToLocalChecked()));
      return;
    }

    MaybeLocal<Object> buffer = node::Buffer::New(isolate, totalSize);
    Local<Object> localBuffer;
    if (!buffer.ToLocal(&localBuffer)) {
      isolate->ThrowException(Exception::TypeError(
                                String::NewFromUtf8(isolate, "Could not convert MaybeLocal to Local", NewStringType::kNormal).ToLocalChecked()));
      return;
    }
    ::memcpy(node::Buffer::Data(localBuffer), data, totalSize);

    delete []data;

    args.GetReturnValue().Set(localBuffer);
  }

  void CEWParserWrap::Deserialize(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    if (args.Length() < 1) {
      isolate->ThrowException(Exception::TypeError(
                                String::NewFromUtf8(isolate, "Wrong number of arguments", NewStringType::kNormal).ToLocalChecked()));
      return;
    }

    unsigned char *buf = (unsigned char *)node::Buffer::Data(args[0]);
    size_t length = node::Buffer::Length(args[0]);

    if (nullptr != deserializedData) {
      delete []deserializedData;
    }
    deserializedData = new char[length];
    memcpy(deserializedData, buf, length);

    CEWParserWrap* obj = ObjectWrap::Unwrap<CEWParserWrap>(args.Holder());
    args.GetReturnValue().Set(Boolean::New(isolate, obj->deserialize(deserializedData)));
  }

  void CEWParserWrap::Cleanup(const FunctionCallbackInfo<Value>& args) {
    if (nullptr != deserializedData) {
      delete []deserializedData;
      deserializedData = nullptr;
    }
  }

}   //namespace EWParserWrap
