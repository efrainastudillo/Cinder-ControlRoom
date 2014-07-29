//
//  Module.h
//  Cinder-ControlRoom
//
//  Created by Jean-Pierre Mouilleseaux on 02 Jul 2014.
//  Copyright 2014 Chorded Constructions. All rights reserved.
//

#pragma once

#include "View.h"

namespace Cinder { namespace ControlRoom {

typedef std::shared_ptr<class Module> ModuleRef;

class Module : public View {
public:
    static ModuleRef create(const ci::Rectf& frame);
    virtual ~Module();

    ModuleRef getPtr() { return std::static_pointer_cast<Module>(shared_from_this()); }

protected:
    Module(const ci::Rectf& frame);

    ci::signals::scoped_connection mConnectionMouseDown, mConnectionMouseDrag, mConnectionMouseUp;
    ViewRef mTrackingView;
};

}}
