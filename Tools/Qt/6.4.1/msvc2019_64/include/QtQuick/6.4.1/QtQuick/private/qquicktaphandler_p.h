// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QQUICKTAPHANDLER_H
#define QQUICKTAPHANDLER_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "qquickitem.h"
#include "qevent.h"
#include "qquicksinglepointhandler_p.h"
#include <QtCore/qbasictimer.h>

QT_BEGIN_NAMESPACE

class Q_QUICK_PRIVATE_EXPORT QQuickTapHandler : public QQuickSinglePointHandler
{
    Q_OBJECT
    Q_PROPERTY(bool pressed READ isPressed NOTIFY pressedChanged)
    Q_PROPERTY(int tapCount READ tapCount NOTIFY tapCountChanged)
    Q_PROPERTY(qreal timeHeld READ timeHeld NOTIFY timeHeldChanged)
    Q_PROPERTY(qreal longPressThreshold READ longPressThreshold WRITE setLongPressThreshold NOTIFY longPressThresholdChanged)
    Q_PROPERTY(GesturePolicy gesturePolicy READ gesturePolicy WRITE setGesturePolicy NOTIFY gesturePolicyChanged)

    QML_NAMED_ELEMENT(TapHandler)
    QML_ADDED_IN_VERSION(2, 12)

public:
    enum GesturePolicy {
        DragThreshold,
        WithinBounds,
        ReleaseWithinBounds,
        DragWithinBounds
    };
    Q_ENUM(GesturePolicy)

    explicit QQuickTapHandler(QQuickItem *parent = nullptr);

    bool isPressed() const { return m_pressed; }

    int tapCount() const { return m_tapCount; }
    qreal timeHeld() const { return (m_holdTimer.isValid() ? m_holdTimer.elapsed() / 1000.0 : -1.0); }

    qreal longPressThreshold() const;
    void setLongPressThreshold(qreal longPressThreshold);

    GesturePolicy gesturePolicy() const { return m_gesturePolicy; }
    void setGesturePolicy(GesturePolicy gesturePolicy);

Q_SIGNALS:
    void pressedChanged();
    void tapCountChanged();
    void timeHeldChanged();
    void longPressThresholdChanged();
    void gesturePolicyChanged();
    // the second argument (Qt::MouseButton) was added in 6.2: avoid name clashes with IDs by not naming it for now
    void tapped(QEventPoint eventPoint, Qt::MouseButton /* button */);
    void singleTapped(QEventPoint eventPoint, Qt::MouseButton /* button */);
    void doubleTapped(QEventPoint eventPoint, Qt::MouseButton /* button */);
    void longPressed();

protected:
    void onGrabChanged(QQuickPointerHandler *grabber, QPointingDevice::GrabTransition transition,
                       QPointerEvent *ev, QEventPoint &point) override;
    void timerEvent(QTimerEvent *event) override;
    bool wantsEventPoint(const QPointerEvent *event, const QEventPoint &point) override;
    void handleEventPoint(QPointerEvent *event, QEventPoint &point) override;

private:
    void setPressed(bool press, bool cancel, QPointerEvent *event, QEventPoint &point);
    int longPressThresholdMilliseconds() const;
    void connectPreRenderSignal(bool conn = true);
    void updateTimeHeld();

private:
    QPointF m_lastTapPos;
    qreal m_lastTapTimestamp = 0;
    QElapsedTimer m_holdTimer;
    QBasicTimer m_longPressTimer;
    int m_tapCount = 0;
    int m_longPressThreshold = -1;
    GesturePolicy m_gesturePolicy = GesturePolicy::DragThreshold;
    bool m_pressed = false;

    static qreal m_multiTapInterval;
    static int m_mouseMultiClickDistanceSquared;
    static int m_touchMultiTapDistanceSquared;
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QQuickTapHandler)

#endif // QQUICKTAPHANDLER_H