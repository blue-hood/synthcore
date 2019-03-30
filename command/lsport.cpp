#include "command.hpp"

#include <core/core.hpp>
#include <io.hpp>

void lsportHandler(vector<string> &args) {
  if (args.size() != 2) {
    throw runtime_error("構文: lsport (Component UUID)");
  }

  uuid_t uuid;
  if (parseUuid(args[1], &uuid)) {
    throw runtime_error("不正な Component UUID です。");
  }

  Component *com = searchCom(uuid);
  if (!com) {
    throw runtime_error("存在しない Component です。");
  }

  int i;
  LsportResponse response;
  vector<string> port_types;

  i = 0;
  port_types = com->getIn();
  for (InPort_p in : com->ins) {
    LsportResponse::InPort inResponse;

    inResponse.uuid = uuidStr(in->id);
    inResponse.type = port_types[i++];
    response.inputs.push_back(inResponse);
  }

  i = 0;
  port_types = com->getOut();
  for (OutPort_p out : com->outs) {
    LsportResponse::OutPort outResponse;

    outResponse.uuid = uuidStr(out->id);
    outResponse.type = port_types[i++];
    response.outputs.push_back(outResponse);
  }

  respond(response);
}
