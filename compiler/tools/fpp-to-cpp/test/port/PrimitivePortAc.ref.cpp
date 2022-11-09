// ======================================================================
// \title  PrimitivePortAc.cpp
// \author Generated by fpp-to-cpp
// \brief  cpp file for Primitive port
// ======================================================================

#include "Fw/Types/Assert.hpp"
#include "Fw/Types/StringUtils.hpp"
#include "PrimitivePortAc.hpp"

namespace {

  // ----------------------------------------------------------------------
  // Port buffer class
  // ----------------------------------------------------------------------

  class PrimitivePortBuffer : public Fw::SerializeBufferBase {

    public:

      NATIVE_UINT_TYPE getBuffCapacity() const {
        return InputPrimitivePort::SERIALIZED_SIZE;
      }

      U8* getBuffAddr() {
        return m_buff;
      }

      const U8* getBuffAddr() const {
        return m_buff;
      }

    private:

      U8 m_buff[InputPrimitivePort::SERIALIZED_SIZE];

  };

}

// ----------------------------------------------------------------------
// Input Port Member functions
// ----------------------------------------------------------------------

InputPrimitivePort ::
  InputPrimitivePort() :
    Fw::InputPortBase(),
    m_func(nullptr)
{

}

void InputPrimitivePort ::
  init()
{
  Fw::InputPortBase::init();
}

void InputPrimitivePort ::
  addCallComp(
      Fw::PassiveComponentBase* callComp,
      CompFuncPtr funcPtr
  )
{
  FW_ASSERT(callComp);
  FW_ASSERT(funcPtr);

  this->m_comp = callComp;
  this->m_func = funcPtr;
  this->m_connObj = callComp;
}

void InputPrimitivePort ::
  invoke(
      U32 u32,
      U32& u32Ref,
      F32 f32,
      F32& f32Ref,
      bool b,
      bool& bRef
  )
{
#if FW_PORT_TRACING == 1
  this->trace();
#endif

  FW_ASSERT(this->m_comp);
  FW_ASSERT(this->m_func);

  return this->m_func(this->m_comp, this->m_portNum, u32, u32Ref, f32, f32Ref, b, bRef);
}

#if FW_PORT_SERIALIZATION == 1

Fw::SerializeStatus InputPrimitivePort ::
  invokeSerial(Fw::SerializeBufferBase& _buffer)
{
  Fw::SerializeStatus _status;

#if FW_PORT_SERIALIZATION == 1
  this->trace();
#endif

  FW_ASSERT(this->m_comp);
  FW_ASSERT(this->m_func);

  U32 u32;
  _status = _buffer.deserialize(u32);
  if (_status != Fw::FW_SERIALIZE_OK) {
    return _status;
  }

  U32 u32Ref;
  _status = _buffer.deserialize(u32Ref);
  if (_status != Fw::FW_SERIALIZE_OK) {
    return _status;
  }

  F32 f32;
  _status = _buffer.deserialize(f32);
  if (_status != Fw::FW_SERIALIZE_OK) {
    return _status;
  }

  F32 f32Ref;
  _status = _buffer.deserialize(f32Ref);
  if (_status != Fw::FW_SERIALIZE_OK) {
    return _status;
  }

  bool b;
  _status = _buffer.deserialize(b);
  if (_status != Fw::FW_SERIALIZE_OK) {
    return _status;
  }

  bool bRef;
  _status = _buffer.deserialize(bRef);
  if (_status != Fw::FW_SERIALIZE_OK) {
    return _status;
  }

  this->m_func(this->m_comp, this->m_portNum, u32, u32Ref, f32, f32Ref, b, bRef);

  return Fw::FW_SERIALIZE_OK;
}

#endif

// ----------------------------------------------------------------------
// Output Port Member functions
// ----------------------------------------------------------------------

OutputPrimitivePort ::
  OutputPrimitivePort() :
    Fw::OutputPortBase(),
    m_port(nullptr)
{

}

void OutputPrimitivePort ::
  init()
{
  Fw::OutputPortBase::init();
}

void OutputPrimitivePort ::
  addCallPort(InputPrimitivePort* callPort)
{
  FW_ASSERT(callPort);

  this->m_port = callPort;
  this->m_connObj = callPort;

#if FW_PORT_SERIALIZATION == 1
  this->m_serPort = nullptr;
#endif
}

void OutputPrimitivePort ::
  invoke(
      U32 u32,
      U32& u32Ref,
      F32 f32,
      F32& f32Ref,
      bool b,
      bool& bRef
  )
{
#if FW_PORT_TRACING == 1
  this->trace();
#endif

#if FW_PORT_SERIALIZATION
  FW_ASSERT(this->m_port || this->m_serPort);
#else
  FW_ASSERT(this->m_port);
#endif
  if (this->m_port) {
    this->m_port->invoke(u32, u32Ref, f32, f32Ref, b, bRef);
#if FW_PORT_SERIALIZATION
  } else if (this->m_serPort) {
    Fw::SerializeStatus _status;
    PrimitivePortBuffer _buffer;

    _status = _buffer.serialize(u32);
    FW_ASSERT(_status == Fw::FW_SERIALIZE_OK, static_cast<FwAssertArgType>(_status));

    _status = _buffer.serialize(u32Ref);
    FW_ASSERT(_status == Fw::FW_SERIALIZE_OK, static_cast<FwAssertArgType>(_status));

    _status = _buffer.serialize(f32);
    FW_ASSERT(_status == Fw::FW_SERIALIZE_OK, static_cast<FwAssertArgType>(_status));

    _status = _buffer.serialize(f32Ref);
    FW_ASSERT(_status == Fw::FW_SERIALIZE_OK, static_cast<FwAssertArgType>(_status));

    _status = _buffer.serialize(b);
    FW_ASSERT(_status == Fw::FW_SERIALIZE_OK, static_cast<FwAssertArgType>(_status));

    _status = _buffer.serialize(bRef);
    FW_ASSERT(_status == Fw::FW_SERIALIZE_OK, static_cast<FwAssertArgType>(_status));

    _status = this->m_serPort->invokeSerial(_buffer);
    FW_ASSERT(_status == Fw::FW_SERIALIZE_OK, static_cast<FwAssertArgType>(_status));
  }
#else
  }
#endif
}
