#pragma once
#include "Command.h"

class TeleportCommand :
    public Command
{
public:
    virtual void execute() override;

};
