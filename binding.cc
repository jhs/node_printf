#include <stdio.h>
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


extern "C" void
init (Handle<Object> target) 
{
  printf("init called\n");
}
