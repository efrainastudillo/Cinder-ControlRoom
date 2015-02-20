//
//  View.h
//  Cinder-ControlRoom
//
//  Created by Jean-Pierre Mouilleseaux on 02 Jul 2014.
//  Copyright 2014-2015 Chorded Constructions. All rights reserved.
//

#pragma once

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

namespace Cinder { namespace ControlRoom {

typedef std::shared_ptr<class View> ViewRef;

class View : public std::enable_shared_from_this<View> {
public:
    static ViewRef create(const ci::Rectf& frame);
    virtual ~View();

    ViewRef getPtr() { return shared_from_this(); }

    inline void setFrame(const ci::Rectf& frame) { mFrame = frame; }
    inline ci::Rectf getFrame() const { return mFrame; }
    inline ci::Rectf getBounds() const { return ci::Rectf(ci::vec2(0), mFrame.getSize()); }

    inline ViewRef getSuperview() const { return mSuperview; }
    inline std::vector<ViewRef> getSubviews() const { return mSubviews; }
    void addSubview(const ViewRef& view);
    void removeFromSuperview();
    bool isDescendantOfView(const ViewRef& view);

    inline void setBackgroundColor(const ci::Color& color) { mBackgroundColor = color; }
    inline ci::Color getBackgroundColor() const { return mBackgroundColor; }

    inline void setHidden(bool hidden) { mHidden = hidden; }
    inline bool isHidden() const { return mHidden; }

    virtual void draw();

    void connectEventListeners();
    void disconnectEventListeners();

    virtual void mouseDown(ci::app::MouseEvent event) {}
    virtual void mouseUp(ci::app::MouseEvent event) {}
    virtual void mouseWheel(ci::app::MouseEvent event) {}
    virtual void mouseMove(ci::app::MouseEvent event) {}
    virtual void mouseDrag(ci::app::MouseEvent event) {}

    ci::ivec2 convertPointFromView(const ci::vec2& point, const ViewRef& view);
    ci::ivec2 convertPointToView(const ci::ivec2& point, const ViewRef& view);

protected:
    View(const ci::Rectf& frame);

    inline void setSuperview(const ViewRef& view) { mSuperview = view; }
    void removeSubview(const ViewRef& view);

    ViewRef hitTestPoint(const ci::ivec2& point);
    bool isPointInsideBounds(const ci::ivec2& point);

    ci::Rectf mFrame;

    ViewRef mSuperview;
    std::vector<ViewRef> mSubviews;

    ci::Color mBackgroundColor;
    bool mHidden;

    ci::signals::scoped_connection mConnectionMouseDown;
    ci::signals::scoped_connection mConnectionMouseUp;
    ci::signals::scoped_connection mConnectionMouseWheel;
    ci::signals::scoped_connection mConnectionMouseMove;
    ci::signals::scoped_connection mConnectionMouseDrag;
    ViewRef mTrackingView;
    ViewRef mTrackingOverView;
};

}}