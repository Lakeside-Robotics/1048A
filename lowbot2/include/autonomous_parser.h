#pragma once

#include "autonomous_controller.h"
#include "v5.h"
#include "v5_vcs.h"
#include "globals.h"

#if false

namespace ls {

    class autonomous_parser {
    
    autonomous_controller& contr;

    public:
        autonomous_parser(autonomous_controller& contr) : contr(contr) {}
        void initController();

    };


};

#endif