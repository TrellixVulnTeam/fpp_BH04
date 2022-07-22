primitive()
{
  run_test "-p $PWD" primitive && \
    diff_cpp PrimitiveBoolArray
    diff_cpp PrimitiveU8Array
    diff_cpp PrimitiveU16Array
    diff_cpp PrimitiveI32Array
    diff_cpp PrimitiveI64Array
    diff_cpp PrimitiveF32fArray
    diff_cpp PrimitiveF32eArray
    diff_cpp PrimitiveF64Array
    diff_cpp PrimitiveArrayArray
}

string()
{
  run_test "-p $PWD" string && \
    diff_cpp String1Array 
    diff_cpp String2Array 
    diff_cpp StringArrayArray
}

enum()
{
  run_test "-p $PWD" enum && \
    diff_cpp E1Enum 
    diff_cpp E2Enum 
    diff_cpp Enum1Array 
    diff_cpp Enum2Array
}

builtin_type()
{
  run_test "-p $PWD" builtin_type && \
    diff_cpp BuiltInTypeArray
}

abs_type()
{
  run_test "-p $PWD" abs_type && \
    diff_cpp AbsTypeArray
}

struct()
{
  run_test "-p $PWD" struct && \
    diff_cpp Struct1Array
    diff_cpp Struct2Array
    diff_cpp Struct3Array
}

component()
{
  run_test "-p $PWD" component && \
    diff_cpp C_AArray
}
