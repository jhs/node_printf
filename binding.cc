#include <stdio.h>
#include <stdarg.h>
#include <node.h>
#include <node_events.h>
#include <assert.h>

using namespace v8;
using namespace node;
static Persistent<String> ready_symbol;
static Persistent<String> result_symbol;
static Persistent<String> close_symbol;
static Persistent<String> connect_symbol;
#define READY_STATE_SYMBOL String::NewSymbol("readyState")

class Printf : public EventEmitter {
 public:
  static void
  Initialize (v8::Handle<v8::Object> target)
  {
    HandleScope scope;

    Local<FunctionTemplate> t = FunctionTemplate::New(New);

    t->Inherit(EventEmitter::constructor_template);
    t->InstanceTemplate()->SetInternalFieldCount(1);

    /*
    close_symbol = NODE_PSYMBOL("close");
    connect_symbol = NODE_PSYMBOL("connect");
    result_symbol = NODE_PSYMBOL("result");
    ready_symbol = NODE_PSYMBOL("ready");

    NODE_SET_PROTOTYPE_METHOD(t, "connect", Connect);
    NODE_SET_PROTOTYPE_METHOD(t, "close", Close);
    NODE_SET_PROTOTYPE_METHOD(t, "reset", Reset);
    NODE_SET_PROTOTYPE_METHOD(t, "dispatchQuery", DispatchQuery);
    */
    NODE_SET_PROTOTYPE_METHOD(t, "sprintf", SPrintf);

    t->PrototypeTemplate()->SetAccessor(READY_STATE_SYMBOL, ReadyStateGetter);

    target->Set(String::NewSymbol("Printf"), t->GetFunction());
  }

 protected:

  static Handle<Value>
  New (const Arguments& args)
  {
    HandleScope scope;

    Printf *printf = new Printf();
    printf->Wrap(args.This());

    return args.This();
  }

  static Handle<Value>
  SPrintf (const Arguments& args)
  {
    printf("Started SPrintf\n");
    Printf *printf = ObjectWrap::Unwrap<Printf>(args.This());

    HandleScope scope;

    if (args.Length() == 0 || !args[0]->IsArray()) {
      return ThrowException(String::New("Must give array as first argument"));
    }

    char result[4096];
    // Convert the format to an ASCII string.
    Array *real_args = Array::Cast(args[0]);//args[0]->ToObject();

  //Initialize (v8::Handle<v8::Object> target)

    //String::AsciiValue ascii(args[0]->[0]->ToString());
    const char *ascii = ToCString(real_args[0]);

    int count = snprintf(result, 4096, *ascii);
    return String::New(result);
  }

  static Handle<Value>
  ReadyStateGetter (Local<String> property, const AccessorInfo& info)
  {
    Printf *printf = ObjectWrap::Unwrap<Printf>(info.This());
    assert(printf);

    assert(property == READY_STATE_SYMBOL);

    HandleScope scope;

    return scope.Close(String::NewSymbol("OK"));
  }

  Printf () : EventEmitter () 
  {
    /*
    ev_init(&read_watcher_, io_event);
    read_watcher_.data = this;

    ev_init(&write_watcher_, io_event);
    write_watcher_.data = this;
    */
  }

  ~Printf ()
  {
  }

 //private:
};

extern "C" void
init (Handle<Object> target) 
{
  HandleScope scope;
  Printf::Initialize(target);
}
