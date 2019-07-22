{
  "targets": [{
    "target_name": "extension-whitelist",
    "type": "static_library",
    "sources": [
      "extension_whitelist_parser.cc",
      "extension_whitelist_parser.h",
      "extension_whitelist_data.cc",
      "extension_whitelist_data.h",
    ],
    "include_dirs": [
      ".",
      './node_modules/hashset-cpp'
    ],
    "dependencies": [
      "./node_modules/hashset-cpp/binding.gyp:hashset-cpp"
    ],
    "conditions": [
      ['OS=="win"', {
        }, {
          'cflags_cc': [ '-fexceptions' ]
        }
      ]
    ],
    "xcode_settings": {
      "OTHER_CFLAGS": [ "-ObjC" ],
      "OTHER_CPLUSPLUSFLAGS" : ["-std=c++11","-stdlib=libc++", "-v"],
      "MACOSX_DEPLOYMENT_TARGET": "10.9",
      "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
    },
  },
  {
      "target_name": "ew_node_addon",
      "sources": [
        "extension_whitelist_parser.cc",
        "extension_whitelist_parser.h",
        "extension_whitelist_data.cc",
        "extension_whitelist_data.h",
        "./node_addon/EWParserWrap.h",
        "./node_addon/EWParserWrap.cc",
        "./node_addon/addon.cpp",
        "./node_modules/hashset-cpp/hashFn.cc",
        "./node_modules/hashset-cpp/hashFn.h"
      ],
      "include_dirs": [
        ".",
        './node_modules/hashset-cpp'
      ],
      "conditions": [
        ['OS=="win"', {
          }, {
            'cflags_cc': [ '-fexceptions' ]
          }
        ]
      ],
      "xcode_settings": {
      "OTHER_CFLAGS": [ "-ObjC" ],
      "OTHER_CPLUSPLUSFLAGS" : ["-std=c++11","-stdlib=libc++", "-v"],
      "OTHER_LDFLAGS": ["-stdlib=libc++"],
      "MACOSX_DEPLOYMENT_TARGET": "10.9",
      "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
      },
  }],
}
