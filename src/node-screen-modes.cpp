#include "nan.h"
#include "v8.h"
#include <windows.h>

struct Res
{
    int Width;
    int Height;
};

NAN_METHOD(GetScreenModes) {
  Nan::HandleScope scope;

  DEVMODE dm = { 0 };
  dm.dmSize = sizeof(dm);

  std::vector<Res> res_vector;

  for( int iModeNum = 0; EnumDisplaySettings( NULL, iModeNum, &dm ) != 0; iModeNum++)
  {
      Res r;
      r.Width = dm.dmPelsWidth;
      r.Height = dm.dmPelsHeight;
      res_vector.push_back(r);
  }

  v8::Local<v8::Array> resolutions = Nan::New<v8::Array>(res_vector.size());

  for(int i=0; i < res_vector.size(); i++)
  {
     v8::Local<v8::Object> res_obj_v8 = Nan::New<v8::Object>();
     Nan::Set(res_obj_v8, Nan::New("width").ToLocalChecked(),  Nan::New(res_vector[i].Width));
     Nan::Set(res_obj_v8, Nan::New("height").ToLocalChecked(),  Nan::New(res_vector[i].Height));

     Nan::Set(resolutions, i, res_obj_v8);
  }
  info.GetReturnValue().Set(resolutions);
}


NAN_MODULE_INIT(init) {
  Nan::Set(target,
           Nan::New("get").ToLocalChecked(),
           Nan::New<v8::FunctionTemplate>(GetScreenModes)->GetFunction());
}

NODE_MODULE(node_screen_modes, init)