// Copyright 2022 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Flags: --allow-natives-syntax --maglev --no-stress-opt

function factory() {
  var x = 1;
  x = 2;
  return function foo() {
    return x;
  }
}

let foo = factory();

%PrepareFunctionForOptimization(foo);
assertEquals(2, foo());
assertEquals(2, foo());

%OptimizeMaglevOnNextCall(foo);
assertEquals(2, foo());


function nested_factory() {
  var x = 1;
  x = 2;
  return (function() {
    var z = 3;
    return function foo(){
      // Add two values from different contexts to force an
      // LdaImmutableCurrentContextSlot
      return x+z;
    }
  })();
}

foo = nested_factory();

%PrepareFunctionForOptimization(foo);
assertEquals(5, foo());
assertEquals(5, foo());

%OptimizeMaglevOnNextCall(foo);
assertEquals(5, foo());
