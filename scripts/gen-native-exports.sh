cat src/yapcduino.cpp | grep NAN_METHOD | sed 's/.*(//' | sed 's/).*//' | sed 's/\(.*\)/exports->Set(NanNew<String>("\1"),\nNanNew<FunctionTemplate>(\1)->GetFunction());\n/'
