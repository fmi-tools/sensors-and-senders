#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <optional>
#include <variant>

#include <common/Component.h>
#include "NmeaTelegram.h"
#include "Enums.h"
#include "UdpSender.h"

struct Variable {
    Causality causality;
    fmi2ValueReference valueReference;
    Type type;
};

class NmeaSenderComponent : public Component {
public:

    NmeaSenderComponent(const std::string& instance_name, const fmi2Type type, const fmi2String uuid, const std::string& resource_directory,
        const fmi2CallbackFunctions* callback_functions);

    ~NmeaSenderComponent() = default;

    void enter_initialization() override;
    void step(double step_size) override;

private:

    void parseModelDescription();
    void parseConfig();

    void updateTelegrams();
    void sendTelegrams();


    //Variables have unique names
    std::unordered_map<std::string, Variable> variables_;

    //Multiple value references 
    std::unordered_map<fmi2ValueReference, Value> values_;

    std::vector<NmeaTelegram> telegrams_;

    std::string remoteIp_ = "127.0.0.1";
    int remotePort_ = 50555;
    UdpSender udpSender_;
};

